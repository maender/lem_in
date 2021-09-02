/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bren.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:03:46 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:12:58 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int
	bren_init(t_bren *b, t_point start, t_point end)
{
	if (b == NULL)
		return (-1);
	bren_helperone(b, start.x, end.x, start.y);
	if ((b->dy = end.y - start.y) != 0)
	{
		if (b->dy < 0)
		{
			b->dy *= -1;
			b->s2 = -1;
		}
		else
			b->s2 = 1;
	}
	else
		b->s2 = 0;
	bren_helpertwo(b);
	b->o = 0;
	return (0);
}

int
	bren_ite(t_bren *b)
{
	if (b == NULL)
		return (-1);
	if (b->count == 0)
		return (-2);
	while (b->error >= 0)
	{
		if (b->swapdir)
			b->x += b->s1;
		else
			b->y += b->s2;
		b->error -= b->dx;
	}
	if (b->swapdir)
		b->y += b->s2;
	else
		b->x += b->s1;
	b->error += b->dy;
	b->count--;
	return ((b->count) ? 0 : 1);
}
