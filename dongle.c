/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:10 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/19 19:09:38 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	acquire_dongle(t_dongle *f_dongle, t_dongle *s_dongle, t_coder *coder)
{
	long			max_available;
	long			cur_time;
	long			priority;
	long			wait_cooldown;
	t_queue_node	node;
	long			last_compile;

	pthread_mutex_lock(&coder->last_compile_start_mut);
	last_compile = coder->last_compile_start;
	pthread_mutex_unlock(&coder->last_compile_start_mut);
	pthread_mutex_lock(&coder->sim->wait_queue->queue_mut);
	cur_time = get_time_fn();
	if (coder->sim->infos->sheduler == SCHEDULER_FIFO)
		priority = cur_time;
	else
		priority = last_compile + coder->sim->infos->time_to_burnout;
	node.coder_id = coder->id;
	node.priority_s= priority;
	if (coder->sim->wait_queue->size > 0 || f_dongle->is_held || s_dongle->is_held)
	{
		heap_insert(coder->sim->wait_queue, node);
		while(f_dongle->is_held || !s_dongle->is_held)
		{
			pthread_cond_wait(&coder->personal_cond, &coder->sim->wait_queue->queue_mut);
			if (checker(coder->sim))
			{
				pthread_mutex_unlock(&coder->sim->wait_queue->queue_mut);
				return (-1);
			}
			if (!f_dongle->is_held || !s_dongle->is_held)
				break;
			heap_insert(coder->sim->wait_queue, node);
		}
	}
	f_dongle->is_held = 1;
	s_dongle->is_held = 1;
	pthread_mutex_unlock(&coder->sim->wait_queue->queue_mut);
	cur_time = get_time_fn();
	if (cur_time < f_dongle->available_at_ms || cur_time < s_dongle->available_at_ms)
	{
		max_available = f_dongle->available_at_ms > s_dongle->available_at_ms ?
						f_dongle->available_at_ms : s_dongle->available_at_ms;
		wait_cooldown = max_available - cur_time;
		if (wait_cooldown > 0 && interruptible_sleep(coder->sim, wait_cooldown))
			return (-1);
	}
	return (0);
}

void	release_dongle(t_simulation *sim, t_dongle *f_dongle, t_dongle *s_dongle, long cooldown_ms)
{
	t_queue_node next_node;

	pthread_mutex_lock(&sim->wait_queue->queue_mut);
	s_dongle->is_held = 0;
	s_dongle->available_at_ms = get_time_fn() + cooldown_ms;	
	f_dongle->is_held = 0;
	f_dongle->available_at_ms = get_time_fn() + cooldown_ms;
	if (sim->wait_queue->size > 0)
	{
		heap_extract_min(sim->wait_queue, &next_node);
		pthread_cond_signal(&sim->coders[next_node.coder_id - 1].personal_cond);
	}
	pthread_mutex_unlock(&sim->wait_queue->queue_mut);
}
