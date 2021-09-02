/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 20:27:50 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/24 10:06:40 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*pf_strnew(size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!(str = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	while (i < size + 1)
		str[i++] = '\0';
	return (str);
}

long double	pf_pow(long double n, int pow)
{
	if (!pow)
		return (1);
	else
		return (n * pf_pow(n, pow - 1));
}

int			pf_strcmp(const char *s1, const char *s2, int n)
{
	int i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] == s2[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int			pf_max(int a, int b)
{
	return (a > b ? a : b);
}
