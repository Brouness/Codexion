/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourajl <ybourajl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:42:24 by ybourajl          #+#    #+#             */
/*   Updated: 2026/09/15 22:50:23 by ybourajl         ###   ########.fr       */
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
	h = malloc(sizeof(t_heap));
	h->size = 0;
	h->data = malloc(sizeof(int) * capacity);
	h->capacity = capacity;
}

int heap_insert(t_heap *h, int value)
{
	int	tmp;

	if (h->size == h->capacity)
		return (-1);
	h->data[h->size] = value;
	h->size++;
	int	i = h->size;
	while (i >= 0)
	{
		int var = h->data[(i - 1) / 2];
		if (var > value)
		{
			tmp = h->data[(i - 1) / 2];
			h->data[(i - 1) / 2] = value;
			h->data[i] = tmp;
		}
		i = (i-1)/2;
	}
}

int	heap_extract_min(t_heap *h, int *out)
{
	
}
