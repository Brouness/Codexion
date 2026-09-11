/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:15 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/12 10:14:46 by ybourajl         ###   ########.fr       */
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
		if (pthread_mutex_init(&sim->dongles[i].dongle_mut, NULL) != 0)
			break ;
		if (pthread_cond_init(&sim->dongles[i].con_var, NULL) != 0)
		{
			pthread_mutex_destroy(&sim->dongles[i].dongle_mut);
			break ;
		}
		i++;
	}
	if (i < sim->infos->number_of_coders)
	{
		while (i-- > 0)
		{
			pthread_mutex_destroy(&sim->dongles[i].dongle_mut);
			pthread_cond_destroy(&sim->dongles[i].con_var);
		}
		free(sim->dongles);
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
		sim->coders[i].last_compile_start = 0;
		sim->coders[i].right_dongle = &sim->dongles[i];
		sim->coders[i].left_dongle = &sim->dongles[(i - 1 + nbr) % nbr];
		sim->coders[i].args = sim->infos;
		i++;
	}
	return (0);
}

long	get_time_fn(void)
{
	struct timeval	time;
	long			curent_time;

	if (gettimeofday(&time, NULL))
		return (-1);
	curent_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (curent_time);
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

t_simulation	*init_simulation(t_args *args)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	if (-1 == (sim->start_time = get_time_fn()))
	{
		free(sim);
		return (NULL);
	}
	sim->infos = args;
	sim->stopped = 0;
	if (0 != pthread_mutex_init(&sim->log_lock, NULL))
	{
		free(sim);
		return (NULL);
	}
	if (0 != pthread_cond_init(&sim->state_cond, NULL))
	{
		pthread_mutex_destroy(&sim->log_lock);
		free(sim);
		return (NULL);
	}
	if (0 != pthread_mutex_init(&sim->state_lock, NULL))
	{
		pthread_mutex_destroy(&sim->log_lock);
		pthread_cond_destroy(&sim->state_cond);
		free(sim);
		return (NULL);
	}
	if (init_simulation_objects(sim))
		return (NULL);
	return (sim);
}
