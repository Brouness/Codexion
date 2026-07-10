/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:22 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/10 12:52:53 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int validate_arguments(char *s)
{
	int i;

	i = 0;
	if (!s || !s[0])
		return 1;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return 1;

	while (s[i])
	{
		if (s[i] == '+' && i == 0 && s[i++])
			i++;
		else if (s[i] <= '9' && s[i] >= '0')
			i++;
		else
			return 1;
	}
	return 0;
}

int main(int ac, char **av)
{
	int i = 1;
	t_args n;
	if (ac != 9)
		printf("Invalid number of arguments\n");
	else
	{
		while (av[i])
		{
			if (validate_arguments(av[i]))
				return printf("invalid arguments %s", av[i]);
			i++;
		}
		n.number_of_coders = atol(av[1]);
		printf("%d\n", n.number_of_coders);
	}
}
