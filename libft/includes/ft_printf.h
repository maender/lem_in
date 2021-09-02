/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:07:07 by sdincbud          #+#    #+#             */
/*   Updated: 2019/06/19 11:14:44 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <float.h>
# include <limits.h>

# define PF_NULL "(null)"
# define PREC LDBL_MANT_DIG

# define PF_SHARP		(1 << 0)
# define PF_ZERO		(1 << 1)
# define PF_MINUS		(1 << 2)
# define PF_ADD			(1 << 3)
# define PF_SPACE		(1 << 4)
# define PF_WILDCARD	(1 << 5)
# define PF_LONG		(1 << 6)
# define PF_LONG2		(1 << 7)
# define PF_SHORT		(1 << 8)
# define PF_SHORT2		(1 << 9)
# define PF_PREC		(1 << 10)
# define PF_UPCASE		(1 << 11)
# define PF_POINTER		(1 << 12)
# define PF_INTMAX		(1 << 13)
# define PF_SSIZE_T		(1 << 14)
# define PF_MINW		(1 << 15)

typedef struct				s_double
{
	long double				n;
	unsigned long long int	intpart;
	long double				decpart;
	int						prec;
	int						pow;
	int						zeros;
}							t_double;

typedef struct				s_color
{
	char					color[30];
	char					code[9];
}							t_color;

typedef struct				s_params
{
	int						len;
	int						minw;
	int						prec;
	char					*format;
	int						printed;
	short					f;
	short					n;
	va_list					ap;
	va_list					apbis;
	int						fd;
	char					c;
	int						padding;
}							t_params;

int							ft_printf(const char *format, ...);
void						pf_padding(t_params *params, int i);
size_t						pf_strlen(const char *str);
char						*pf_strdup(const char *src);
char						*pf_strcpy(char *dest, const char *src);
char						*pf_strnew(size_t size);
void						pf_strdel(char **as);
int							pf_strichr(char *str, int c);
char						*pf_strchr(char *s, int c);
size_t						pf_strlen(const char *str);
int							pf_strichr_case(char *str, int c);
void						pf_putchar(t_params *params);
void						pf_putstr(t_params *params);
void						pf_putnbr_fd(int n, int fd);
int							pf_atoi(const char *str);
void						pf_putnbr(t_params *params);
void						pf_putnbr_base(t_params *params, int base);
void						pf_itoa(long long int n, t_params *p, int len);
void						pf_itoa_base(unsigned long long int n,
								t_params *params, int base);
void						pf_itoa_base_print(unsigned long long int n,
								t_params *params, char *str, int base);
void						pf_print_adress(t_params *params);
void						pf_putdouble(t_params *p);
void						pf_bzero(void *src, size_t size);
char						*pf_strnew(size_t size);
void						pf_strdel(char **as);
char						*pf_strndup(const char *src, size_t n);
char						*pf_strncpy(char *dest, const char *src, size_t n);
char						*pf_strdup(const char *src);
char						*pf_strnew(size_t size);
void						pf_parse_flags(t_params *params);
void						pf_parse_minw_prec(t_params *params);
void						pf_parse_conversion(t_params *params);
void						pf_parse_options(t_params *params);
void						pf_cs_not_found(t_params *params);
void						pf_wildcard(t_params *p);
long double					pf_pow(long double n, int pow);
void						pf_dtoa_print(t_double *dbl, t_params *p,
							char *out);
void						pf_color(t_params *p);
int							pf_strcmp(const char *s1, const char *s2, int n);
int							pf_max(int a, int b);

#endif
