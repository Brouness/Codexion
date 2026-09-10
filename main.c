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

int	main(int ac, char **av)
{
	int				i;
	t_args			args;
	t_data_needed	*ptr;

	i = 1;
	if (ac != 9)
		printf("Invalid number of arguments\n");
	else
	{
		if (parse_args(av, &args))
		{
			printf("invalid arguments\n");
			return (0);
		}
		ptr = init(args);
		if (!ptr)
		{
			fprintf(stderr,"error");
		}
		i = 0;
		// while(i < args.number_of_coders)
		// {
		// 	pthread_create(&ptr->coders[i], NULL, start_cooder_routine, ptr);
		// }
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
