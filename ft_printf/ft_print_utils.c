/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:27:39 by anwar             #+#    #+#             */
/*   Updated: 2026/08/05 11:52:28 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static size_t	local_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	pf_char(char c)
{
	return ((int)write(1, &c, 1));
}

int	pf_pad(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
	return (n);
}

int	pf_str(const char *s)
{
	return ((int)write(1, s, local_strlen(s)));
}

int	pf_digits(t_fmt *f)
{
	char	buf[32];
	size_t	i;
	size_t	n;

	n = f->val;
	i = f->ndig;
	while (i > 0)
	{
		i--;
		buf[i] = f->set[n % f->base];
		n /= f->base;
	}
	return ((int)write(1, buf, f->ndig));
}
