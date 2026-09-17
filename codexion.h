/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:06 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/17 18:10:52 by ybourajl         ###   ########.fr       */
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

// struct timeval	time;
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
typedef struct s_time
{
	struct timespec	time;
} t_time;

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
	pthread_mutex_t	last_compile_start_mut;
	long			last_compile_start;
	int				compile_done;
	pthread_cond_t	thread_creation_cond;
	pthread_mutex_t	thread_creation_mutex;
	t_simulation	*sim;
}	t_coder;

typedef	struct s_simulation
{
	t_args			*infos;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		monitor_thread;
	long			start_time;
	int				stopped;
	pthread_mutex_t	state_lock;
	pthread_cond_t	state_cond;
	pthread_cond_t	thread_creation_cond;
	pthread_mutex_t	thread_creation_mutex;
	pthread_mutex_t	log_lock;
	int				threads_created;
	t_heap			*heap;
}	t_simulation;

//heap
typedef struct s_heap
{
	int	*data;
	int	size;
	int	capacity;
}	t_heap;

void	heap_init(t_heap *h, int capacity);
int		heap_insert(t_heap *h, int value);
int		heap_extract_min(t_heap *h, int	*out);
void	heap_destroy(t_heap *h);
t_heap	*scheduler_init(t_simulation *sim);

//init all
t_simulation	*init_simulation(t_args *args);
int				init_dongles(t_simulation *sim);
int				init_coders(t_simulation *sim);

//clean memory
void	destroy_simulation(t_simulation *sim);
void	*couder_routine(void *args);
int 	validate_arguments(char *s);
int		parse_args(char **s, t_args *n);
long	get_time_fn(void);

//dongles utils
int		acquire_dongle(t_dongle *dongle, t_coder *thread);
void    release_dongle(t_dongle *dongle, long cooldown_ms);

//log helpers
void    log_message(t_simulation *sim, int id, char *msg);
void    log_monitor_message(t_simulation *sim, int id, char *msg);
int approve_log(t_coder *thread, t_dongle *first, t_dongle *second);

//monitor
void    *monitor_routine(void *args);

//time utils
int		interruptible_sleep(t_simulation *sim, long duration_ms);

#endif
