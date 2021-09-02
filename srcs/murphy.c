/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murphy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:13 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:14 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <math.h>

void
	m_ite(t_env *env, t_murphy *m, t_ang *ang, int clr)
{
	t_ite	ite;
	t_bren	b;

	if (env->iter > 1)
	{
		if (m->first1x != -32768)
		{
			init_ite(&ite, m, ang);
			continue_ite(&ite, m, ang);
			iterate_ite(&ite, ang);
			bren_init(&b, (t_point){.x = ite.m2x, .y = ite.m2y},
				(t_point){.x = ite.m1x, .y = ite.m1y});
			img_pixel_put(env, (t_point){.x = b.x, .y = b.y}, clr);
			ang->clr = clr;
			ite_loop(env, &b, &ite, ang);
			set_ite_p(&ite, ang);
		}
	}
	set_murphy(m, ang);
}

void
	m_par_helper(t_murphy *m, int *x, int *y, int *d1)
{
	if (*d1 <= m->kt)
	{
		if (m->oct2 == 0)
			*x += 1;
		else
		{
			if (m->quad4 == 0)
				*y += 1;
			else
				*y -= 1;
		}
		*d1 += m->kv;
	}
	else
	{
		*x += 1;
		if (m->quad4 == 0)
			*y += 1;
		else
			*y -= 1;
		*d1 += m->kd;
	}
}

void
	m_par(t_env *env, t_murphy *m, t_point pt, t_point p)
{
	int i;

	i = 0;
	p.x = -p.x;
	while (i <= m->u)
	{
		img_pixel_put(env, pt, p.y);
		m_par_helper(m, &pt.x, &pt.y, &p.x);
		++i;
	}
	m->tempx = pt.x;
	m->tempy = pt.y;
}

void
	init_murphy_two(t_murphy *m, t_ang *ang)
{
	if (m->v > m->u)
	{
		ang->tmp = m->u;
		m->u = m->v;
		m->v = ang->tmp;
		m->oct2 = 1;
	}
	else
		m->oct2 = 0;
	m->ku = m->u + m->u;
	m->kv = m->v + m->v;
	m->kd = m->kv - m->ku;
	m->kt = m->u - m->kv;
	ang->d0 = 0;
	ang->d1 = 0;
	ang->dd = 0;
	ang->ang = atan((double)m->v / (double)m->u);
	ang->sang = sin(ang->ang);
	ang->cang = cos(ang->ang);
}

void
	drawthickline(t_env *env, t_point start, t_point end, int clr)
{
	t_murphy	m;
	t_ang		ang;

	if (start.x == end.x && start.y == end.y)
		return ;
	init_murphy(&m, &ang, &start, &end);
	check_oct(&m, &ang, &start);
	murphy_helper_one(env, &m, &ang, &start);
	while (ang.dd <= m.tk)
	{
		m_par(env, &m, (t_point){.x = ang.ptx, .y = ang.pty},
			(t_point){.x = ang.d1, .y = clr});
		murphy_helper_two(&m, &ang);
		if (ang.d0 < m.kt)
			murphy_helper_six(&m, &ang);
		else
		{
			if (murphy_helper_three(env, &m, &ang, clr) == 0)
				return ;
		}
		ang.dd += m.ku;
		ang.d0 += m.kv;
	}
}
