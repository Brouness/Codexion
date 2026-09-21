/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:15 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/21 22:18:31 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_dongles(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->dongles = malloc(sizeof(t_dongle) * sim->infos->number_of_coders);
	if (!sim->dongles)
		return (-1);
	while (i < sim->infos->number_of_coders)
	{
		sim->dongles[i].is_held = 0;
		sim->dongles[i].dongle_id = i + 1;
		sim->dongles[i].available_at_ms = 0;
		i++;
	}
	if (i < sim->infos->number_of_coders)
	{
		free(sim->dongles);
		sim->dongles = NULL;
		return (-1);
	}
	return (0);
}

int	init_coders(t_simulation *sim)
{
	int	nbr;
	int	i;

	nbr = sim->infos->number_of_coders;
	i = 0;
	sim->coders = malloc(sizeof(t_coder) * nbr);
	if (!sim->coders)
		return (-1);
	while (i < nbr)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].compile_done = 0;
		sim->coders[i].last_compile_start = sim->start_time;
		sim->coders[i].right_dongle = &sim->dongles[i];
		sim->coders[i].left_dongle = &sim->dongles[(i - 1 + nbr) % nbr];
		sim->coders[i].sim = sim;
		pthread_mutex_init(&sim->coders[i].last_compile_start_mut, NULL);
		pthread_cond_init(&sim->coders[i].personal_cond, NULL);
		i++;
	}
	return (0);
}

int	init_simulation_objects(t_simulation *sim)
{
	if (init_dongles(sim))
	{
		destroy_simulation(sim);
		return (-1);
	}
	if (init_coders(sim))
	{
		destroy_simulation(sim);
		return (-1);
	}
	return (0);
}

static int	init_all(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->thread_creation_mutex, NULL))
	{
		free_malloc(sim);
		return (-1);
	}
	if (pthread_cond_init(&sim->thread_creation_cond, NULL))
	{
		destroy_simulation(sim);
		return (-1);
	}
	if (pthread_mutex_init(&sim->log_lock, NULL)
		|| pthread_mutex_init(&sim->wait_queue->queue_mut, NULL))
	{
		destroy_simulation(sim);
		return (-1);
	}
	if (pthread_cond_init(&sim->state_cond, NULL)
		|| pthread_mutex_init(&sim->state_lock, NULL))
	{
		destroy_simulation(sim);
		return (-1);
	}
	return (0);
}

t_simulation	*init_simulation(t_args *args)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	sim->start_time = get_time_fn();
	if (-1 == (sim->start_time))
	{
		free(sim);
		return (NULL);
	}
	sim->infos = args;
	sim->threads_created = 0;
	sim->stopped = 0;
	sim->wait_queue = heap_init(sim->infos->number_of_coders);
	if (!sim->wait_queue)
	{
		free_malloc(sim);
		return (NULL);
	}
	if (init_all(sim))
		return (NULL);
	if (init_simulation_objects(sim))
		return (NULL);
	return (sim);
}
