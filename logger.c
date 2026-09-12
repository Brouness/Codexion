/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:19 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/09 15:35:20 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    *thread_loging(void *args)
{
    t_coder *thread;
    int id;
    long    current_time;
    int     number_of_compile;

    number_of_compile = 0;
    thread = (t_coder *) args;
    id = thread->id;
    while(number_of_compile < thread->sim->infos->number_of_compiles_required)
    {    
        pthread_mutex_lock(&thread->sim->log_lock);
        current_time = get_time_fn() - thread->sim->start_time;
        printf("%ld %d has taken a dongle\n", current_time, thread->id);
        current_time = get_time_fn() - thread->sim->start_time;
        printf("%ld %d is compiling\n", current_time, id);
        usleep(thread->sim->infos->time_to_compile * 10000);
        current_time = get_time_fn() - thread->sim->start_time;
        printf("%ld %d is debugging\n", current_time, id);
        usleep(thread->sim->infos->time_to_debug * 10000);
        current_time = get_time_fn() - thread->sim->start_time;
        printf("%ld %d is refactoring\n", current_time, id);
        usleep(thread->sim->infos->time_to_refactor * 10000);
        pthread_mutex_unlock(&thread->sim->log_lock);
        number_of_compile++;
    }
    return NULL;
}
