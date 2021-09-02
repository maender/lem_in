/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:14:43 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:16:12 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void
	set_room(t_env *env)
{
	env->rooms[env->vert].clr = 0x4e4e4e;
	env->rooms[env->vert].pipes.len = 0;
	env->rooms[env->vert].inpath = 0;
	env->rooms[env->vert].blocked = 0;
	env->xmax = env->xmax < env->rooms[env->vert].x
		? env->rooms[env->vert].x : env->xmax;
	env->ymax = env->ymax < env->rooms[env->vert].y
		? env->rooms[env->vert].y : env->ymax;
	env->io = 0;
	env->vert++;
}

void
	realloc_rooms(t_env *env, size_t size)
{
	t_room *tmp;

	if (!(tmp = (t_room*)ft_memalloc(sizeof(t_room) * size)))
		die(env);
	ft_bzero(tmp, sizeof(t_room) * size);
	ft_memcpy(tmp, env->rooms, sizeof(t_room) * (env->vert));
	ft_memdel((void**)&env->rooms);
	env->rooms = tmp;
}

int
	check_names(t_env *env, char *str)
{
	int i;

	i = 0;
	i += ft_strlen(env->rooms[env->vert].name) + 1;
	if (!str[i] || !ft_isdigit(str[i]) || check_exist(env)
		|| (env->rooms[env->vert].x = ft_atoi(str + i)) < 0)
	{
		ft_strdel(&env->rooms[env->vert].name);
		return (0);
	}
	i += ft_snbrlen(env->rooms[env->vert].x) + 1;
	if ((env->rooms[env->vert].y = ft_atoi(str + i)) < 0)
	{
		ft_strdel(&env->rooms[env->vert].name);
		return (0);
	}
	i += ft_snbrlen(env->rooms[env->vert].y);
	if (str[i])
	{
		ft_strdel(&env->rooms[env->vert].name);
		return (0);
	}
	return (1);
}

int
	add_room(t_env *env, char *str)
{
	if (env->flag)
		return (0);
	if (env->vert >= MSIZE && env->vert % MSIZE == 0)
		realloc_rooms(env, env->vert + MSIZE);
	if ((str[0] == 'L' || !ft_strchr(str, ' ')))
		return (0);
	env->rooms[env->vert].name = ft_strndup(str,
			ft_strchr(str, ' ') - str);
	if (!check_names(env, str))
		return (0);
	env->rooms[env->vert].pipes.p = NULL;
	set_room(env);
	return (1);
}
