/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:19:40 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/24 10:39:14 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_parse_minw_prec(t_params *p)
{
	if (*p->format >= '1' && *p->format <= '9')
	{
		p->minw = pf_max(1, pf_atoi(p->format));
		while (*p->format >= '0' && *p->format <= '9')
			p->format++;
	}
	while (*p->format == '.')
	{
		p->f |= PF_PREC;
		p->format++;
		p->prec = pf_max(0, pf_atoi(p->format));
		while (*p->format >= '0' && *p->format <= '9')
			p->format++;
	}
}

void		pf_parse_conversion(t_params *p)
{
	p->c = *p->format;
	if (p->c == 'c')
		pf_putchar(p);
	else if (p->c == 's')
		pf_putstr(p);
	else if (pf_strchr("bBoOuUxX", p->c))
		pf_putnbr_base(p, pf_strichr_case(".b..ou..x", p->c) << 1);
	else if (p->c == 'p')
		pf_print_adress(p);
	else if (pf_strchr("diDI", p->c))
		pf_putnbr(p);
	else if (pf_strchr("fF", p->c))
		pf_putdouble(p);
	else
		pf_cs_not_found(p);
}

void		pf_parse_modifier(t_params *p)
{
	while (1)
	{
		if (*p->format == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format)
				? PF_SHORT2 : PF_SHORT;
		else if (*p->format == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? PF_LONG2 : PF_LONG;
		else if (*p->format == 'L')
			p->f |= PF_LONG2;
		else if (*p->format == 'z')
			p->f |= PF_SSIZE_T;
		else if (*p->format == 'j')
			p->f |= PF_INTMAX;
		else
			break ;
		p->format++;
	}
}

void		pf_parse_options(t_params *p)
{
	p->prec = 1;
	p->f = 0;
	p->minw = 0;
	pf_parse_flags(p);
	pf_parse_modifier(p);
	pf_parse_minw_prec(p);
	pf_parse_flags(p);
	pf_parse_modifier(p);
	pf_parse_flags(p);
	(p->f & PF_MINUS) ? p->f &= ~PF_ZERO : 0;
	if (pf_strchr("XDIFUO", *p->format))
		p->f |= (*p->format == 'X' || *p->format == 'F') ? PF_UPCASE : PF_LONG;
	(p->f & PF_LONG || p->f & PF_LONG2) ? p->f &= (~PF_SHORT & ~PF_SHORT2) : 0;
	(p->f & PF_SSIZE_T || p->f & PF_INTMAX)
		? p->f &= (~PF_SHORT & ~PF_SHORT2) : 0;
	pf_parse_conversion(p);
}

void		pf_cs_not_found(t_params *p)
{
	if (!(*p->format))
		return ;
	if ((p->padding = p->minw - 1) > 0)
	{
		pf_padding(p, 0);
		write(p->fd, p->format, 1);
		++p->len;
		pf_padding(p, 1);
		return ;
	}
	write(p->fd, p->format, 1);
	++p->len;
}
