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

t_data_needed	*init(t_args *args)
{
    t_data_needed    data;

    data.args = args;
    data.coders = malloc(sizeof(pthread_t) * args->number_of_coders);
    if (!data.coders)
    {
        free(data.coders);
        return 0;
    }
    return (&data);
}
