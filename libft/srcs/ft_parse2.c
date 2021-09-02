/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 20:32:14 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/15 18:44:59 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_get_params(t_params *p, int *tmp, int i)
{
	(!(p->f & PF_PREC)) ? p->f |= PF_MINW : 0;
	if ((*tmp = pf_atoi(p->format)) < 0)
	{
		(!(p->f & PF_PREC)) ? p->f |= PF_MINUS : 0;
		*tmp *= -1;
	}
	while (*p->format >= '0' && *p->format <= '9')
		++p->format;
	(*p->format != '$') ? p->n = va_arg(p->ap, int) : 0;
	if (*p->format == '$')
	{
		while (i++ < *tmp)
			p->n = (int)va_arg(p->apbis, int);
	}
	if (p->n < 0)
	{
		p->n = (!(p->f & PF_PREC)) ? -p->n : 0;
		(!(p->f & PF_PREC)) ? p->f |= PF_MINUS : 0;
		p->f &= ~PF_PREC;
	}
}

void		pf_wildcard(t_params *p)
{
	int i;
	int tmp;

	i = 0;
	va_copy(p->apbis, p->ap);
	p->f &= ~PF_WILDCARD;
	p->f &= ~PF_MINW;
	pf_get_params(p, &tmp, i);
	(*p->format != '$' && tmp > 0) ? p->n = tmp : 0;
	(*p->format == '$') ? ++p->format : 0;
	(p->f & PF_MINW) ? p->minw = p->n : 0;
	(p->f & PF_PREC) ? p->prec = p->n : 0;
}

void		pf_parse_flags(t_params *p)
{
	while ((p->n = pf_strichr("#0-+ *", *(p->format))) > -1 && ++p->format)
		p->f |= (1 << p->n);
	(p->f & PF_MINUS && !(p->f & PF_WILDCARD)) ? p->f &= ~PF_ZERO : 0;
	(p->f & PF_ADD) ? p->f &= ~PF_SPACE : 0;
	if (p->f & PF_WILDCARD)
		pf_wildcard(p);
}
