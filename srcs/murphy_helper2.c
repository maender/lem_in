/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murphy_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:21 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:22 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	init_murphy(t_murphy *m, t_ang *ang, t_point *start, t_point *end)
{
	ang->off = 3.0f / 2.0f;
	m->u = end->x - start->x;
	m->v = end->y - start->y;
	if (m->u < 0)
	{
		ang->tmp = start->x;
		start->x = end->x;
		end->x = ang->tmp;
		ang->tmp = start->y;
		start->y = end->y;
		end->y = ang->tmp;
		m->u *= -1;
		m->v *= -1;
	}
	if (m->v < 0)
	{
		m->v *= -1;
		m->quad4 = 1;
	}
	else
		m->quad4 = 0;
	init_murphy_two(m, ang);
}

void
	check_oct(t_murphy *m, t_ang *ang, t_point *start)
{
	if (m->oct2 == 0)
	{
		ang->ptx = start->x + ((int)((ang->off + ang->sang) + 0.5));
		if (!m->quad4)
			ang->pty = start->y - ((int)((ang->off + ang->cang) + 0.5));
		else
			ang->pty = start->y + ((int)((ang->off + ang->cang) + 0.5));
	}
	else
	{
		ang->ptx = start->x - ((int)((ang->off + ang->cang) + 0.5));
		if (!m->quad4)
			ang->pty = start->y + ((int)((ang->off + ang->sang) + 0.5));
		else
			ang->pty = start->y - ((int)((ang->off + ang->sang) + 0.5));
	}
}

void
	murphy_helper_six(t_murphy *m, t_ang *ang)
{
	if (m->oct2 == 0)
	{
		if (m->quad4 == 0)
			ang->pty++;
		else
			ang->pty--;
	}
	else
		ang->ptx++;
}
