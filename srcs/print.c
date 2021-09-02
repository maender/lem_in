/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:37 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:38 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void
	print_ants(t_env *env, t_queue paths[])
{
	int i;
	int j;
	int flag;

	flag = 1;
	i = env->paths[env->flowmax - 1][env->flowmax - 1].len;
	while (--i >= 0)
	{
		j = -1;
		while (++j < env->flowmax)
		{
			if ((int)(env->paths[env->flowmax - 1][j].len) - 1 >= i
				&& paths[j].q[i] > 0)
			{
				if (!flag)
					ft_printf(" ");
				ft_printf("L%d-%s", paths[j].q[i]
					, env->rooms[env->paths[env->flowmax - 1][j].q[i]].name);
				flag = 0;
			}
		}
	}
}

void
	init_sol(t_env *env, t_queue paths[])
{
	int i;

	i = -1;
	if (env->vis)
		if (!(env->diff = (t_bren**)malloc(sizeof(t_bren*) * env->flowmax)))
			die(env);
	while (++i < env->flowmax)
	{
		if (!(paths[i].q = (int*)malloc(INTS * (env->vert - 1))))
		{
			free_queue(paths, i, 1);
			die(env);
		}
		if (env->vis)
			if (!(env->diff[i] = (t_bren*)malloc(sizeof(t_bren)
				* (env->vert - 1))))
			{
				free_queue(paths, i + 1, 1);
				die(env);
			}
		ft_bzero(paths[i].q, INTS * (env->vert - 1));
		paths[i].len = env->paths[env->flowmax - 1][i].len;
	}
}

int
	show_one(t_env *env)
{
	create_map(env, 0);
	env->antshow = env->ant + 1;
	img_fill_rect_circ(env, (t_point){.x = env->diff[0][0].x,
		.y = env->diff[0][0].y}, 5,
			env->v.clr[0]);
	if (all_done(env, env->ants))
		quit(env);
	mlx_draw(env);
	return (0);
}

void
	print_one_line(t_env *env)
{
	int i;

	i = 0;
	if (env->vis && (!(env->diff = (t_bren**)malloc(sizeof(t_bren*)))
		|| !(env->diff[0] = (t_bren*)malloc(sizeof(t_bren)))))
		die(env);
	while (++i <= (int)env->ant)
	{
		if (i > 1)
			ft_printf(" ");
		ft_printf("L%d-%s", i, env->rooms[env->paths[0][0].q[0]].name);
	}
	ft_printf("\n");
	if (env->vis)
	{
		calc_diff(env);
		mlx_loop_hook(env->v.mlx_ptr, show_one, env);
		mlx_loop(env->v.mlx_ptr);
	}
}

void
	print_sol(t_env *env)
{
	t_queue	paths[env->flowmax];
	int		ants;
	int		step;

	ants = 1;
	step = 0;
	env->togo = env->ant;
	if (env->flowmax == 1 && env->paths[0][0].len == 1)
		return (print_one_line(env));
	if (env->vis)
		return (print_sol_visu(env));
	init_sol(env, paths);
	while (step <= (int)(env->paths[env->flowmax - 1][0].tosend
			+ env->paths[env->flowmax - 1][0].len - 1))
	{
		if (step > 0)
			ft_printf("\n");
		push_ants(env, paths, &ants, step);
		print_ants(env, paths);
		rotate_ants(env, paths);
		step++;
	}
	free_queue(paths, env->flowmax, 1);
}
