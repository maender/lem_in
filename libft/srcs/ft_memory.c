/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:16:34 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/15 18:44:51 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_bzero(void *s, size_t n)
{
	char *dest;

	dest = (char*)s;
	if (n)
	{
		while (n--)
			*dest++ = 0;
	}
}

char	*pf_strncpy(char *dest, const char *src, size_t n)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (++i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*pf_strdup(const char *src)
{
	char *dest;

	if (!(dest = malloc(sizeof(char) * (pf_strlen(src) + 1))))
		return (0);
	pf_strncpy(dest, src, pf_strlen(src));
	return (dest);
}

char	*pf_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	i;

	i = -1;
	if (!(dest = malloc(sizeof(char) * (n + 1))))
		return (0);
	while (++i < n)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
