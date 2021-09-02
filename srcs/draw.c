/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:03:52 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:03:55 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <math.h>

void
	draw_circle(t_env *env, int xm, int ym, int r)
{
	int	x;
	int	y;
	int	err;

	x = -r;
	y = 0;
	err = 2 - 2 * r;
	img_pixel_put(env, (t_point){.x = xm - x, .y = ym + y}, 0xffffff);
	img_pixel_put(env, (t_point){.x = xm - y, .y = ym + x}, 0xffffff);
	img_pixel_put(env, (t_point){.x = xm + x, .y = ym + y}, 0xffffff);
	img_pixel_put(env, (t_point){.x = xm + y, .y = ym + x}, 0xffffff);
	r = err;
	err += (r > x) ? ++x * 2 + 1 : 0;
	err += (r <= y) ? ++y * 2 + 1 : 0;
	while (x < 0)
	{
		img_pixel_put(env, (t_point){.x = xm - x, .y = ym + y}, 0xffffff);
		img_pixel_put(env, (t_point){.x = xm - y, .y = ym + x}, 0xffffff);
		img_pixel_put(env, (t_point){.x = xm + x, .y = ym + y}, 0xffffff);
		img_pixel_put(env, (t_point){.x = xm + y, .y = ym + x}, 0xffffff);
		r = err;
		err += (r > x) ? ++x * 2 + 1 : 0;
		err += (r <= y) ? ++y * 2 + 1 : 0;
	}
}

void
	drawrectcircle(t_env *env, int i)
{
	if (i == (int)env->source)
		img_fill_rect_circ_border(env, (t_point){env->rooms[i].x,
				env->rooms[i].y}, 15, env->v.clr[3]);
	else if (i == (int)env->sink)
		img_fill_rect_circ_border(env, (t_point){env->rooms[i].x,
				env->rooms[i].y}, 15, env->v.clr[4]);
	else
		img_fill_rect_circ_border(env, (t_point){env->rooms[i].x,
				env->rooms[i].y}, 15, env->rooms[i].clr);
}

void
	draw_paths(t_env *env, int u, int v)
{
	env->iter = 0;
	drawthickline(env, (t_point){.x = env->rooms[u].x,
		.y = env->rooms[u].y}, (t_point){.x = env->rooms[v].x,
			.y = env->rooms[v].y}, GREEN);
	env->iter = 1;
	drawthickline(env, (t_point){.x = env->rooms[u].x,
		.y = env->rooms[u].y}, (t_point){.x = env->rooms[v].x,
			.y = env->rooms[v].y}, GREEN);
}

void
	draw_pipes(t_env *env, int a)
{
	int u;
	int v;

	u = -1;
	while (++u < (int)env->vert)
	{
		v = -1;
		while (++v < (int)env->vert)
		{
			if (env->graph[u][v] > 0)
			{
				env->iter = 0;
				drawthickline(env, (t_point){.x = env->rooms[u].x,
					.y = env->rooms[u].y}, (t_point){.x = env->rooms[v].x,
						.y = env->rooms[v].y}, 0x6f6f6f);
				env->iter = 1;
				drawthickline(env, (t_point){.x = env->rooms[u].x,
					.y = env->rooms[u].y}, (t_point){.x = env->rooms[v].x,
						.y = env->rooms[v].y}, 0x6f6f6f);
			}
			if (a > -1 && env->rgraph[u][v] != 0)
				draw_paths(env, u, v);
		}
	}
}

void
	draw_name(t_env *env, int ants)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < (int)env->vert)
		mlx_string_put(env->v.mlx_ptr, env->v.win_ptr, env->rooms[i].x
			- ft_strlen(env->rooms[i].name) * 5, env->rooms[i].y + 126,
			WHITE, env->rooms[i].name);
	str = ft_itoa(env->ant);
	mlx_string_put(env->v.mlx_ptr, env->v.win_ptr, 25, WIN_H - 100, WHITE,
		"TOTAL : ");
	mlx_string_put(env->v.mlx_ptr, env->v.win_ptr, 105, WIN_H - 100, WHITE,
		str);
	ft_strdel(&str);
	str = ft_itoa(ants);
	mlx_string_put(env->v.mlx_ptr, env->v.win_ptr, 25, WIN_H - 50, WHITE,
		"TO GO : ");
	mlx_string_put(env->v.mlx_ptr, env->v.win_ptr, 105, WIN_H - 50, WHITE,
		str);
	ft_strdel(&str);
}
