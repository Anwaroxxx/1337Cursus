/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 11:06:23 by anwar             #+#    #+#             */
/*   Updated: 2026/08/14 19:28:47 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	conv_di(va_list ap, t_fmt *f)
{
	int	n;

	n = va_arg(ap, int);
	f->base = 10;
	f->set = PF_DEC;
	if (n < 0)
	{
		f->neg = 1;
		return (pf_putnum(f, -(unsigned long)n));
	}
	f->neg = 0;
	return (pf_putnum(f, (unsigned long)n));
}
