/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:26 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/24 19:47:19 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wake_dongles(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->wait_queue->queue_mut);
	while (i < sim->infos->number_of_coders)
	{
		pthread_cond_broadcast(&sim->coders[i].personal_cond);
		i++;
	}
	pthread_mutex_unlock(&sim->wait_queue->queue_mut);
}

static int	check_routine(t_simulation *sim, int *all_done)
{
	int		i;
	long	deadline;

	i = 0;
	while (i < sim->infos->number_of_coders)
	{
		if (sim->coders[i].compile_done
			< sim->infos->number_of_compiles_required)
		{
			*all_done = 0;
			deadline = get_time_fn() - sim->coders[i].last_compile_start;
			if (deadline > sim->infos->time_to_burnout)
			{
				sim->stopped = 1;
				log_monitor_message(sim, sim->coders[i].id, "burned out",
					deadline);
				pthread_cond_broadcast(&sim->state_cond);
				pthread_mutex_unlock(&sim->state_lock);
				wake_dongles(sim);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

static void	wake_up(t_simulation *sim)
{
	pthread_cond_broadcast(&sim->state_cond);
	pthread_mutex_unlock(&sim->state_lock);
	wake_dongles(sim);
}

void	*monitor_routine(void *args)
{
	t_simulation	*sim;
	int				all_done;

	sim = (t_simulation *) args;
	pthread_mutex_lock(&sim->thread_creation_mutex);
	while (sim->threads_created == 0)
		pthread_cond_wait(&sim->thread_creation_cond,
			&sim->thread_creation_mutex);
	pthread_mutex_unlock(&sim->thread_creation_mutex);
	while (!sim->stopped)
	{
		all_done = 1;
		pthread_mutex_lock(&sim->state_lock);
		if (check_routine(sim, &all_done))
			return (NULL);
		if (all_done)
		{
			sim->stopped = 1;
			wake_up(sim);
			return (NULL);
		}
		pthread_mutex_unlock(&sim->state_lock);
		interruptible_sleep(sim, 1);
	}
	return (NULL);
}
