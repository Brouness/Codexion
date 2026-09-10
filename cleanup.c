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
    pthread_mutex_destroy(&sim->log_lock);
    pthread_mutex_destroy(&sim->state_lock);
    pthread_cond_destroy(&sim->state_cond);
    free(sim);
    return ;
}
