/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:42:24 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/17 09:00:05 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

typedef struct s_heap
{
	int	*data;
	int	size;
	int	capacity;
}	t_heap;

void	heap_init(t_heap *h, int capacity)
{
	h->size = 0;
	h->data = (int*)malloc(sizeof(int) * capacity);
	h->capacity = capacity;
}

void	swap(int *shild, int *parent)
{
	int	*tmp;

	tmp = parent;
	*parent = *shild;
	*shild =  *tmp;
}

void	heap_insert(t_heap *h, int value)
{
	int	i;
	int	parent;

	i = h->size;
	h->data[i] = value;
	h->size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (h->data[i] < h->data[parent])
			swap(&h->data[i], &h->data[parent]);
		i = (i - 1) / 2;
	}
}

int	heap_extract_min(t_heap *h, int *out)
{
	int	i;
	int tmp;

	i = h->size;
	if (h->size == 0)
		return (-1);
	*out = h->data[0];
	h->data[0] = h->data[h->size - 1];
	h->size--;
	while ((i * 2) + 1 < h->size)
	{
		if ((i * 2) + 1 <= h->size && h->data[i] > h->data[(i * 2) + 1])
		{
			tmp = h->data[i];
			h->data[i] = h->data[(i * 2) + 1];
			h->data[(i * 2) + 1] = tmp;
			i = (i * 2) + 1;
		}
		if ((i * 2) + 2 <= h->size && h->data[i] > h->data[(i * 2) + 2])
		{
			tmp = h->data[i];
			h->data[i] = h->data[(i * 2) + 2];
			h->data[(i * 1) + 2] = tmp;
			i = (i * 2) + 2;
		}
		i++;
	}
	return (0);
}

void	heap_destroy(t_heap *h)
{
	free(h->data);
	free(h);
}

int main()
{
	int i = 0;
	t_heap *heap = (t_heap *)malloc(sizeof(t_heap));;
	heap_init(heap, 6);
	while (i++ < 6)
		heap_insert(heap, i + 10);
	i = 0;
	printf("debug\n");
	for (i = 0; i < 6; i++)
	{
		printf("THIS IS INDEX %d in heap: %d\n", i, heap->data[i]);
	}
	return (0);	
}