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
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define SCHEDULER_FIFO 0
# define SCHEDULER_EDF 1

typedef struct s_simulation t_simulation;

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

typedef struct s_dongle
{
	pthread_mutex_t	dongle_mut;
	pthread_cond_t	con_var;
	int				dongle_id;
	int				is_held;
	long			available_at_ms;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t		thread;
	long			last_compile_start;
	int				compile_done;
	t_simulation	*sim;
}	t_coder;


typedef	struct s_simulation
{
	t_args			*infos;
	t_coder			*coders;
	t_dongle		*dongles;
	// pthread_t	monitor_thread;
	long			start_time;
	int				stopped;
	pthread_mutex_t	state_lock;
	pthread_cond_t	state_cond;
	pthread_mutex_t	log_lock;
}	t_simulation;

//init all
t_simulation	*init_simulation(t_args *args);
int				init_dongles(t_simulation *sim);
int				init_coders(t_simulation *sim);

//clean memory
void    destroy_simulation(t_simulation *sim);
void    *thread_loging(void *args);
int 			validate_arguments(char *s);
int				parse_args(char **s, t_args *n);

#endif
