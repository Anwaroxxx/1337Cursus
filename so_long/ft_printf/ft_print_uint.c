/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:41:09 by anwar             #+#    #+#             */
/*   Updated: 2026/08/17 20:03:55 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	pf_nil(t_fmt *f)
{
	int	pad;

	pad = 0;
	if (f->width > 5)
		pad = f->width - 5;
	if (!f->left)
		pf_pad(' ', pad);
	pf_str("(nil)");
	if (f->left)
		pf_pad(' ', pad);
	return (5 + pad);
}

int	conv_u(va_list ap, t_fmt *f)
{
	f->base = 10;
	f->set = PF_DEC;
	f->neg = 0;
	return (pf_putnum(f, va_arg(ap, unsigned int)));
}

int	conv_x(va_list ap, t_fmt *f)
{
	f->base = 16;
	f->set = PF_HEXLOW;
	f->neg = 0;
	return (pf_putnum(f, va_arg(ap, unsigned int)));
}

int	conv_xup(va_list ap, t_fmt *f)
{
	f->base = 16;
	f->set = PF_HEXUP;
	f->neg = 0;
	return (pf_putnum(f, va_arg(ap, unsigned int)));
}

int	conv_p(va_list ap, t_fmt *f)
{
	void	*ptr;

	ptr = va_arg(ap, void *);
	if (!ptr)
		return (pf_nil(f));
	f->base = 16;
	f->set = PF_HEXLOW;
	f->neg = 0;
	return (pf_putnum(f, (unsigned long)ptr));
}
