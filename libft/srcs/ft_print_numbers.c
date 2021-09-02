/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 20:13:46 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/24 10:39:47 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void
	pf_confid_itoa(long long int n, t_params *p, int len)
{
	long long int tmp;

	tmp = (n < 0) ? -n : n;
	p->printed = 0;
	(!tmp && !(p->f & PF_PREC && !p->prec)) ? ++len : 0;
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	((n < 0 || p->f & PF_SPACE || p->f & PF_ADD) && p->f & PF_ZERO)
		? --p->prec : 0;
	p->printed = pf_max(p->prec, len);
	(n < 0 || p->f & PF_ADD || p->f & PF_SPACE) ? ++p->printed : 0;
	p->padding = (p->printed > p->minw) ? 0 : p->minw - p->printed;
}

void
	pf_confid_itoa_base(unsigned long long int n, t_params *p,
		int *flag, int base)
{
	unsigned long long int tmp;

	tmp = n;
	p->printed = 0;
	(p->f & PF_ZERO && !(p->f & PF_PREC)) ? p->prec = p->minw : 0;
	(!tmp) ? ++p->printed : 0;
	while (tmp && ++p->printed)
		tmp /= base;
	(!p->prec && p->f & PF_PREC && !n) ? --p->printed : 0;
	*flag = (p->printed >= p->prec) ? 1 : 0;
	(p->f & PF_SHARP && base == 8 && !flag) ? p->printed++ : 0;
	(p->f & PF_SHARP && base == 8 && !n && p->f & PF_PREC && !p->prec)
		? p->printed++ : 0;
	(p->f & PF_SHARP && base == 8 && flag && n) ? p->minw-- : 0;
	(p->f & PF_SHARP && base == 8 && n && p->printed < p->prec)
		? p->minw++ : 0;
	(p->f & PF_SHARP && base == 16 && n) ? p->minw -= 2 : 0;
	(p->f & PF_ZERO && !(p->f & PF_PREC) && p->printed >= p->minw)
		? p->prec = p->minw : 0;
	p->printed = pf_max(p->printed, p->prec);
	p->padding = pf_max(p->minw - p->printed, 0);
	(p->f & PF_PREC && p->prec < p->minw) ? p->f &= ~PF_ZERO : 0;
}

void
	pf_itoa(long long int n, t_params *p, int len)
{
	char					*out;
	unsigned long long int	tmp;

	tmp = (n < 0) ? -n : n;
	pf_confid_itoa(n, p, len);
	pf_padding(p, 0);
	if (!(out = pf_strnew(p->printed)))
		exit(0);
	pf_itoa_base_print(tmp, p, out, 10);
	if (p->f & PF_ADD || p->f & PF_SPACE || n < 0)
	{
		out[0] = ' ';
		(p->f & PF_ADD && n >= 0) ? out[0] = '+' : 0;
		(n < 0) ? out[0] = '-' : 0;
	}
	write(p->fd, out, p->printed);
	pf_strdel(&out);
	p->len += p->printed;
	pf_padding(p, 1);
}

void
	pf_itoa_base(unsigned long long int n, t_params *p, int base)
{
	char	*out;
	int		flag;

	pf_confid_itoa_base(n, p, &flag, base);
	pf_padding(p, 0);
	if (!(out = pf_strnew(p->printed)))
		exit(0);
	if ((n || p->f & PF_POINTER) && p->f & PF_SHARP && ((base == 8 && flag)
			|| (base == 16)))
	{
		write(p->fd, "0", 1);
		++p->len;
		if (base == 16)
		{
			write(p->fd, (p->f & PF_UPCASE) ? "X" : "x", 1);
			p->len++;
		}
	}
	pf_itoa_base_print(n, p, out, base);
	write(p->fd, out, p->printed);
	pf_strdel(&out);
	p->len += p->printed;
	pf_padding(p, 1);
}

void
	pf_itoa_base_print(unsigned long long int n, t_params *p,
		char *str, int base)
{
	int						len;
	unsigned long long int	tmp;

	tmp = n;
	len = 0;
	while (tmp && ++len)
		tmp /= base;
	(n && base == 16 && (p->f & PF_ZERO) && (p->f & PF_SHARP)
		&& p->printed > 3 && !(p->f & PF_PREC) && p->printed > len)
			? p->printed -= 2 : 0;
	len = p->printed;
	p->c = 'a' - 10 - ((p->f & PF_UPCASE) >> 6);
	while (len--)
	{
		str[len] = n % base + ((n % base < 10) ? '0' : p->c);
		n /= base;
	}
}
