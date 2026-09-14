/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:26 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/09 15:35:27 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static  void    wake_dongles(t_simulation *sim)
{
	int i;

	i = 0;
	while(i < sim->infos->number_of_coders)
	{
		pthread_mutex_lock(&sim->dongles[i].dongle_mut);
		pthread_cond_broadcast(&sim->dongles[i].con_var);
		pthread_mutex_unlock(&sim->dongles[i].dongle_mut);
		i++;
	}
}

void    *monitor_routine(void *args)
{
	t_simulation    *sim;
	int             i;
	int             all_done;

	sim = (t_simulation *) args;
	pthread_mutex_lock(&sim->thread_creation_mutex);
	while(sim->threads_created == 0)
		pthread_cond_wait(&sim->thread_creation_cond, &sim->thread_creation_mutex);
	pthread_mutex_unlock(&sim->thread_creation_mutex);
	while(!sim->stopped)
	{    
		i = 0;
		all_done = 1;
		pthread_mutex_lock(&sim->state_lock);
		while (i < sim->infos->number_of_coders)
		{
			if (sim->coders[i].compile_done < sim->infos->number_of_compiles_required)
			{
				all_done = 0;
				if (get_time_fn() - sim->coders[i].last_compile_start > sim->infos->time_to_burnout)
				{
					sim->stopped = 1;
					log_monitor_message(sim, sim->coders[i].id, "burned out");
					pthread_mutex_unlock(&sim->state_lock);
					pthread_cond_broadcast(&sim->state_cond);
					wake_dongles(sim);
					return NULL;
				}
			}
			i++;
		}
		if (all_done)
			sim->stopped = 1;
		pthread_mutex_unlock(&sim->state_lock);
		usleep(1000);
	}
	return NULL;
}
