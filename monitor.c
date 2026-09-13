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

void    monitor_routine(void *args)
{
    t_simulation    *sim;

    sim = (t_simulation *) args;
    while (sim->stopped == 0)
        pthread_cond_wait(&sim->state_cond);
    
}