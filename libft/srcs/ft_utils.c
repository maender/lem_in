/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:47:32 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/15 18:45:25 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_strichr(char *str, int c)
{
	int i;

	i = -1;
	if (str && c)
	{
		while (str[++i])
		{
			if (str[i] == c)
				return (i);
		}
	}
	return (-1);
}

int		pf_strichr_case(char *str, int c)
{
	int i;

	i = -1;
	if (str && c)
	{
		while (str[++i])
		{
			if (str[i] == c || str[i] == c + 32)
				return (i);
		}
	}
	return (-1);
}

char	*pf_strchr(char *s, int c)
{
	size_t	len;
	size_t	i;

	len = pf_strlen(s);
	i = 0;
	while (i < len + 1)
	{
		if (*s == c && *s)
			return (s);
		s++;
		i++;
	}
	return (NULL);
}

void	pf_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}

size_t	pf_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}
