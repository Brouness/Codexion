/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:19 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/09 15:35:20 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_message(t_simulation *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->state_lock);
	pthread_mutex_lock(&sim->log_lock);
	if (sim->stopped == 0)
		printf("%ld %d %s\n", get_time_fn() - sim->start_time, id, msg);
	pthread_mutex_unlock(&sim->state_lock);
	pthread_mutex_unlock(&sim->log_lock);
}

void	log_monitor_message(t_simulation *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->log_lock);
	printf("%ld %d %s\n", get_time_fn() - sim->start_time, id, msg);
	pthread_mutex_unlock(&sim->log_lock);
}

static int  checker(t_simulation *sim)
{
	pthread_mutex_lock(&sim->state_lock);
	if (sim->stopped)
	{
		pthread_mutex_unlock(&sim->state_lock);
		return (-1);
	}
	pthread_mutex_unlock(&sim->state_lock);
	return (0);
}

int approve_log(t_coder *thread, t_dongle *first, t_dongle *second)
{
	int		id;

	id = thread->id;
	if (checker(thread->sim))
		return (-1);
	log_message(thread->sim, id, "has taken a dongle");
	log_message(thread->sim, id, "has taken a dongle");
	log_message(thread->sim, id, "is compiling");
	pthread_mutex_lock(&thread->sim->state_lock);
	thread->last_compile_start = get_time_fn();
	thread->compile_done++;
	pthread_mutex_unlock(&thread->sim->state_lock);
	usleep(thread->sim->infos->time_to_compile * 1000);
	if (checker(thread->sim))
		return (-1);
	release_dongle(first, thread->sim->infos->dongle_cooldown);
	release_dongle(second, thread->sim->infos->dongle_cooldown);
	log_message(thread->sim, id, "is debugging");
	usleep(thread->sim->infos->time_to_debug * 1000);
	if (checker(thread->sim))
		return (-1);
	log_message(thread->sim, id, "is refactoring");
	usleep(thread->sim->infos->time_to_refactor * 1000);
	return (0);
}
