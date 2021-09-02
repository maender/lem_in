/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:52 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:53 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	free_queue(t_queue *q, int len, int flag)
{
	int i;

	i = 0;
	while (i < len)
	{
		ft_memdel((void**)&q[i].q);
		i++;
	}
	if (!flag)
		ft_memdel((void**)&q);
}

void
	free_env_bis(t_env *env)
{
	int i;

	i = -1;
	while (++i < (int)env->vert)
	{
		ft_memdel((void**)&env->rooms[i].pipes.p);
		ft_strdel(&env->rooms[i].name);
	}
	if ((i = -1) && env->vert)
		ft_memdel((void**)&env->rooms);
	while (++i < (int)env->flow)
		if (env->paths[i])
			free_queue(env->paths[i], i + 1, 0);
	ft_memdel((void**)&env->paths);
	ft_memdel((void**)&env->rooms);
}

void
	free_env(t_env *env)
{
	int i;

	i = -1;
	if (env->graph)
		ft_free_matrix((void**)env->graph, env->vert);
	if (env->rgraph)
		ft_free_matrix((void**)env->rgraph, env->vert);
	if (env->vis && env->diff)
	{
		while (++i < env->flowmax)
			ft_memdel((void**)&env->diff[i]);
		ft_memdel((void**)env->diff);
	}
	if ((i = -1) && env->toprint)
		ft_free_matrix((void**)env->toprint, env->index);
	free_env_bis(env);
}

void
	die(t_env *env)
{
	if (env->vis)
	{
		mlx_destroy_image(env->v.mlx_ptr, env->v.img.ptr);
		mlx_destroy_image(env->v.mlx_ptr, env->v.banner.ptr);
		mlx_destroy_window(env->v.mlx_ptr, env->v.win_ptr);
	}
	free_env(env);
	ft_putendl_fd("ERROR", STDERR_FILENO);
	exit(0);
}
