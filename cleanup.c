/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:34:53 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/20 10:56:57 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_malloc(t_simulation *sim)
{
	if (sim->dongles)
	{
		free(sim->dongles);
	}
	if (sim->coders)
		free(sim->coders);
	free(sim->wait_queue->queue);
	free(sim->wait_queue);
	free(sim);
}
void	destroy_simulation(t_simulation *sim)
{

	pthread_mutex_destroy(&sim->thread_creation_mutex);
	sim->stopped = 1;
	sim->threads_created = 1;
	pthread_cond_broadcast(&sim->thread_creation_cond);
	pthread_cond_destroy(&sim->thread_creation_cond);
	pthread_mutex_destroy(&sim->log_lock);
	pthread_mutex_destroy(&sim->state_lock);
	pthread_cond_destroy(&sim->state_cond);
	pthread_mutex_destroy(&sim->wait_queue->queue_mut);
	free_malloc(sim);
	return ;
}
void	heap_destroy(t_heap *h)
{
	if (h)
	{
		free(h->queue);
		free(h);
	}
}
