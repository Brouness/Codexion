/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:31 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/19 19:59:25 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	interruptible_sleep(t_simulation *sim, long duration_ms)
{
	struct timespec	deadline;
	long			target_ms;
	int				was_stopped;

	target_ms = get_time_fn() + duration_ms;
	deadline.tv_sec = target_ms / 1000;
	deadline.tv_nsec = (target_ms % 1000) * 1000000;
	pthread_mutex_lock(&sim->state_lock);
	while (!sim->stopped && get_time_fn() < target_ms)
		pthread_cond_timedwait(&sim->state_cond, &sim->state_lock, &deadline);
	was_stopped = sim->stopped;
	pthread_mutex_unlock(&sim->state_lock);
	if (was_stopped)
		return (-1);
	return (0);
}

long	get_time_fn(void)
{
	struct timeval	time;
	long			curent_time;

	if (gettimeofday(&time, NULL))
		return (-1);
	curent_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (curent_time);
}
