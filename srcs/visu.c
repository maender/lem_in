/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:05:13 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:05:14 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	reset_clr(t_env *env)
{
	int i;

	i = -1;
	while (++i < (int)env->vert)
		env->rooms[i].clr = 0x4e4e4e;
}

void
	mlx_draw(t_env *env)
{
	mlx_hook(env->v.win_ptr, KeyRelease,
		KeyReleaseMask, key_release, env);
	mlx_put_image_to_window(env->v.mlx_ptr, env->v.win_ptr,
		env->v.banner.ptr, 0, 0);
	mlx_put_image_to_window(env->v.mlx_ptr, env->v.win_ptr,
		env->v.img.ptr, 0, 136);
	draw_name(env, (env->togo - (int)env->antshow + 1 >= 0 ? env->togo
			- (int)env->antshow + 1 : 0));
	mlx_do_sync(env->v.mlx_ptr);
}

void
	draw_loop(t_env *env)
{
	int i;
	int j;

	i = -1;
	while (1)
	{
		create_map(env, 0);
		i = -1;
		while (++i < env->flowmax)
		{
			j = -1;
			while (++j < (int)env->paths[env->flowmax - 1][i].len)
			{
				if (env->ants[i].q[j] > 0)
					img_fill_rect_circ(env, (t_point){.x = env->diff[i][j].x,
						.y = env->diff[i][j].y}, 5,
							env->v.clr[env->ants[i].q[j] % NBR_CLR]);
			}
		}
		if (all_done(env, env->ants))
			break ;
		mlx_draw(env);
	}
}

int
	show_ants(t_env *env)
{
	calc_diff(env);
	push_ants(env, env->ants, (int*)&env->antshow, env->step);
	print_ants(env, env->ants);
	draw_loop(env);
	rotate_ants(env, env->ants);
	env->step++;
	if (env->step > (int)(env->paths[env->flowmax - 1][0].tosend
			+ env->paths[env->flowmax - 1][0].len - 1))
		quit(env);
	if (env->step)
		ft_printf("\n");
	return (1);
}

void
	print_sol_visu(t_env *env)
{
	env->step = 0;
	env->antshow = 1;
	if (!(env->ants = (t_queue*)malloc(QS * env->flowmax)))
		die(env);
	init_sol(env, env->ants);
	mlx_hook(env->v.win_ptr, KeyRelease,
		KeyReleaseMask, key_release, env);
	mlx_loop_hook(env->v.mlx_ptr, show_ants, env);
	mlx_loop(env->v.mlx_ptr);
}
