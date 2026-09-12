/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:34:56 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/09 15:34:57 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void    *couder_routine(void *args)
{
	t_coder *thread;
	int		id;
	long	current_time;
	int		number_of_compile;

	number_of_compile = 0;
	thread = (t_coder *) args;
	id = thread->id;
	while(number_of_compile <= thread->sim->infos->number_of_compiles_required)
	{
		pthread_mutex_lock(&thread->left_dongle->dongle_mut);
		current_time = get_time_fn() - thread->sim->start_time;
		if (thread->left_dongle->is_held == 0 && current_time >= thread->left_dongle->available_at_ms)
		{
			
			thread->left_dongle->is_held = 1;
			pthread_mutex_lock(&thread->sim->log_lock);
			current_time = get_time_fn() - thread->sim->start_time;
			printf("%ld %d has taken a dongle\n", current_time, thread->id);
			pthread_mutex_unlock(&thread->sim->log_lock);
			current_time = get_time_fn() - thread->sim->start_time;
			thread->last_compile_start = get_time_fn() - thread->sim->start_time;
			pthread_mutex_lock(&thread->sim->log_lock);
			printf("%ld %d is compiling\n", current_time, id);
			pthread_mutex_unlock(&thread->sim->log_lock);
			usleep(thread->sim->infos->time_to_compile * 1000);
			current_time = get_time_fn() - thread->sim->start_time;
			pthread_mutex_lock(&thread->sim->log_lock);
			printf("%ld %d is debugging\n", current_time, id);
			pthread_mutex_unlock(&thread->sim->log_lock);
			usleep(thread->sim->infos->time_to_debug * 1000);
			current_time = get_time_fn() - thread->sim->start_time;
			pthread_mutex_lock(&thread->sim->log_lock);
			printf("%ld %d is refactoring\n", current_time, id);
			pthread_mutex_unlock(&thread->sim->log_lock);
			usleep(thread->sim->infos->time_to_refactor * 1000);
			thread->left_dongle->is_held = 0;
			thread->left_dongle->available_at_ms = get_time_fn() + thread->sim->infos->dongle_cooldown;
			acquire_dongle(thread->left_dongle);
			release_dongle(thread->left_dongle, thread->sim->infos->dongle_cooldown);
			thread->left_dongle->available_at_ms = thread->sim->infos->dongle_cooldown + get_time_fn() - thread->sim->start_time;
			
			number_of_compile++;
		}
		pthread_mutex_unlock(&thread->left_dongle->dongle_mut);
	}
	return NULL;
}
