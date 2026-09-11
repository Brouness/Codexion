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

    thread = (t_coder *) args;
    id = thread->id;
    pthread_mutex_lock(&thread->last_compile_start_mut);
    current_time = get_time_fn();
    printf("%ld %d has taken a dongle\n", current_time, thread->id);
    pthread_mutex_lock(&thread->left_dongle->dongle_mut);
    current_time = get_time_fn();
    printf("%ld %d is compiling\n", current_time, id);
    pthread_mutex_unlock(&thread->left_dongle->dongle_mut);
    current_time = get_time_fn();
    printf("%ld %d is debugging\n", current_time, id);
    current_time = get_time_fn();
    printf("%ld %d is refactoring\n", current_time, id);
    pthread_mutex_unlock(&thread->last_compile_start_mut);
    return NULL;
}
