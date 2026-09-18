/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:10 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/18 11:06:34 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	acquire_dongle(t_dongle *dongle, t_coder *thread, t_dongle *s_dongle)
{
	struct timespec deadline;

	pthread_mutex_lock(&dongle->dongle_mut);
	while (dongle->is_held == 1 || get_time_fn() < dongle->available_at_ms)
	{
		if (checker(thread->sim))
		{
			pthread_mutex_unlock(&dongle->dongle_mut);
			return (-1);
		}
		if (dongle->is_held == 1)
			pthread_cond_wait(&dongle->con_var, &dongle->dongle_mut);
		else
		{
			deadline.tv_sec = dongle->available_at_ms / 1000;
			deadline.tv_nsec = (dongle->available_at_ms % 1000) * 1000000;
			pthread_cond_timedwait(&dongle->con_var, &dongle->dongle_mut, &deadline);
		}
	}
	dongle->is_held = 1;
	pthread_mutex_unlock(&dongle->dongle_mut);
	return (0);
}

void	release_dongle(t_dongle *dongle, long cooldown_ms)
{
	pthread_mutex_lock(&dongle->dongle_mut);
	dongle->is_held = 0;
	dongle->available_at_ms = get_time_fn() + cooldown_ms;
	pthread_cond_broadcast(&dongle->con_var);
	pthread_mutex_unlock(&dongle->dongle_mut);
}
