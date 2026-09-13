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

static int	check_sim_stopped(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->state_lock);
	if (coder->sim->stopped)
	{
		pthread_mutex_unlock(&coder->sim->state_lock);
		return 0;
	}
	pthread_mutex_unlock(&coder->sim->state_lock);
	return 1;
}
void	*couder_routine(void *args)
{
	t_coder *thread;

	int		id;
	int		number_of_compile;

	t_dongle	*first;
	t_dongle	*second;
	thread = (t_coder *) args;

	if (thread->left_dongle->dongle_id < thread->right_dongle->dongle_id)
	{
		first = thread->left_dongle;
		second = thread->right_dongle;
	}
	else
	{
		first = thread->right_dongle;
		second = thread->left_dongle;
	}
	number_of_compile = 0;
	id = thread->id;
	while(check_sim_stopped(thread) && number_of_compile < thread->sim->infos->number_of_compiles_required)
	{
		acquire_dongle(first);
		acquire_dongle(second);
		pthread_mutex_lock(&thread->sim->log_lock);
		log_message(get_time_fn() - thread->sim->start_time, id, "has taken a dongle");
		log_message(get_time_fn() - thread->sim->start_time, id, "has taken a dongle");
		log_message(get_time_fn() - thread->sim->start_time, id, "is compiling");
		pthread_mutex_lock(&thread->sim->state_lock);
		thread->last_compile_start = get_time_fn() - thread->sim->start_time;
		pthread_mutex_unlock(&thread->sim->state_lock);
		usleep(thread->sim->infos->time_to_compile * 1000);
		release_dongle(first, thread->sim->infos->dongle_cooldown);
		release_dongle(second, thread->sim->infos->dongle_cooldown);
		log_message(get_time_fn() - thread->sim->start_time, id, "is debugging");
		usleep(thread->sim->infos->time_to_debug * 1000);
		log_message(get_time_fn() - thread->sim->start_time, id, "is refactoring");
		usleep(thread->sim->infos->time_to_refactor * 1000);
		pthread_mutex_unlock(&thread->sim->log_lock);
		number_of_compile++;
	}
	return NULL;
}
