/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murphy_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:17 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:19 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <math.h>

void
	murphy_helper_one(t_env *env, t_murphy *m, t_ang *ang, t_point *start)
{
	m->tk = (int)(4. * sqrt((double)(ang->ptx - start->x) * (double)
				(ang->ptx - start->x) + (double)(ang->pty - start->y)
				* (double)(ang->pty - start->y)) * sqrt(
				(double)(m->u) * (double)(m->u) + (double)(m->v)
				* (double)(m->v)));
	if (env->iter == 0)
	{
		m->first1x = -32768;
		m->first1y = -32768;
		m->first2x = -32768;
		m->first2y = -32768;
		m->last1x = -32768;
		m->last1y = -32768;
		m->last2x = -32768;
		m->last2y = -32768;
	}
	ang->ptxx = ang->ptx;
	ang->ptyy = ang->pty;
	ang->q = 0;
}

void
	murphy_helper_two(t_murphy *m, t_ang *ang)
{
	if (ang->q == 0)
	{
		ang->ml1x = ang->ptx;
		ang->ml1y = ang->pty;
		ang->ml1bx = m->tempx;
		ang->ml1by = m->tempy;
	}
	else
	{
		ang->ml2x = ang->ptx;
		ang->ml2y = ang->pty;
		ang->ml2bx = m->tempx;
		ang->ml2by = m->tempy;
	}
}

void
	murphy_helper_four(t_murphy *m, t_ang *ang)
{
	if (m->oct2 == 0)
	{
		ang->ptx--;
		if (m->quad4 == 0)
			ang->pty++;
		else
			ang->pty--;
	}
	else
	{
		ang->ptx++;
		if (m->quad4 == 0)
			ang->pty--;
		else
			ang->pty++;
	}
	ang->d1 += m->kv;
}

void
	murphy_helper_five(t_murphy *m, t_ang *ang)
{
	if (m->oct2 == 0)
		ang->ptx--;
	else
	{
		if (m->quad4 == 0)
			ang->pty--;
		else
			ang->pty++;
	}
	ang->d1 += m->kd;
}

int
	murphy_helper_three(t_env *env, t_murphy *m, t_ang *ang, int clr)
{
	ang->dd += m->kv;
	ang->d0 -= m->ku;
	if (ang->d1 < m->kt)
		murphy_helper_four(m, ang);
	else
	{
		murphy_helper_five(m, ang);
		if (ang->dd > m->tk)
		{
			m_ite(env, m, ang, clr);
			return (0);
		}
		m_par(env, m, (t_point){.x = ang->ptx, .y = ang->pty},
			(t_point){.x = ang->d1, .y = clr});
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
	return (1);
}
