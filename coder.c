/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:34:56 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/09 15:34:57 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_sim_stopped(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->state_lock);
	if (coder->sim->stopped)
	{
		pthread_mutex_unlock(&coder->sim->state_lock);
		return 0;
	}
	pthread_mutex_unlock(&coder->sim->state_lock);
	return 1;
}

void	*couder_routine(void *args)
{
	t_coder *thread;
	int		number_of_compile;
	t_dongle	*first;
	t_dongle	*second;

	thread = (t_coder *) args;
	pthread_mutex_lock(&thread->sim->thread_creation_mutex);
	while(thread->sim->threads_created == 0)
		pthread_cond_wait(&thread->sim->thread_creation_cond, &thread->sim->thread_creation_mutex);
	pthread_mutex_unlock(&thread->sim->thread_creation_mutex);
	if (thread->left_dongle->dongle_id < thread->right_dongle->dongle_id)
	{
		first = thread->left_dongle;
		second = thread->right_dongle;
	}
	else
	{
		first = thread->right_dongle;
		second = thread->left_dongle;
	}
	number_of_compile = 0;
	while(check_sim_stopped(thread) && number_of_compile < thread->sim->infos->number_of_compiles_required)
	{
		if (acquire_dongle(first, thread))
			break;
		else if (acquire_dongle(second, thread))
			break;
		if (approve_log(thread, first, second))
			break;
		number_of_compile++;
	}
	return (NULL);
}
