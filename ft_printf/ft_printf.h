/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:21:47 by anwar             #+#    #+#             */
/*   Updated: 2026/08/23 00:21:47 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

# define PF_DEC "0123456789"
# define PF_HEXLOW "0123456789abcdef"
# define PF_HEXUP "0123456789ABCDEF"

typedef struct s_fmt
{
	char			conv;
	int				left;
	int				zero;
	int				hash;
	int				plus;
	int				space;
	int				width;
	int				prec;
	int				neg;
	int				spaces;
	unsigned long	val;
	unsigned long	base;
	const char		*set;
	size_t			ndig;
	size_t			zeros;
	size_t			fill;
}	t_fmt;

int		ft_printf(const char *format, ...);

void	pf_init(t_fmt *f);
const char	*pf_flags(const char *s, t_fmt *f);
const char	*pf_width(const char *s, t_fmt *f);
const char	*pf_prec(const char *s, t_fmt *f);

int		pf_char(char c);
int		pf_pad(char c, int n);
int		pf_str(const char *s);

int		pf_putnum(t_fmt *f, unsigned long n);
int		conv_c(va_list ap, t_fmt *f);
int		conv_s(va_list ap, t_fmt *f);
int		conv_pct(t_fmt *f);
int		conv_di(va_list ap, t_fmt *f);
int		conv_u(va_list ap, t_fmt *f);
int		conv_x(va_list ap, t_fmt *f);
int		conv_X(va_list ap, t_fmt *f);
int		conv_p(va_list ap, t_fmt *f);

#endif
