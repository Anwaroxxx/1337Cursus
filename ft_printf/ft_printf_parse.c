/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:21:47 by anwar             #+#    #+#             */
/*   Updated: 2026/08/23 00:21:47 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_init(t_fmt *f)
{
	f->conv = '\0';
	f->left = 0;
	f->zero = 0;
	f->hash = 0;
	f->plus = 0;
	f->space = 0;
	f->width = 0;
	f->prec = -1;
	f->neg = 0;
	f->spaces = 0;
	f->val = 0;
	f->base = 10;
	f->set = PF_DEC;
	f->ndig = 0;
	f->zeros = 0;
	f->fill = 0;
}

const char	*pf_flags(const char *s, t_fmt *f)
{
	while (*s == '-' || *s == '0' || *s == '#' || *s == '+' || *s == ' ')
	{
		if (*s == '-')
			f->left = 1;
		else if (*s == '0')
			f->zero = 1;
		else if (*s == '#')
			f->hash = 1;
		else if (*s == '+')
			f->plus = 1;
		else
			f->space = 1;
		s++;
	}
	return (s);
}

const char	*pf_width(const char *s, t_fmt *f)
{
	while (*s >= '0' && *s <= '9')
	{
		f->width = f->width * 10 + (*s - '0');
		s++;
	}
	return (s);
}

const char	*pf_prec(const char *s, t_fmt *f)
{
	if (*s != '.')
		return (s);
	s++;
	f->prec = 0;
	while (*s >= '0' && *s <= '9')
	{
		f->prec = f->prec * 10 + (*s - '0');
		s++;
	}
	return (s);
}
