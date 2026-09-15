/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:34:53 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/09 15:34:54 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    destroy_simulation(t_simulation *sim)
{
    int nbr;
    int i;

    i = 0;
    nbr = sim->infos->number_of_coders;
    if (sim->dongles)
    {
        while (i < nbr)
        {
            pthread_mutex_destroy(&sim->dongles[i].dongle_mut);
            pthread_cond_destroy(&sim->dongles[i].con_var);
            i++;
        }
        free(sim->dongles);
    }
    if (sim->coders)
        free(sim->coders);
    pthread_mutex_destroy(&sim->thread_creation_mutex);
    pthread_cond_destroy(&sim->thread_creation_cond);
    pthread_mutex_destroy(&sim->log_lock);
    pthread_mutex_destroy(&sim->state_lock);
    pthread_cond_destroy(&sim->state_cond);
    free(sim);
    return ;
}
