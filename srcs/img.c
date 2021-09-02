/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:03:59 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:00 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	img_pixel_put(t_env *env, t_point a, int clr)
{
	int x;
	int y;

	x = a.x;
	y = a.y;
	if (x >= 0 && x < env->v.img.dimx && y >= 0 && y < env->v.img.dimy)
		env->v.img.pixel[(int)(y * env->v.img.dimx + x)] = clr;
}

void
	img_reset(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->v.img.dimy * WIN_W)
	{
		env->v.img.pixel[(int)(i)] = 0;
	}
}

void
	img_fill_rect_circ_border(t_env *env, t_point start, int rad, int color)
{
	int tmpx;
	int tmpy;

	tmpy = -rad;
	while (tmpy < rad)
	{
		tmpx = -rad;
		while (tmpx < rad)
		{
			if (tmpx * tmpx + tmpy * tmpy < rad * rad - rad * 4
				&& start.x + tmpx < WIN_W && start.x + tmpx >= 0
				&& start.y + tmpy < env->v.img.dimy && start.y + tmpy >= 0)
				env->v.img.pixel[(int)
					((start.y + tmpy) * env->v.img.dimx + start.x + tmpx)
						] = color;
			else if (tmpx * tmpx + tmpy * tmpy <= rad * rad
				&& start.x + tmpx < WIN_W && start.x + tmpx >= 0
				&& start.y + tmpy < env->v.img.dimy && start.y + tmpy >= 0)
				env->v.img.pixel[(int)
					((start.y + tmpy) * env->v.img.dimx + start.x + tmpx)
						] = 0x6f6f6f;
			++tmpx;
		}
		++tmpy;
	}
}

void
	img_fill_rect_circ(t_env *env, t_point start, int rad, int color)
{
	int tmpx;
	int tmpy;

	tmpy = -rad;
	while (tmpy < rad)
	{
		tmpx = -rad;
		while (tmpx < rad)
		{
			if (tmpx * tmpx + tmpy * tmpy <= rad * rad)
				env->v.img.pixel[(int)
					((start.y + tmpy) * env->v.img.dimx + start.x + tmpx)
						] = color;
			++tmpx;
		}
		++tmpy;
	}
}
