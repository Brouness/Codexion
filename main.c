/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:22 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/19 17:13:41 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	threads_creation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->infos->number_of_coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL,
				couder_routine, &sim->coders[i]))
		{
			destroy_simulation(sim);
			return (-1);
		}
		i++;
	}
	if (pthread_create(&sim->monitor_thread, NULL, monitor_routine, sim))
	{
		destroy_simulation(sim);
		return (-1);
	}
	return (0);
}

static int	join_my_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	if (pthread_join(sim->monitor_thread, NULL))
	{
		destroy_simulation(sim);
		return (-1);
	}
	while (i < sim->infos->number_of_coders)
	{
		if (pthread_join(sim->coders[i].thread, NULL))
		{
			destroy_simulation(sim);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	start_simulation(t_args *args)
{
	t_simulation	*sim;

	sim = init_simulation(args);
	if (!sim)
		return (-1);
	if (threads_creation(sim))
		return (-1);
	pthread_mutex_lock(&sim->thread_creation_mutex);
	sim->threads_created = 1;
	pthread_cond_broadcast(&sim->thread_creation_cond);
	pthread_mutex_unlock(&sim->thread_creation_mutex);
	if (join_my_threads(sim))
		return (-1);
	destroy_simulation(sim);
	return (0);
}

int	main(int ac, char **av)
{
	t_args			args;
	char			*err;

	err = "something went wrong in your machine my code is goddeam good :)\n";
	if (ac != 9)
		printf("Invalid number of arguments\n");
	else
	{
		if (parse_args(av, &args))
		{
			printf("invalid arguments\n");
			return (-1);
		}
		if (start_simulation(&args))
		{
			printf("%s", err);
			return (-1);
		}
	}
	return (0);
}
