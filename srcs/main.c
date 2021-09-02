/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:45:29 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/24 10:09:19 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>
#include <string.h>

void
	options(t_env *env, char *av)
{
	env->vis = 0;
	if (av[0] == '-' && av[1] == 'v')
		env->vis = 1;
	else
	{
		ft_printf("Usage : ./lem-in [options...] < [input file]\n");
		ft_printf("Options:\n-v\tvisual\n");
		exit(0);
	}
}

int
	quit(t_env *env)
{
	if (env->vis)
	{
		mlx_destroy_image(env->v.mlx_ptr, env->v.img.ptr);
		mlx_destroy_image(env->v.mlx_ptr, env->v.banner.ptr);
		mlx_destroy_window(env->v.mlx_ptr, env->v.win_ptr);
	}
	free_env(env);
	if (env->vis)
		exit(0);
	return (0);
}

int
	key_release(int key, t_env *env)
{
	if (key == KEY_ESCAPE || key == 65307)
		quit(env);
	return (0);
}

int
	main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (ac > 1 || ac != 1)
		(ac > 1) ? options(&env, av[1]) : die(&env);
	init_env(&env);
	parse_wrapper(&env);
	ft_printf("\n");
	print_sol(&env);
	return (quit(&env));
}
