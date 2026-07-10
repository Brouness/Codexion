/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:29:22 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/10 16:36:27 by ybourajl         ###   ########.fr       */
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

int	parse_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (validate_arguments(s[i]))
		{
			printf("Error: argument %s", s[i]);
			return 1;
		}
		i++;
	}
	return 0;
}
