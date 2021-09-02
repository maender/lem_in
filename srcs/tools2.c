/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:56 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:57 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	bren_helperone(t_bren *b, int x1, int x2, int y1)
{
	b->x = x1;
	b->y = y1;
	if ((b->dx = x2 - x1) != 0)
	{
		if (b->dx < 0)
		{
			b->dx *= -1;
			b->s1 = -1;
		}
		else
			b->s1 = 1;
	}
	else
		b->s1 = 0;
}

void
	bren_helpertwo(t_bren *b)
{
	int tmp;

	if (b->dy > b->dx)
	{
		tmp = b->dx;
		b->dx = b->dy;
		b->dy = tmp;
		b->swapdir = 1;
	}
	else
		b->swapdir = 0;
	b->count = (b->dx < 0) ? 0 : (unsigned int)b->dx;
	b->dy <<= 1;
	b->error = b->dy - b->dx;
	b->dx <<= 1;
}

void
	init_ite(t_ite *ite, t_murphy *m, t_ang *ang)
{
	ite->fix = (m->first1x + m->first2x) / 2;
	ite->fiy = (m->first1y + m->first2y) / 2;
	ite->lax = (m->last1x + m->last2x) / 2;
	ite->lay = (m->last1y + m->last2y) / 2;
	ite->curx = (ang->ml1x + ang->ml2x) / 2;
	ite->cury = (ang->ml1y + ang->ml2y) / 2;
	ite->atemp1 = (ite->fix - ite->curx);
	ite->atemp2 = (ite->fiy - ite->cury);
	ite->ftmp1 = ite->atemp1 * ite->atemp1 + ite->atemp2 * ite->atemp2;
	ite->atemp1 = (ite->lax - ite->curx);
	ite->atemp2 = (ite->lay - ite->cury);
	ite->ftmp2 = ite->atemp1 * ite->atemp1 + ite->atemp2 * ite->atemp2;
}

void
	continue_ite(t_ite *ite, t_murphy *m, t_ang *ang)
{
	if (ite->ftmp1 <= ite->ftmp2)
	{
		ite->m1x = m->first1x;
		ite->m1y = m->first1y;
		ite->m2x = m->first2x;
		ite->m2y = m->first2y;
	}
	else
	{
		ite->m1x = m->last1x;
		ite->m1y = m->last1y;
		ite->m2x = m->last2x;
		ite->m2y = m->last2y;
	}
	ite->atemp1 = (ite->m2x - ang->ml2x);
	ite->atemp2 = (ite->m2y - ang->ml2y);
	ite->ftmp1 = ite->atemp1 * ite->atemp1 + ite->atemp2 * ite->atemp2;
	ite->atemp1 = (ite->m2x - ang->ml2bx);
	ite->atemp2 = (ite->m2y - ang->ml2by);
	ite->ftmp2 = ite->atemp1 * ite->atemp1 + ite->atemp2 * ite->atemp2;
}

void
	iterate_ite(t_ite *ite, t_ang *ang)
{
	if (ite->ftmp2 >= ite->ftmp1)
	{
		ite->ftmp1 = ang->ml2bx;
		ite->ftmp2 = ang->ml2by;
		ang->ml2bx = ang->ml2x;
		ang->ml2by = ang->ml2y;
		ang->ml2x = ite->ftmp1;
		ang->ml2y = ite->ftmp2;
		ite->ftmp1 = ang->ml1bx;
		ite->ftmp2 = ang->ml1by;
		ang->ml1bx = ang->ml1x;
		ang->ml1by = ang->ml1y;
		ang->ml1x = ite->ftmp1;
		ang->ml1y = ite->ftmp2;
	}
}
