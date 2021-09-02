/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:04:26 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/24 10:04:27 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int
	parse_io(t_env *env, char *tmp)
{
	int	i;

	i = 0;
	if (ft_strncmp(tmp + 2, "start", 5) && ft_strncmp(tmp + 2, "end", 3))
		return (0);
	if (env->source == -1 && !ft_strncmp(tmp + 2, "start", 5) && ft_strlen(
			tmp + 2) == 5)
	{
		env->io = 1;
		env->source = env->vert;
	}
	else if (env->sink == -1 && ft_strlen(tmp + 2) == 3)
	{
		env->sink = env->vert;
		env->io = 2;
	}
	else
		return (0);
	return (env->source != env->sink ? 1 : 0);
}

static int
	parse(t_env *env, char *raw)
{
	int	i;

	i = -1;
	while (raw[++i] && !env->end)
	{
		if (raw[i] == '#')
		{
			if (env->io > 0)
				return (0);
			if (raw[i + 1] && raw[i + 1] == '#' && raw[i + 2])
				return (parse_io(env, raw));
			else if ((env->io = 0) >= 0)
				return (1);
		}
		else
		{
			if (raw[i] && ft_isalnum(raw[i]) && ft_strchr(raw, ' '))
				return (add_room(env, raw));
			else if (ft_isalnum(raw[i]))
				return (add_pipe(env, raw));
			else
				return (0);
		}
	}
	return (0);
}

void
	realloc_toprint(t_env *env, size_t size)
{
	char **tmp;

	if (!(tmp = (char**)ft_memalloc(sizeof(char*) * size)))
		die(env);
	ft_bzero(tmp, sizeof(char**) * size);
	ft_memcpy(tmp, env->toprint, sizeof(char*) * (env->index));
	ft_memdel((void**)&env->toprint);
	env->toprint = tmp;
}

void
	parse_wrapper_helper(t_env *env, char **tmp)
{
	int i;

	i = 0;
	ft_strdel(tmp);
	if (env->source < 0 || env->sink < 0 || env->source == env->sink)
		die(env);
	if (env->vis)
		visu(env, -1);
	if (!(env->flowmax = saumon_fume(env)))
		die(env);
	if (env->vis)
		reset_clr(env);
	while (++i < (int)env->index)
		ft_printf("%s\n", env->toprint[i]);
}

void
	parse_wrapper(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (!(env->toprint = (char**)ft_memalloc(sizeof(char*) * NBLINE)))
		die(env);
	while (get_next_line(0, &tmp) > 0)
	{
		if (env->index % NBLINE == 0)
			realloc_toprint(env, sizeof(char*) * (env->index + NBLINE));
		if (env->ant == 0)
		{
			if ((env->ant = ft_atoi(tmp)) <= 0 || (int)ft_strlen(tmp)
				!= ft_snbrlen(env->ant))
			{
				ft_strdel(&tmp);
				die(env);
			}
			env->toprint[env->index++] = ft_strdup(tmp);
		}
		else if (!parse(env, tmp))
			break ;
		env->toprint[env->index++] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	parse_wrapper_helper(env, &tmp);
}
