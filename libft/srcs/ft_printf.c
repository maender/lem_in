/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:13:57 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/23 20:28:55 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_colors.h"

int			check_colors(t_params *p)
{
	int i;

	i = 0;
	while (i < 13)
	{
		if (!pf_strcmp(p->format + 1, g_colors[i].color,
				pf_strlen(g_colors[i].color)))
			return (i);
		i++;
	}
	return (-1);
}

void		pf_color(t_params *p)
{
	int i;

	i = check_colors(p);
	++p->format;
	if (i < 0)
		return ;
	if (i < 12 && i >= 0 && i != 5)
	{
		write(p->fd, g_colors[i].code, 7);
		p->len += 7;
	}
	else if (i == 5)
	{
		write(p->fd, g_colors[i].code, 8);
		p->len += 8;
	}
	else
	{
		write(p->fd, g_colors[i].code, 4);
		p->len += 4;
	}
	p->format += pf_strlen(g_colors[i].color);
}

int			ft_printf(const char *format, ...)
{
	t_params p;

	pf_bzero(&p, sizeof(p));
	va_start(p.ap, format);
	p.format = (char*)format;
	p.fd = 1;
	while (*(p.format) != '\0')
	{
		if (*(p.format) == '%')
		{
			++p.format;
			if (!*(p.format))
				break ;
			pf_parse_options(&p);
		}
		else if (*(p.format) == '{' && (check_colors(&p) != -1))
			pf_color(&p);
		else
		{
			write(1, p.format, 1);
			p.len++;
		}
		(*p.format) ? p.format++ : 0;
	}
	return (p.len);
}

void		pf_padding(t_params *p, int i)
{
	if (!p->padding)
		return ;
	p->c = 32 | ((p->f & PF_ZERO) << 3);
	if (!i && !(p->f & PF_MINUS))
	{
		while (p->padding--)
		{
			write(p->fd, &(p->c), 1);
			++p->len;
		}
	}
	if (i && p->f & PF_MINUS)
	{
		while (p->padding--)
		{
			write(p->fd, &(p->c), 1);
			++p->len;
		}
	}
}
