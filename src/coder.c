/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:34:56 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/20 20:12:26 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_sim_stopped(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->state_lock);
	if (coder->sim->stopped)
	{
		pthread_mutex_unlock(&coder->sim->state_lock);
		return (0);
	}
	pthread_mutex_unlock(&coder->sim->state_lock);
	return (1);
}

static int	validate_sim(t_dongle *first, t_dongle *second, t_coder *thread)
{
	int		validate;
	long	cooldown;

	cooldown = thread->sim->infos->dongle_cooldown;
	if (acquire_dongle(first, second, thread))
		return (-1);
	validate = approve_log(thread, first, second);
	if (validate)
	{
		if (validate == -1)
		{
			release_dongle(thread->sim, first, second, cooldown);
			return (-1);
		}
		return (-1);
	}
	return (0);
}

void	*coder_routine(void *args)
{
	t_coder	*thread;
	int		number_of_compile;

	thread = (t_coder *) args;
	pthread_mutex_lock(&thread->sim->thread_creation_mutex);
	while (thread->sim->threads_created == 0)
		pthread_cond_wait(&thread->sim->thread_creation_cond,
			&thread->sim->thread_creation_mutex);
	pthread_mutex_unlock(&thread->sim->thread_creation_mutex);
	if (thread->id % 2 != 0)
		interruptible_sleep(thread->sim, 6);
	if (thread->left_dongle == thread->right_dongle)
		return (NULL);
	number_of_compile = 0;
	while (check_sim_stopped(thread)
		&& number_of_compile < thread->sim->infos->number_of_compiles_required)
	{
		if (validate_sim(thread->left_dongle, thread->right_dongle, thread))
			break ;
		number_of_compile++;
	}
	return (NULL);
}
