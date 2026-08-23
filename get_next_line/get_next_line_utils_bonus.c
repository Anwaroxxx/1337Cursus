/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 15:03:31 by anwar             #+#    #+#             */
/*   Updated: 2026/08/22 20:16:05 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_copy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

int	gnl_grow(t_gnl *g)
{
	char	*nbuf;
	size_t	ncap;

	ncap = g->cap * 2;
	if (ncap == 0)
		ncap = BUFFER_SIZE;
	nbuf = malloc(ncap);
	if (!nbuf)
		return (0);
	gnl_copy(nbuf, g->buf, g->len);
	free(g->buf);
	g->buf = nbuf;
	g->cap = ncap;
	return (1);
}
