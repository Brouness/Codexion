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
    thread = (t_coder *) args;
    id = thread->id;
    pthread_mutex_lock(&thread->sim->log_lock);
    printf("Coder id: %d Start login\n", thread->id);
    pthread_mutex_lock(&thread->left_dongle->dongle_mut);
    printf("Coder id: %d is locking dongle id: %d\n", id, thread->left_dongle->dongle_id);
    pthread_mutex_unlock(&thread->left_dongle->dongle_mut);
    printf("Coder release dongle id %d\n", thread->left_dongle->dongle_id);
    pthread_mutex_unlock(&thread->sim->log_lock);
    return NULL;
}