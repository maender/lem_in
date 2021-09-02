/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:59 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:05:00 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	set_ite_p(t_ite *ite, t_ang *ang)
{
	ite->px[0] = ite->m1x;
	ite->px[1] = ite->m2x;
	ite->px[2] = ang->ml1bx;
	ite->px[3] = ang->ml2bx;
	ite->py[0] = ite->m1y;
	ite->py[1] = ite->m2y;
	ite->py[2] = ang->ml1by;
	ite->py[3] = ang->ml2by;
}

void
	set_murphy(t_murphy *m, t_ang *ang)
{
	m->last1x = ang->ml1x;
	m->last1y = ang->ml1y;
	m->last2x = ang->ml2x;
	m->last2y = ang->ml2y;
	m->first1x = ang->ml1bx;
	m->first1y = ang->ml1by;
	m->first2x = ang->ml2bx;
	m->first2y = ang->ml2by;
}

void
	ite_loop(t_env *env, t_bren *b, t_ite *ite, t_ang *ang)
{
	while (bren_ite(b) == 0)
		img_pixel_put(env, (t_point){.x = b->x, .y = b->y}, ang->clr);
	bren_init(b, (t_point){.x = ite->m1x, .y = ite->m1y},
			(t_point){.x = ang->ml1bx, .y = ang->ml1by});
	img_pixel_put(env, (t_point){.x = b->x, .y = b->y}, ang->clr);
	while (bren_ite(b) == 0)
		img_pixel_put(env, (t_point){.x = b->x, .y = b->y}, ang->clr);
	bren_init(b, (t_point){.x = ang->ml1bx, .y = ang->ml1by},
			(t_point){.x = ang->ml2bx, .y = ang->ml2by});
	img_pixel_put(env, (t_point){.x = b->x, .y = b->y}, ang->clr);
	while (bren_ite(b) == 0)
		img_pixel_put(env, (t_point){.x = b->x, .y = b->y}, ang->clr);
	bren_init(b, (t_point){.x = ang->ml2bx, .y = ang->ml2by},
			(t_point){.x = ite->m2x, .y = ite->m2y});
	img_pixel_put(env, (t_point){.x = b->x, .y = b->y}, ang->clr);
	while (bren_ite(b) == 0)
		img_pixel_put(env, (t_point){.x = b->x, .y = b->y}, ang->clr);
}

void
	bfs_helper(t_env *env, int *parent, size_t u, int v)
{
	parent[env->rooms[u].pipes.p[v]] = u;
	env->rooms[env->rooms[u].pipes.p[v]].clr = GREEN;
	if (env->vis)
		visu(env, 0);
}

void
	init_bfs(t_env *env, t_queue *q)
{
	if (!(q->q = (int*)ft_memalloc(INTS * (env->vert - 1))))
		die(env);
	q->len = 0;
	queue_push(q, env->source);
}
