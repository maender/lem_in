/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:05:06 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:05:07 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	rotate_ants(t_env *env, t_queue paths[])
{
	int i;

	i = -1;
	while (++i < env->flowmax)
		queue_rotate(&paths[i]);
}

void
	push_ants(t_env *env, t_queue paths[], int *ants, int step)
{
	int i;

	i = -1;
	while (++i < env->flowmax)
	{
		if (env->paths[env->flowmax - 1][i].tosend > step)
		{
			paths[i].q[0] = *ants;
			*ants += 1;
		}
		else
			paths[i].q[0] = 0;
	}
}

void
	calc_nite(t_env *env)
{
	int i;
	int j;
	int min;

	i = -1;
	min = 2147483647;
	while (++i < env->flowmax)
	{
		j = -1;
		while (++j < (int)(int)env->paths[env->flowmax - 1][i].len)
			if ((int)env->diff[i][j].count < min)
				min = env->diff[i][j].count;
	}
	i = -1;
	nite_helper(env, &min);
	while (++i < env->flowmax)
	{
		j = -1;
		while (++j < (int)(int)env->paths[env->flowmax - 1][i].len)
		{
			env->diff[i][j].n = env->diff[i][j].count / min;
			if ((env->diff[i][j].m = env->diff[i][j].count % min) > 0)
				env->diff[i][j].o = 1;
		}
	}
}

void
	calc_diff(t_env *env)
{
	t_point i;

	i.y = -1;
	while (++i.y < env->flowmax)
	{
		i.x = -1;
		while (++i.x < (int)env->paths[env->flowmax - 1][i.y].len)
		{
			if (!i.x)
				bren_init(&env->diff[i.y][i.x], (t_point){.x = env->rooms[
						env->source].x, .y = env->rooms[env->source].y},
							(t_point){.x = env->rooms[env->paths[
						env->flowmax - 1][i.y].q[i.x]].x, .y = env->rooms
							[env->paths[env->flowmax - 1][i.y].q[i.x]].y});
			else
				bren_init(&env->diff[i.y][i.x], (t_point){.x = env->rooms[
						env->paths[env->flowmax - 1][i.y].q[i.x - 1]].x,
						.y = env->rooms[env->paths[env->flowmax - 1][i.y].q[
							i.x - 1]].y}, (t_point){.x = env->rooms[
						env->paths[env->flowmax - 1][i.y].q[i.x]].x,
						.y = env->rooms[env->paths[
							env->flowmax - 1][i.y].q[i.x]].y});
		}
	}
	calc_nite(env);
}

int
	all_done(t_env *env, t_queue paths[])
{
	t_point i;
	int		k;
	int		out;

	i.y = -1;
	out = 1;
	if (paths == NULL)
		return ((out = bren_ite(&env->diff[0][0])));
	while (++i.y < env->flowmax)
	{
		i.x = -1;
		while (++i.x < (int)paths[i.y].len)
		{
			if ((k = -1) && paths[i.y].q[i.x] > 0)
			{
				while (++k < (int)(env->diff[i.y][i.x].n
						+ env->diff[i.y][i.x].o))
					if (bren_ite(&env->diff[i.y][i.x]) == 0)
						out = 0;
				if (--env->diff[i.y][i.x].m <= 0)
					env->diff[i.y][i.x].o = 0;
			}
		}
	}
	return (out);
}
