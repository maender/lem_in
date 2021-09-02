/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:03 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:05 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	init_window(t_env *env)
{
	if (!(env->v.win_ptr = mlx_new_window(env->v.mlx_ptr,
		env->v.win_w, env->v.win_h, "LEMIN")))
		die(env);
	if (!(env->v.img.ptr = mlx_new_image(env->v.mlx_ptr,
		env->v.img.dimx, env->v.img.dimy)))
		die(env);
	if (!(env->v.banner.ptr = mlx_xpm_file_to_image(env->v.mlx_ptr,
		"./assets/banner.XPM", &env->v.banner.dimx, &env->v.banner.dimy)))
		die(env);
	env->v.img.pixel = (int*)mlx_get_data_addr(env->v.img.ptr,
			&env->v.img.bpp, &env->v.img.size_line, &env->v.img.endian);
}

void
	init_clr(t_env *env)
{
	env->v.clr[0] = 0x08f7fe;
	env->v.clr[1] = 0xfdf200;
	env->v.clr[2] = 0xff2281;
	env->v.clr[3] = GOLDEN_ROD;
	env->v.clr[4] = SADDLEBROWN;
	env->v.clr[5] = LAWN_GREEN;
	env->v.clr[6] = 0x08f7fe;
	env->v.clr[7] = 0xff2281;
}

void
	init_visu(t_env *env)
{
	env->v.mlx_ptr = mlx_init();
	init_clr(env);
	env->v.win_w = WIN_W;
	env->v.win_h = WIN_H;
	env->v.img.dimx = WIN_W;
	env->v.img.dimy = WIN_H - 136;
	init_window(env);
}

void
	init_env(t_env *env)
{
	if (env->vis)
		init_visu(env);
	env->min = 214748647;
	env->outmin = 214748647;
	env->source = -1;
	env->sink = -1;
	if (!(env->rooms = ft_memalloc(sizeof(t_room) * 120)))
		die(env);
	ft_bzero(env->rooms, sizeof(t_room) * 120);
	env->graph = NULL;
	env->rgraph = NULL;
}
