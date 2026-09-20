/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:19 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/20 20:05:35 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_message(t_simulation *sim, int id, char *msg)
{	
	pthread_mutex_lock(&sim->state_lock);
	pthread_mutex_lock(&sim->log_lock);
	if (sim->stopped)
	{
		pthread_mutex_unlock(&sim->log_lock);
		pthread_mutex_unlock(&sim->state_lock);
		return;
	}
	printf("%ld %d %s\n", get_time_fn() - sim->start_time, id, msg);
	pthread_mutex_unlock(&sim->log_lock);
	pthread_mutex_unlock(&sim->state_lock);
}

void	log_monitor_message(t_simulation *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->log_lock);
	printf("%ld %d %s\n", get_time_fn() - sim->start_time, id, msg);
	pthread_mutex_unlock(&sim->log_lock);
}

int	checker(t_simulation *sim)
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

int	approve_log(t_coder *thread, t_dongle *f, t_dongle *s)
{
	if (checker(thread->sim))
		return (-1);
	log_message(thread->sim, thread->id, "has taken a dongle");
	log_message(thread->sim, thread->id, "has taken a dongle");
	log_message(thread->sim, thread->id, "is compiling");
	pthread_mutex_lock(&thread->sim->state_lock);
	thread->last_compile_start = get_time_fn();
	pthread_mutex_unlock(&thread->sim->state_lock);
	if (interruptible_sleep(thread->sim, thread->sim->infos->time_to_compile))
		return (-1);
	if (checker(thread->sim))
		return (-1);
	release_dongle(thread->sim, f, s, thread->sim->infos->dongle_cooldown);
	log_message(thread->sim, thread->id, "is debugging");
	if (interruptible_sleep(thread->sim, thread->sim->infos->time_to_debug))
		return (-2);
	if (checker(thread->sim))
		return (-2);
	log_message(thread->sim, thread->id, "is refactoring");
	pthread_mutex_lock(&thread->sim->state_lock);
	thread->compile_done++;
	pthread_mutex_unlock(&thread->sim->state_lock);
	if (interruptible_sleep(thread->sim, thread->sim->infos->time_to_refactor))
		return (-2);
	return (0);
}
