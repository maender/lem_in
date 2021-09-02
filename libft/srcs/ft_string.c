/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:25:34 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/15 18:45:20 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putchar(t_params *p)
{
	char	out;

	out = (char)va_arg(p->ap, int);
	p->printed = pf_max(1, p->minw);
	p->padding = pf_max(0, p->minw - 1);
	pf_padding(p, 0);
	write(p->fd, &out, 1);
	++p->len;
	pf_padding(p, 1);
}

void	pf_putstr(t_params *p)
{
	char	*tmp;
	size_t	len;

	tmp = (char*)va_arg(p->ap, char*);
	len = (!tmp) ? 6 : pf_strlen(tmp);
	(!(p->f & PF_PREC)) ? p->prec = len : 0;
	(p->prec > (int)len) ? p->prec = len : 0;
	p->printed = pf_max(p->minw, p->prec);
	p->padding = pf_max(0, p->minw - p->prec);
	pf_padding(p, 0);
	(!tmp) ? write(p->fd, PF_NULL, p->prec) : write(p->fd, tmp, p->prec);
	p->len += p->prec;
	pf_padding(p, 1);
}
