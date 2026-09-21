/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:10 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/21 21:27:39 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	update_last_compile(t_coder *coder)
{
	long	last_compile;
	long	priority;

	pthread_mutex_lock(&coder->last_compile_start_mut);
	last_compile = coder->last_compile_start;
	pthread_mutex_unlock(&coder->last_compile_start_mut);
	if (coder->sim->infos->scheduler == SCHEDULER_FIFO)
		priority = get_time_fn();
	else
		priority = last_compile + coder->sim->infos->time_to_burnout;
	return (priority);
}

static int	wait_cooldown(t_dongle *f_dongle,
				t_dongle *s_dongle, t_coder *coder)
{
	long	max_available;
	long	wait_cooldown;

	if (get_time_fn() < f_dongle->available_at_ms
		|| get_time_fn() < s_dongle->available_at_ms)
	{
		if (f_dongle->available_at_ms > s_dongle->available_at_ms)
			max_available = f_dongle->available_at_ms;
		else
			max_available = s_dongle->available_at_ms;
		wait_cooldown = max_available - get_time_fn();
		if (wait_cooldown > 0 && interruptible_sleep(coder->sim, wait_cooldown))
			return (-1);
	}
	return (0);
}

int	acquire_dongle(t_dongle *f_dongle, t_dongle *s_dongle, t_coder *coder)
{
	t_queue_node	node;

	pthread_mutex_lock(&coder->sim->wait_queue->queue_mut);
	node.coder_id = coder->id;
	node.priority_s = update_last_compile(coder);
	node.coder = coder;
	heap_insert(coder->sim->wait_queue, node);
	while (f_dongle->is_held || s_dongle->is_held)
	{
		pthread_cond_wait(&coder->personal_cond,
			&coder->sim->wait_queue->queue_mut);
		if (checker(coder->sim))
		{
			heap_remove_by_id(coder->sim->wait_queue, coder->id);
			pthread_mutex_unlock(&coder->sim->wait_queue->queue_mut);
			return (-1);
		}
	}
	heap_remove_by_id(coder->sim->wait_queue, coder->id);
	f_dongle->is_held = 1;
	s_dongle->is_held = 1;
	pthread_mutex_unlock(&coder->sim->wait_queue->queue_mut);
	if (wait_cooldown(f_dongle, s_dongle, coder))
		return (-1);
	return (0);
}

void	release_dongle(t_simulation *sim,
			t_dongle *f_dongle, t_dongle *s_dongle, long cooldown_ms)
{
	int	i;

	pthread_mutex_lock(&sim->wait_queue->queue_mut);
	s_dongle->is_held = 0;
	s_dongle->available_at_ms = get_time_fn() + cooldown_ms;
	f_dongle->is_held = 0;
	f_dongle->available_at_ms = get_time_fn() + cooldown_ms;
	i = 0;
	while (i < sim->wait_queue->size)
	{
		pthread_cond_signal(
			&sim->coders[sim->wait_queue->queue[i].coder_id - 1].personal_cond);
		i++;
	}
	pthread_mutex_unlock(&sim->wait_queue->queue_mut);
}
