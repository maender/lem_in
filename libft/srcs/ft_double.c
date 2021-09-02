/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:35:21 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/24 10:46:08 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_config_double(t_params *p, t_double *dbl)
{
	char out[128];

	dbl->prec = (p->prec > PREC) ? PREC : p->prec;
	dbl->zeros = (dbl->zeros < PREC) ? 0 : p->prec - dbl->zeros;
	dbl->pow = (!dbl->zeros) ? p->prec : p->prec - dbl->zeros;
	p->printed += dbl->pow;
	p->minw = (p->printed > p->minw) ? p->printed : p->minw;
	(p->f & PF_ZERO) ? p->prec = p->minw : 0;
	p->printed = (p->f & PF_ZERO) ? p->prec : p->printed;
	p->padding = p->minw - p->printed - dbl->zeros > 0
		? p->minw - p->printed - dbl->zeros : 0;
	pf_padding(p, 0);
	pf_dtoa_print(dbl, p, out);
	(dbl->n < 0.0f || p->f & PF_ADD || p->f & PF_SPACE) ? out[0] = ' ' : 0;
	(dbl->n >= 0.0f && p->f & PF_ADD) ? out[0] = '+' : 0;
	(dbl->n < 0.0f) ? out[0] = '-' : 0;
	write(p->fd, out, p->printed);
	p->len += p->printed + dbl->zeros;
	while (dbl->zeros--)
		write(p->fd, "0", 1);
	pf_padding(p, 1);
}

void	pf_putdouble(t_params *p)
{
	t_double	dbl;
	long double	tmp;

	pf_bzero(&dbl, sizeof(dbl));
	p->printed = 0;
	if (p->f & PF_LONG2)
		dbl.n = (long double)va_arg(p->ap, long double);
	else
		dbl.n = (long double)va_arg(p->ap, double);
	(!(p->f & PF_PREC)) ? p->prec = 6 : 0;
	(p->prec) ? ++p->printed : 0;
	(dbl.n < 0.0f || p->f & PF_ADD || p->f & PF_SPACE || p->f & PF_SHARP)
		? ++p->printed : 0;
	tmp = (dbl.n < 0.0f) ? -dbl.n : dbl.n;
	dbl.intpart = (unsigned long long int)tmp;
	dbl.decpart = tmp - dbl.intpart;
	(!(unsigned long long int)tmp) ? ++p->printed : 0;
	while ((unsigned long long int)tmp && ++p->printed)
		tmp /= 10;
	while (dbl.zeros < PREC && dbl.zeros < p->prec + 1)
		++dbl.zeros;
	pf_config_double(p, &dbl);
}

void	pf_dtoa_print_bis(t_double *dbl, t_params *p, char *out, int middle)
{
	int len;

	len = middle;
	while (len--)
	{
		out[len] = dbl->intpart % 10 + '0';
		dbl->intpart /= 10;
	}
	(dbl->prec > 0 || p->f & PF_SHARP) ? out[middle] = '.' : 0;
	while (++len <= dbl->pow)
	{
		dbl->decpart *= 10;
		out[len + middle + 1] = (int)dbl->decpart + '0';
		dbl->decpart -= (int)dbl->decpart;
	}
}

void	pf_dtoa_print(t_double *dbl, t_params *p, char *out)
{
	int			middle;
	long double	tmp;
	int			add;

	tmp = dbl->decpart * pf_pow(10, dbl->pow + 1);
	tmp = tmp > 0 ? tmp : -tmp;
	dbl->decpart = ((long long int)dbl->decpart % 10 > 4 ? (tmp + 1)
			/ pf_pow(10, dbl->pow + 1) : tmp / pf_pow(10, dbl->pow + 1));
	add = (int)dbl->decpart;
	dbl->intpart += add;
	tmp = dbl->intpart;
	middle = p->printed - dbl->prec - (dbl->prec > 0 || p->f & PF_SHARP);
	pf_dtoa_print_bis(dbl, p, out, middle);
}
