/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:42:24 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/19 23:30:19 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "codexion.h"

// t_heap	*heap_init(int capacity)
// {
// 	t_heap	*h;

// 	h = (t_heap *)malloc(sizeof(t_heap));
// 	h->queue = (t_queue_node *)malloc(sizeof(t_queue_node) * capacity);
// 	h->capacity = capacity;
// 	h->size = 0;
// 	return (h);
// }

// static void	swap(t_queue_node *shild, t_queue_node *parent)
// {
// 	t_queue_node	tmp;

// 	tmp = *parent;
// 	*parent = *shild;
// 	*shild = tmp;
// }

// int	heap_insert(t_heap *h, t_queue_node node)
// {
// 	int	parent;
// 	int	i;

// 	i = h->size;
// 	if (h->size == h->capacity)
// 		return (-1);
// 	h->queue[h->size] = node;
// 	h->size++;
// 	while (i > 0)
// 	{
// 		parent = (i - 1) / 2;
// 		if (h->queue[i].priority_s < h->queue[parent].priority_s)
// 			swap(&h->queue[i], &h->queue[parent]);
// 		else
// 			break ;
// 		i = parent;
// 	}
// 	return (0);
// }

// void	heap_extract_min(t_heap *h, t_queue_node *node)
// {
// 	int	i;
// 	int	l;
// 	int	r;
// 	int	s;

// 	if (h->size == 0 || h->capacity == 0)
// 		return ;
// 	h->size--;
// 	*node = h->queue[0];
// 	i = 0;
// 	h->queue[0] = h->queue[h->size];
// 	while (1)
// 	{
// 		l = (i * 2) + 1;
// 		r = (i * 2) + 2;
// 		s = i;
// 		if (l < h->size && h->queue[s].priority_s > h->queue[l].priority_s)
// 			s = l;
// 		if (r < h->size && h->queue[s].priority_s > h->queue[r].priority_s)
// 			s = r;
// 		if (s == i)
// 			break ;
// 		swap(&h->queue[i], &h->queue[s]);
// 		i = s;
// 	}
// }

// void	heap_destroy(t_heap *h)
// {
// 	free(h->queue);
// 	free(h);
// }
#include "codexion.h"

t_heap  *heap_init(int capacity)
{
    t_heap  *h;

    h = (t_heap *)malloc(sizeof(t_heap));
    if (!h)
        return (NULL);
    h->queue = (t_queue_node *)malloc(sizeof(t_queue_node) * capacity);
    if (!h->queue)
    {
        free(h);
        return (NULL);
    }
    h->capacity = capacity;
    h->size = 0;
    return (h);
}

static void swap(t_queue_node *child, t_queue_node *parent)
{
    t_queue_node    tmp;

    tmp = *parent;
    *parent = *child;
    *child = tmp;
}

int heap_insert(t_heap *h, t_queue_node node)
{
    int parent;
    int i;

    if (h->size == h->capacity)
        return (-1);
    i = h->size;
    h->queue[i] = node;
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

static void heapify_down(t_heap *h, int idx)
{
    int l;
    int r;
    int s;

    while (1)
    {
        l = (idx * 2) + 1;
        r = (idx * 2) + 2;
        s = idx;
        if (l < h->size && h->queue[l].priority_s < h->queue[s].priority_s)
            s = l;
        if (r < h->size && h->queue[r].priority_s < h->queue[s].priority_s)
            s = r;
        if (s == idx)
            break ;
        swap(&h->queue[idx], &h->queue[s]);
        idx = s;
    }
}

void heap_extract_min(t_heap *h, t_queue_node *node)
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

void heap_remove_by_id(t_heap *h, int coder_id)
{
    int i;

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

void heap_destroy(t_heap *h)
{
    if (h)
    {
        free(h->queue);
        free(h);
    }
}
