/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheduler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:35:28 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/17 18:11:02 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_heap  *scheduler_init(t_simulation *sim)
{
    int i;
    t_heap *shceduler_heap;

    i = 0;
    shceduler_heap = malloc(sizeof(t_heap *));
    if (!shceduler_heap)
        return (NULL);
    heap_init(shceduler_heap, sim->infos->number_of_coders);
    for (i = 0; i < sim->infos->number_of_coders; i++)
    {
        shceduler_heap->data[i] = i + 1;
        shceduler_heap->size++;
    }
    return (shceduler_heap);
}
