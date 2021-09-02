/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:05:09 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:05:11 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	malloc_matrix(t_env *env, char ***matrix, size_t x)
{
	size_t i;

	i = 0;
	if (!(matrix[0] = (char**)malloc(CHARPS * x)))
		die(env);
	while (i < x)
	{
		if (!(matrix[0][i] = (char*)malloc(CHARS * x)))
			die(env);
		ft_bzero(matrix[0][i], x);
		i++;
	}
}

void
	malloc_graph(t_env *env)
{
	int i;

	i = -1;
	if (!(env->graph = (char**)malloc(BPS * env->vert)))
		die(env);
	if (!(env->rooms = (t_room*)malloc(ROOMS * env->vert)))
		die(env);
	while (++i < (int)env->vert)
	{
		if (!(env->graph[i] = (char*)malloc(BS * env->vert)))
			die(env);
		ft_bzero(env->graph[i], env->vert);
	}
}

void
	init_pos(t_env *env, t_fpoint ants[env->flowmax][env->vert - 1],
		t_queue paths[])
{
	int i;
	int j;

	i = -1;
	while (++i < env->flowmax)
	{
		j = -1;
		while (++j < (int)env->paths[env->flowmax - 1][i].len)
		{
			if (!j)
			{
				ants[i][j].x = paths[i].q[j] > 0 ? env->rooms[
					env->source].x : -1;
				ants[i][j].y = paths[i].q[j] > 0 ? env->rooms[
					env->source].y : -1;
			}
			else
			{
				ants[i][j].x = paths[i].q[j] > 0 ? env->rooms[
					env->paths[env->flowmax - 1][i].q[j - 1]].x : -1;
				ants[i][j].y = paths[i].q[j] > 0 ? env->rooms[
					env->paths[env->flowmax - 1][i].q[j - 1]].y : -1;
			}
		}
	}
}

void
	nite_helper(t_env *env, int *min)
{
	if (SPEED < *min)
		env->v.minb = SPEED;
	else
		env->v.minb = *min;
	*min = env->v.minb;
}

int
	check_exist(t_env *env)
{
	int	i;

	i = -1;
	while (++i < (int)env->vert)
	{
		if (!ft_strcmp(env->rooms[env->vert].name, env->rooms[i].name))
			return (1);
	}
	return (0);
}
