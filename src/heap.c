/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:42:24 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/21 21:23:59 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	swap(t_queue_node *child, t_queue_node *parent)
{
	t_queue_node	tmp;

	tmp = *parent;
	*parent = *child;
	*child = tmp;
}

int	heap_insert(t_heap *h, t_queue_node node)
{
	int	parent;
	int	i;

	if (h->size == h->capacity)
		return (-1);
	i = h->size;
	h->queue[i] = node;
	h->size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (choose(&h->queue[i], &h->queue[parent]))
			swap(&h->queue[i], &h->queue[parent]);
		else
			break ;
		i = parent;
	}
	return (0);
}

static void	heapify_down(t_heap *h, int idx)
{
	int	l;
	int	r;
	int	s;

	while (1)
	{
		l = (idx * 2) + 1;
		r = (idx * 2) + 2;
		s = idx;
		if (l < h->size && choose(&h->queue[l], &h->queue[s]))
			s = l;
		if (r < h->size && h->queue[r].priority_s < h->queue[s].priority_s)
			s = r;
		if (s == idx)
			break ;
		swap(&h->queue[idx], &h->queue[s]);
		idx = s;
	}
}

void	heap_extract_min(t_heap *h, t_queue_node *node)
{
	if (h->size == 0)
		return ;
	h->size--;
	*node = h->queue[0];
	if (h->size > 0)
	{
		h->queue[0] = h->queue[h->size];
		heapify_down(h, 0);
	}
}

void	heap_remove_by_id(t_heap *h, int coder_id)
{
	int	i;

	i = 0;
	while (i < h->size)
	{
		if (h->queue[i].coder_id == coder_id)
		{
			h->size--;
			if (i < h->size)
			{
				h->queue[i] = h->queue[h->size];
				heapify_down(h, i);
			}
			break ;
		}
		i++;
	}
}
