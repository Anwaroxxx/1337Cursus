/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 09:33:14 by anwar             #+#    #+#             */
/*   Updated: 2026/08/22 23:47:19 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	conv_c(va_list ap, t_fmt *f)
{
	char	c;

	c = (char)va_arg(ap, int);
	if (!f->left && f->width > 1)
		pf_pad(' ', f->width - 1);
	pf_char(c);
	if (f->left && f->width > 1)
		pf_pad(' ', f->width - 1);
	if (f->width > 1)
		return (f->width);
	return (1);
}

int	conv_pct(t_fmt *f)
{
	(void)f;
	pf_char('%');
	return (1);
}

static int	put_n(const char *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pf_char(s[i]);
		i++;
	}
	return (i);
}

int	conv_s(va_list ap, t_fmt *f)
{
	const char	*s;
	int			len;
	int			pad;

	s = va_arg(ap, const char *);
	if (!s)
		s = "(null)";
	len = 0;
	while (s[len] != '\0' && (f->prec < 0 || len < f->prec))
		len++;
	pad = 0;
	if (f->width > len)
		pad = f->width - len;
	if (!f->left)
		pf_pad(' ', pad);
	put_n(s, len);
	if (f->left)
		pf_pad(' ', pad);
	return (len + pad);
}
