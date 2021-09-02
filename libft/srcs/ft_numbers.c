/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:44:34 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/24 10:34:30 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_atoi(const char *str)
{
	int			pos;
	long long	res;
	char		*nstr;

	pos = 1;
	res = 0;
	nstr = (char*)str;
	if (*nstr == '-' || *nstr == '+')
		pos = (*nstr++ == '+');
	while (*nstr <= '9' && *nstr >= '0')
		res = res * 10 + *nstr++ - '0';
	return (pos ? res : (-res));
}

void	pf_putnbr(t_params *p)
{
	long long int n;

	(p->f & PF_ADD) ? p->f &= ~PF_SPACE : 0;
	(p->f & PF_MINUS) ? p->f &= ~PF_ZERO : 0;
	if (p->f & PF_LONG || p->f & PF_LONG2)
		n = (p->f & PF_LONG2) ? (long long int)(va_arg(p->ap, long long))
		: (long long int)(va_arg(p->ap, long));
	else if (p->f & PF_SHORT || p->f & PF_SHORT2)
		n = (p->f & PF_SHORT2) ? (char)(va_arg(p->ap, int))
		: (short)(va_arg(p->ap, int));
	else if (p->f & PF_SSIZE_T)
		n = (ssize_t)va_arg(p->ap, long long int);
	else if (p->f & PF_INTMAX)
		n = (long long int)va_arg(p->ap, long long int);
	else
		n = (long long int)va_arg(p->ap, int);
	(p->f & PF_ZERO && !(p->f & PF_PREC)) ? p->prec = p->minw : 0;
	(p->f & PF_PREC) ? p->f &= ~PF_ZERO : 0;
	pf_itoa(n, p, 0);
}

void	pf_putnbr_base(t_params *p, int base)
{
	unsigned long long int n;

	(p->f & PF_ADD) ? p->f &= ~PF_SPACE : 0;
	(p->f & PF_MINUS) ? p->f &= ~PF_ZERO : 0;
	if (p->f & PF_LONG || p->f & PF_LONG2)
		n = (p->f & PF_LONG2) ? va_arg(p->ap, unsigned long long int)
		: (unsigned long)(va_arg(p->ap, unsigned long long int));
	else if (p->f & PF_SHORT || p->f & PF_SHORT2)
		n = (p->f & PF_SHORT2) ? (unsigned char)(va_arg(
			p->ap, unsigned long long int))
			: (unsigned short)(va_arg(p->ap, unsigned long long int));
	else if (p->f & PF_SSIZE_T)
		n = (size_t)va_arg(p->ap, unsigned long long int);
	else if (p->f & PF_INTMAX)
		n = (unsigned long long int)va_arg(p->ap, unsigned long long int);
	else
		n = (unsigned int)(va_arg(p->ap, unsigned long long int));
	pf_itoa_base(n, p, base);
}

void	pf_print_adress(t_params *p)
{
	void	*pointer;

	pointer = va_arg(p->ap, void *);
	(p->f & PF_ZERO || !pointer) ? p->minw -= 2 : 0;
	p->f |= PF_POINTER;
	p->f |= PF_SHARP;
	pf_itoa_base((unsigned long long int)pointer, p, 16);
}
