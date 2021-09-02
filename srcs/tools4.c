/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:05:02 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:05:04 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	bfs_uv(size_t *u, int *v, t_queue *q)
{
	*u = queue_pop(q);
	*v = -1;
}

void
	karp_helper(t_env *env, int *parent, int *u, int *v)
{
	*v = env->sink;
	while (*v != (int)env->source)
	{
		*u = parent[*v];
		env->rgraph[*u][*v]++;
		env->rgraph[*v][*u]--;
		*v = *u;
	}
	env->flowmax++;
	if (env->vis)
	{
		reset_clr(env);
		visu(env, 0);
	}
}

void
	karp_loop(t_env *env, int **parent, int *u, int *v)
{
	if (!(env->paths = (t_queue**)ft_memalloc(sizeof(t_queue*) * (env->vert))))
		die(env);
	malloc_matrix(env, &env->rgraph, env->vert);
	if (!(*parent = (int*)malloc(INTS * env->vert)))
		die(env);
	while (++(*u) < (int)env->vert)
	{
		*v = -1;
		while (++(*v) < (int)env->vert)
			env->rgraph[*u][*v] = 0;
	}
	env->flowmax = 0;
}
