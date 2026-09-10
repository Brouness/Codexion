/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:22 by ybourajl          #+#    #+#             */
/*   Updated: 2026/08/29 17:00:03 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	start_simulation(t_args args)
{
	t_simulation	*sim;

	sim = init_simulation(&args);
	if (!sim)
		return (-1);
	if (init_coders(sim))
	{
		destroy_simulation(sim);
		return (-1);
	}
	if (init_dongles(sim))
	{
		destroy_simulation(sim);
		free(sim->coders);
		return (-1);
	}
	int i = 0;
	int nbr = sim->infos->number_of_coders;
	while(i < nbr)
	{
		pthread_create(&sim->coders[i].thread, NULL, thread_loging, &sim->coders[i]);
		i++;
	}
	return (0);

}

int	main(int ac, char **av)
{
	int				i;
	t_args			args;
	t_simulation	*sim;

	i = 0;
	if (ac != 9)
		printf("Invalid number of arguments\n");
	else
	{
		if (parse_args(av, &args))
		{
			printf("invalid arguments\n");
			return (-1);
		}
		if (start_simulation(args))
		{
			printf("invalid arguments\n");
			return (-1);
		}
		while(i < sim->infos->number_of_coders)
		{
			pthread_join(sim->coders[i].thread, NULL);
			i++;
		}
		printf("%d\n", args.number_of_coders);
		printf("%ld\n", args.time_to_burnout);
		printf("%ld\n", args.time_to_compile);
		printf("%ld\n", args.time_to_debug);
		printf("%ld\n", args.time_to_refactor);
		printf("%d\n", args.number_of_compiles_required);
		printf("%ld\n", args.dongle_cooldown);
		printf("%d\n", args.sheduler);

	}
}
