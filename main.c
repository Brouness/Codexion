/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:22 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/10 18:59:58 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int ac, char **av)
{
	int i = 1;
	t_args n;
	if (ac != 9)
		printf("Invalid number of arguments\n");
	else
	{
		if (parse_args(av, &n))
		{
			printf("invalid arguments\n");
			return 0;
		}
		printf("%d\n", n.number_of_coders);
		printf("%ld\n", n.time_to_burnout);
		printf("%ld\n", n.time_to_compile);
		printf("%ld\n", n.time_to_debug);
		printf("%ld\n", n.time_to_refactor);
		printf("%d\n", n.number_of_compiles_required);
		printf("%ld\n", n.dongle_cooldown);
		printf("%d\n", n.sheduler);
	}
}
