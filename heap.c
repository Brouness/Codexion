/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:42:24 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/19 10:42:24 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_heap	*heap_init(int capacity)
{
	t_heap	*h;

	h = (t_heap *)malloc(sizeof(t_heap));
	h->queue = (t_queue_node *)malloc(sizeof(t_queue_node) * capacity);
	h->capacity = capacity;
	h->size = 0;
	return (h);
}

static void	swap(t_queue_node *shild, t_queue_node *parent)
{
	t_queue_node	tmp;

	tmp = *parent;
	*parent = *shild;
	*shild = tmp;
}

int	heap_insert(t_heap *h, t_queue_node node)
{
	int	parent;
	int	i;

	i = h->size;
	if (h->size == h->capacity)
		return (-1);
	h->queue[h->size] = node;
	h->size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (h->queue[i].priority_s < h->queue[parent].priority_s)
			swap(&h->queue[i], &h->queue[parent]);
		else
			break ;
		i = parent;
	}
	return (0);
}

void	heap_extract_min(t_heap *h, t_queue_node *node)
{
	int	i;
	int	l;
	int	r;
	int	s;

	if (h->size == 0 || h->capacity == 0)
		return ;
	h->size--;
	*node = h->queue[0];
	i = 0;
	h->queue[0] = h->queue[h->size];
	while (1)
	{
		l = (i * 2) + 1;
		r = (i * 2) + 2;
		s = i;
		if (l < h->size && h->queue[s].priority_s > h->queue[l].priority_s)
			s = l;
		if (r < h->size && h->queue[s].priority_s > h->queue[r].priority_s)
			s = r;
		if (s == i)
			break ;
		swap(&h->queue[i], &h->queue[s]);
		i = s;
	}
}

void	heap_destroy(t_heap *h)
{
	free(h->queue);
	free(h);
}
