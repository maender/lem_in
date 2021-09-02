/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:48 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:49 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int
	pipe_helper(t_env *env, int *parent, size_t a, int i)
{
	env->from = (int)a == env->source ? 0 : env->rgraph[parent[a]][a];
	if ((env->rooms[a].pipes.len == 2 && parent[env->rooms[a].pipes.p[i]]
			== -1) || (env->rooms[a].pipes.p[i] == env->sink
			&& env->rgraph[a][env->rooms[a].pipes.p[i]] < 1))
		return (1);
	return (0);
}

int
	is_pipe_worth(t_env *env, int *parent, size_t a, int i)
{
	int j;
	int pos;

	j = -1;
	pos = 0;
	if (env->rgraph[a][env->rooms[a].pipes.p[i]] > 0
		|| parent[env->rooms[a].pipes.p[i]] != -1)
		return (0);
	if (pipe_helper(env, parent, a, i))
		return (1);
	while (++j < (int)env->rooms[a].pipes.len)
	{
		if (i != j)
		{
			if (env->from == 0 && env->rgraph[a][env->rooms[a].pipes.p[j]]
				< 0 && env->rooms[a].pipes.p[j] != env->source)
				return (0);
			else if (env->rgraph[a][env->rooms[a].pipes.p[j]] > 0)
				pos = 1;
		}
	}
	if (env->from == 0 && (int)a != env->source && pos
		&& env->rgraph[a][env->rooms[a].pipes.p[i]] >= 0)
		return (0);
	return (1);
}

t_bool
	beufeuseu(t_env *env, int *parent)
{
	t_queue	q;
	size_t	u;
	int		v;

	init_bfs(env, &q);
	while (q.len > 0)
	{
		bfs_uv(&u, &v, &q);
		while (++v < (int)env->rooms[u].pipes.len)
		{
			if (is_pipe_worth(env, parent, u, v))
			{
				bfs_helper(env, parent, u, v);
				if (env->rooms[u].pipes.p[v] != env->sink)
					queue_push_front(&q, env->rooms[u].pipes.p[v]);
				else
				{
					ft_memdel((void**)&q.q);
					return (1);
				}
			}
		}
	}
	ft_memdel((void**)&q.q);
	return (0);
}

int
	is_set_worth(t_env *env, int flow)
{
	int		i;
	int		nb_paths;
	int		total_len;
	int		meanlen;
	int		mod;

	total_len = 0;
	nb_paths = -1;
	while (++nb_paths < flow + 1)
		total_len += env->paths[flow][nb_paths].len;
	meanlen = (env->ant + total_len) / nb_paths;
	mod = (env->ant + total_len) % nb_paths;
	i = -1;
	while (++i < flow + 1)
	{
		if ((env->paths[flow][i].tosend = meanlen - env->paths[flow][i].len
			+ (mod > 0)) <= 0)
			return (0);
		mod--;
	}
	return (1);
}

int
	saumon_fume(t_env *env)
{
	int		u;
	int		v;
	int		*parent;

	u = -1;
	parent = NULL;
	karp_loop(env, &parent, &u, &v);
	while (env->flowmax < (int)env->ant)
	{
		ft_memset(parent, -1, INTS * env->vert);
		parent[env->source] = -2;
		if (!(beufeuseu(env, parent)))
			break ;
		karp_helper(env, parent, &u, &v);
		if (!(env->paths[env->flowmax - 1
				] = (t_queue*)malloc(QS * env->flowmax)))
			die(env);
		paths_from_residual(env, env->flowmax);
		if ((env->flowmax == 1 && env->paths[0][0].len == 1)
			|| (!is_set_worth(env, env->flowmax - 1)
				&& env->flowmax-- > -1))
			break ;
	}
	ft_memdel((void**)&parent);
	return (env->flowmax);
}
