/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:26 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/09 15:35:27 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    *monitor_routine(void *args)
{
    t_simulation    *sim;
    int             i;

    sim = (t_simulation *) args;
    while(!sim->stopped)
    {    
        i = 0;
        pthread_mutex_lock(&sim->state_lock);
        while (i < sim->infos->number_of_coders)
        {
            if (get_time_fn() - sim->coders[i].last_compile_start <= sim->infos->time_to_burnout)
            {
                sim->stopped = 1;
                log_message(get_time_fn() - sim->start_time, sim->coders[i].id, "burned out");
                pthread_mutex_unlock(&sim->state_lock);
                pthread_cond_broadcast(&sim->state_cond);
                return NULL;
            }
            i++;
        }
        pthread_mutex_unlock(&sim->state_lock);
        // usleep(1000);
    }
    return NULL;
}   