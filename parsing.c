/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:29:22 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/18 21:57:43 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int validate_arguments(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return 1;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return 1;

	while (s[i])
	{
		if (s[i] == '+' && i == 0)
			i++;
		if (!s[i])
			return 1;
		else if (s[i] <= '9' && s[i] >= '0')
			i++;
		else
			return 1;
	}
	return 0;
}

int	check_numbers(char **s)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (atol(s[i]) < 0)
			return (1);
		i++;
	}
	return 0;
}

int	parse_args(char **s, t_args *n)
{
	int		i;

	i = 1;
	while (i < 8)
	{
		if (validate_arguments(s[i]))
			return 1;
		i++;
	}
	if (strcmp(s[i], "fifo") && strcmp(s[i], "edf"))
		return 1;
	if (check_numbers(s))
		return 1;
	n->number_of_coders = atoi(s[1]);
	n->time_to_burnout = atol(s[2]);
	n->time_to_compile = atol(s[3]);
	n->time_to_debug = atol(s[4]);
	n->time_to_refactor = atol(s[5]);
	n->number_of_compiles_required = atoi(s[6]);
	n->dongle_cooldown = atol(s[7]);
	if (!strcmp(s[i], "fifo"))
		n->sheduler = SCHEDULER_FIFO;
	else
		n->sheduler = SCHEDULER_EDF;
	return 0;
}
