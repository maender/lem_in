/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:05:16 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:05:21 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	create_map(t_env *env, int a)
{
	int	i;

	i = -1;
	if (!env->vis)
		return ;
	img_reset(env);
	while (a < 0 && ++i < (int)env->vert)
	{
		env->rooms[i].x = (env->rooms[i].x * WIN_W / (env->xmax
					? env->xmax : 1)) / 2 + WIN_W / 4;
		env->rooms[i].y = (env->rooms[i].y * WIN_H / (env->ymax
					? env->ymax : 1)) / 2 + WIN_H / 4;
	}
	draw_pipes(env, a);
	i = -1;
	while (++i < (int)env->vert)
		drawrectcircle(env, i);
}

void
	visu(t_env *env, int a)
{
	mlx_do_sync(env->v.mlx_ptr);
	create_map(env, a);
	mlx_put_image_to_window(env->v.mlx_ptr, env->v.win_ptr, env->v.banner.ptr,
		0, 0);
	mlx_put_image_to_window(env->v.mlx_ptr, env->v.win_ptr, env->v.img.ptr,
		0, 136);
	draw_name(env, env->ant);
	mlx_hook(env->v.win_ptr, KeyRelease,
		KeyReleaseMask, key_release, env);
}
