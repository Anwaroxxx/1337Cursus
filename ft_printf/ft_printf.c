/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:21:47 by anwar             #+#    #+#             */
/*   Updated: 2026/08/23 00:21:47 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	route(t_fmt *f, va_list ap)
{
	if (f->conv == 'c')
		return (conv_c(ap, f));
	if (f->conv == 's')
		return (conv_s(ap, f));
	if (f->conv == 'd' || f->conv == 'i')
		return (conv_di(ap, f));
	if (f->conv == 'u')
		return (conv_u(ap, f));
	if (f->conv == 'x')
		return (conv_x(ap, f));
	if (f->conv == 'X')
		return (conv_X(ap, f));
	if (f->conv == 'p')
		return (conv_p(ap, f));
	if (f->conv == '%')
		return (conv_pct(f));
	return (0);
}

static int	parse_one(const char **format, va_list ap)
{
	t_fmt	f;
	int		printed;

	pf_init(&f);
	*format += 1;
	*format = pf_flags(*format, &f);
	*format = pf_width(*format, &f);
	*format = pf_prec(*format, &f);
	f.conv = **format;
	if (**format != '\0')
		*format += 1;
	printed = route(&f, ap);
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	const char	*p;
	const char	*start;
	int			total;

	va_start(ap, format);
	total = 0;
	p = format;
	while (*p != '\0')
	{
		start = p;
		while (*p != '\0' && *p != '%')
			p++;
		total += (int)write(1, start, p - start);
		if (*p == '%')
		{
			total += parse_one(&p, ap);
		}
	}
	va_end(ap);
	return (total);
}
