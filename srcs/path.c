/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:29 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:31 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	sort_paths(t_queue *paths, int flow)
{
	int		i;
	int		j;
	t_queue tmp;

	i = -1;
	while (++i < flow)
	{
		j = i;
		while (++j < flow)
		{
			if (paths[i].len > paths[j].len)
			{
				tmp = paths[i];
				paths[i] = paths[j];
				paths[j] = tmp;
			}
		}
	}
}

void
	path_from_pipe(t_env *env, size_t u, int flow)
{
	int i;

	queue_push_front(&env->paths[flow - 1][env->flow], env->sink);
	while ((int)u != env->source)
	{
		i = env->vert;
		queue_push_front(&env->paths[flow - 1][env->flow], u);
		while (--i >= 0)
		{
			if (env->rgraph[u][i] < 0)
			{
				u = i;
				break ;
			}
		}
	}
}

void
	paths_from_residual(t_env *env, int flow)
{
	int		u;
	int		i;

	i = -1;
	u = env->sink;
	env->flow = 0;
	while (++i < (int)env->vert)
	{
		if (env->rgraph[u][i] < 0)
		{
			if (!(env->paths[flow - 1][env->flow].q = (int*)
				malloc(INTS * (env->vert - 1))))
				die(env);
			env->paths[flow - 1][env->flow].len = 0;
			path_from_pipe(env, i, flow);
			env->flow++;
		}
	}
	sort_paths(env->paths[flow - 1], flow);
}
