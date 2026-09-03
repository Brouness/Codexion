/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:06 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/10 18:41:19 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define SCHEDULER_FIFO 0
# define SCHEDULER_EDF 1

typedef struct t_codexion
{
	int		number_of_coders;
	long	time_to_burnout;
	long	time_to_compile;
	long	time_to_debug;
	long	time_to_refactor;
	int		number_of_compiles_required;
	long	dongle_cooldown;
	int		sheduler;
}			t_args;

typedef struct s_coder
{
	int	c_id;
	t_dongle	*left;
	t_dongle	*right;
	t_args		*ptr;
} t_coder;

typedef struct s_dongle
{
	int		dongle_available;
	
}	t_dongle;


int validate_arguments(char *s);
int	parse_args(char **s, t_args *n);

#endif
