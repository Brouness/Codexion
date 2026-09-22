/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:06 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/22 11:54:22 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define SCHEDULER_FIFO 0
# define SCHEDULER_EDF 1

typedef struct s_simulation	t_simulation;
typedef struct s_coder		t_coder;

typedef struct s_queue_node
{
	int		coder_id;
	int		priority_s;
	t_coder	*coder;
}	t_queue_node;

typedef struct s_heap
{
	pthread_mutex_t	queue_mut;
	t_queue_node	*queue;
	int				size;
	int				capacity;
}	t_heap;

typedef struct t_codexion
{
	int		number_of_coders;
	long	time_to_burnout;
	long	time_to_compile;
	long	time_to_debug;
	long	time_to_refactor;
	int		number_of_compiles_required;
	long	dongle_cooldown;
	int		scheduler;
}			t_args;

typedef struct s_dongle
{
	int				dongle_id;
	int				is_held;
	long			available_at_ms;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	pthread_cond_t	personal_cond;
	pthread_mutex_t	last_compile_start_mut;
	t_dongle		*right_dongle;
	t_dongle		*left_dongle;
	long			last_compile_start;
	int				compile_done;
	int				id;
	t_simulation	*sim;
}	t_coder;

typedef struct s_simulation
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
	t_heap			*wait_queue;
}	t_simulation;

t_heap			*heap_init(int capacity);
int				heap_insert(t_heap *h, t_queue_node node);
void			heap_extract_min(t_heap *h, t_queue_node *node);
void			heap_destroy(t_heap *h);

//init all
t_simulation	*init_simulation(t_args *args);
int				init_dongles(t_simulation *sim);
int				init_coders(t_simulation *sim);

//clean memory
void			destroy_simulation(t_simulation *sim);
void			free_malloc(t_simulation *sim);
void			*coder_routine(void *args);
int				validate_arguments(char *s);
int				parse_args(char **s, t_args *n);
long			get_time_fn(void);

//dongles utils
int				acquire_dongle(t_dongle *f_dongle,
					t_dongle *s_dongle, t_coder *coder);
void			release_dongle(t_simulation *sim, t_dongle *f_dongle,
					t_dongle *s_dongle, long cooldown_ms);

//log helpers
void			log_message(t_simulation *sim, int id, char *msg);
void			log_monitor_message(t_simulation *sim, int id, char *msg);
int				approve_log(t_coder *thread, t_dongle *first, t_dongle *second);

//monitor
void			*monitor_routine(void *args);

//utils
int				interruptible_sleep(t_simulation *sim, long duration_ms);
int				checker(t_simulation *sim);
void			heap_remove_by_id(t_heap *h, int coder_id);
int				choose(t_queue_node *a, t_queue_node *b);

#endif
