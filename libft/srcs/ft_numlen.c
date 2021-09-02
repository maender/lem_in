/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:55:41 by maabou-h          #+#    #+#             */
/*   Updated: 2019/06/15 03:46:27 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_numlen(int n, int base)
{
	int len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}