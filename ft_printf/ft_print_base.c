/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 15:19:48 by anwar             #+#    #+#             */
/*   Updated: 2026/08/23 01:05:47 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static size_t	digit_count(unsigned long n, unsigned long base)
{
	size_t	len;

	len = 1;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	return (len);
}

static int	pf_sign(t_fmt *f, int emit)
{
	if (!(f->neg || ((f->plus || f->space)
				&& (f->conv == 'd' || f->conv == 'i' || f->conv == 'p'))))
		return (0);
	if (!emit)
		return (1);
	if (f->neg)
		pf_char('-');
	else if (f->plus)
		pf_char('+');
	else
		pf_char(' ');
	return (1);
}

static int	prefix(t_fmt *f, int emit)
{
	int	len;

	len = pf_sign(f, emit);
	if (f->conv == 'p' || (f->hash && f->val != 0
			&& (f->conv == 'x' || f->conv == 'X')))
	{
		len += 2;
		if (emit && f->conv == 'X')
			pf_str("0X");
		else if (emit)
			pf_str("0x");
	}
	return (len);
}

static void	layout(t_fmt *f)
{
	int	content;

	f->ndig = digit_count(f->val, f->base);
	if (f->val == 0 && f->prec == 0)
		f->ndig = 0;
	f->zeros = 0;
	if (f->prec >= 0 && (size_t)f->prec > f->ndig)
		f->zeros = (size_t)f->prec - f->ndig;
	f->fill = 0;
	f->spaces = 0;
	content = prefix(f, 0) + (int)f->ndig + (int)f->zeros;
	if (f->width <= content)
		return ;
	if (f->zero && !f->left && f->prec < 0)
		f->fill = (size_t)(f->width - content);
	else
		f->spaces = f->width - content;
}

int	pf_putnum(t_fmt *f, unsigned long n)
{
	int	total;

	f->val = n;
	layout(f);
	total = prefix(f, 0) + (int)f->ndig + (int)f->zeros + (int)f->fill;
	if (!f->left)
		pf_pad(' ', f->spaces);
	prefix(f, 1);
	pf_pad('0', (int)(f->zeros + f->fill));
	if (f->ndig > 0)
		pf_digits(f);
	if (f->left)
		pf_pad(' ', f->spaces);
	return (total + f->spaces);
}
