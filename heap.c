/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:42:24 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/17 16:31:54 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void	heap_init(t_heap *h, int capacity)
{
	h->size = 0;
	h->data = (int*)malloc(sizeof(int) * capacity);
	h->capacity = capacity;
}

void	swap(int *shild, int *parent)
{
	int	tmp;

	tmp = *parent;
	*parent = *shild;
	*shild =  tmp;
}

int	heap_insert(t_heap *h, int value)
{
	int	parent;
	int	i;

	i = h->size;
	if (h->size == h->capacity)
		return (-1);
	h->data[h->size] = value;
	h->size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (h->data[i] < h->data[parent])
			swap(&h->data[i], &h->data[parent]);
		i = parent;
	}
	return (0);
}

int	heap_extract_min(t_heap *h, int	*out)
{
	int	i;

	if (h->size == 0 || h->capacity == 0)
		return (-1);
	h->size--;
	*out = h->data[0];
	i = 0;
	h->data[0] = h->data[h->size];
	while (1)
	{
		if ((i * 2) + 1 < h->size && h->data[i] > h->data[(i * 2) + 1])
		{
			swap(&h->data[i], &h->data[(i * 2) + 1]);
			i = (i * 2) + 1;
		}
		if ((i * 2) + 2 < h->size && h->data[i] > h->data[(i * 2) + 2])
		{
			swap(&h->data[i], &h->data[(i * 2) + 2]);
			i = (i * 2) + 2;
		}
		if (!((i * 2) + 1 < h->size && h->data[i] > h->data[(i * 2) + 1]) &&
		 !((i * 2) + 2 < h->size && h->data[i] > h->data[(i * 2) + 2]))
			break;
	}
	return (*out);
}

void	heap_destroy(t_heap *h)
{
	free(h->data);
	free(h);
}

// int main()
// {
// 	int i = 0;
// 	int c = 10;
// 	printf("this is i before [i = %d] | this is c before [c = %d]\n", i, c);
// 	swap(&i, &c);
// 	printf("this is i after [i = %d] | this is c after [c = %d]\n", i, c);
// 	t_heap *heap = (t_heap *)malloc(sizeof(t_heap));
// 	swap(&i, &c);
// 	heap_init(heap, 6);
// 	while (i < 6)
// 	{
// 		heap_insert(heap, i + 10);
// 		i++;
// 	}
// 	i = 0;int *out;
// 	printf("debug\n");
// 	int x = heap_extract_min(heap, out);
// 	printf("THIS IS X %d\n", x);
// 	for (i = 0; i < 6; i++)
// 	{
// 		printf("THIS IS INDEX %d in heap: %d\n", i, heap->data[i]);
// 	}
// 	return (0);	
// }
