/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:40 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:42 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t
	queue_pop(t_queue *queue)
{
	if (queue->len > 0)
		queue->len--;
	return (queue->q[queue->len]);
}

size_t
	queue_pop_front(t_queue *queue)
{
	size_t	out;
	int		i;

	i = -1;
	out = queue->q[0];
	if (queue->len > 0)
		queue->len--;
	while (++i < (int)queue->len)
		queue->q[i] = queue->q[i + 1];
	return (out);
}

void
	queue_push(t_queue *queue, int v)
{
	queue->len++;
	queue->q[queue->len - 1] = (int)v;
}

void
	queue_push_front(t_queue *q, int u)
{
	int i;

	q->len++;
	i = q->len;
	while (--i > 0)
		q->q[i] = q->q[i - 1];
	q->q[0] = u;
}

void
	queue_rotate(t_queue *q)
{
	int i;

	i = q->len - 1;
	while (--i >= 0)
		q->q[i + 1] = q->q[i];
	q->q[0] = 0;
}
