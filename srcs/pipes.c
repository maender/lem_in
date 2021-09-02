/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:14:49 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:17:13 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	malloc_pipe(t_env *env, int i)
{
	if (!(env->rooms[i].pipes.p = ft_memalloc(INTS * (env->vert - 1))))
		die(env);
	ft_memset(env->rooms[i].pipes.p, -1, INTS * (env->vert - 1));
}

static int
	set_pipe(t_env *env, char *str, t_point i, int j)
{
	if (env->graph[i.x][i.y])
		return (0);
	env->graph[i.x][i.y] = 1;
	env->graph[i.y][i.x] = 1;
	if (!env->rooms[i.x].pipes.p)
		malloc_pipe(env, i.x);
	if (!env->rooms[i.y].pipes.p)
		malloc_pipe(env, i.y);
	env->rooms[i.x].pipes.p[env->rooms[i.x].pipes.len++] = i.y;
	env->rooms[i.y].pipes.p[env->rooms[i.y].pipes.len++] = i.x;
	if ((i.y >= (int)env->vert || *(str + j
				+ ft_strlen(env->rooms[i.y].name)) != '\0'))
		return (0);
	return (1);
}

int
	check_pipes(t_env *env, char *str, t_point *i, int *j)
{
	while (++i->x < (int)env->vert)
		if (str[*j] && !ft_strncmp(str, env->rooms[i->x].name,
				ft_strlen(env->rooms[i->x].name))
			&& str[*j + ft_strlen(env->rooms[i->x].name)] == '-')
			break ;
	if (!env->rooms[i->x].name
		|| str[*j + ft_strlen(env->rooms[i->x].name)] != '-')
		return (0);
	*j += ft_strlen(env->rooms[i->x].name) + 1;
	while (++i->y < (int)env->vert)
	{
		if (str[*j] && !ft_strncmp(str + *j, env->rooms[i->y].name,
				ft_strlen(env->rooms[i->y].name))
			&& str[*j + ft_strlen(env->rooms[i->y].name)] == '\0')
			break ;
	}
	if (!env->rooms[i->y].name)
		return (0);
	return (1);
}

int
	add_pipe(t_env *env, char *str)
{
	t_point	i;
	int		j;

	i = (t_point){.x = -1, .y = -1};
	j = 0;
	env->flag = 1;
	if (env->source == -1 || env->sink == -1 || env->source == env->sink
		|| env->io > 0)
		return (0);
	if (!env->graph)
		malloc_matrix(env, &env->graph, env->vert);
	if (!(check_pipes(env, str, &i, &j)))
		return (0);
	return (set_pipe(env, str, i, j));
}
