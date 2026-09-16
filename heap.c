/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:42:24 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/16 22:38:35 by ybourajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_heap
{
	int	*data;
	int	size;
	int	capacity;
}	t_heap;

void	heap_init(t_heap *h, int capacity)
{
	h->size = 0;
	h->data = malloc(sizeof(int) * capacity);
	h->capacity = capacity;
}

int heap_insert(t_heap *h, int value)
{
	int	tmp;
	int	parrent;

	if (h->size == h->capacity)
		return (-1);
	h->data[h->size] = value;
	h->size++;
	int	i = h->size - 1;
	while (i > 0)
	{
		parrent = h->data[(i - 1) / 2];
		if (parrent > h->data[i])
		{
			tmp = h->data[(i - 1) / 2];
			h->data[(i - 1) / 2] = value;
			h->data[i] = tmp;
		}
		i = (i-1)/2;
	}
	return (0);
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

