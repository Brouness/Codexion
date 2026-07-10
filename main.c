/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:22 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/10 16:47:42 by ybourajl         ###   ########.fr       */
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
		if (parse_args(av))
			return 0;
		n.number_of_coders = atoi(av[1]);
		printf("%d\n", n.number_of_coders);
	}
	
}
