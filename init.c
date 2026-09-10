/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:15 by ybourajl          #+#    #+#             */
/*   Updated: 2026/07/12 10:14:46 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int init_dongles(t_simulation *sim)
{
    int nbr;
    int i;

    nbr = sim->infos->number_of_coders;
    i = 0;
    sim->dongles = malloc(sizeof(t_dongle) * nbr);
    if (!sim->dongles)
        return (-1);
    while (i < nbr)
    {
        sim->dongles[i].is_held = 0;
        sim->dongles[i].dongle_id = i + 1;
        sim->dongles[i].available_at_ms = 0;
        if (pthread_mutex_init(&sim->dongles[i].dongle_mut, NULL) != 0)
            break;
        if (pthread_cond_init(&sim->dongles[i].con_var, NULL) != 0)
        {
            pthread_mutex_destroy(&sim->dongles[i].con_var);
            break;
        }
        i++;
    }
    if (i < nbr)
    {
        while(i-- > 0)
        {
            pthread_mutex_destroy(&sim->dongles[i].dongle_mut);
            pthread_cond_destroy(&sim->dongles[i].con_var);
        }
        free(sim->dongles);
        return (-1);
    }
    return (0);
}

int init_coders(t_simulation *sim)
{
    int nbr;
    int i;

    nbr = sim->infos->number_of_coders;
    i = 0;
    sim->coders = malloc(sizeof(t_coder) * nbr);
    if (!sim->coders)
        return (-1);
    while (i < nbr)
    {
        sim->coders[i].id = i + 1;
        sim->coders[i].compile_done = 0;
        sim->coders[i].last_compile_start = 0;
        sim->coders[i].right_dongle = &sim->dongles[i];
        sim->coders[i].left_dongle = &sim->dongles[(i - 1 + nbr) % nbr];
        sim->coders[i].sim = sim;
        i++;
    }
    return (0);
}