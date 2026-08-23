/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 15:02:19 by anwar             #+#    #+#             */
/*   Updated: 2026/08/23 01:07:52 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	find_nl(t_gnl *c)
{
	size_t	i;

	i = c->pos;
	while (i < c->len)
	{
		if (c->buf[i] == '\n')
			return (i);
		i++;
	}
	return ((size_t)-1);
}

static char	*extract(t_gnl *c, size_t end)
{
	char	*line;

	line = malloc(end - c->pos + 1);
	if (!line)
		return (NULL);
	gnl_copy(line, c->buf + c->pos, end - c->pos);
	line[end - c->pos] = '\0';
	c->pos = end;
	if (c->pos == c->len)
	{
		c->pos = 0;
		c->len = 0;
	}
	return (line);
}

static void	*givup(t_gnl *c)
{
	free(c->buf);
	c->buf = NULL;
	c->len = 0;
	c->pos = 0;
	c->cap = 0;
	return (NULL);
}

static int	refill(int fd, t_gnl *c)
{
	ssize_t	bytes;

	if (c->pos > 0)
	{
		gnl_copy(c->buf, c->buf + c->pos, c->len - c->pos);
		c->len -= c->pos;
		c->pos = 0;
	}
	if (c->len == c->cap && !gnl_grow(c))
		return (-1);
	bytes = read(fd, c->buf + c->len, c->cap - c->len);
	if (bytes < 0)
		return (-1);
	c->len += (size_t)bytes;
	return (bytes > 0);
}

char	*get_next_line(int fd)
{
	static t_gnl	cache[GNL_MAX_FD];
	t_gnl			*c;
	size_t			nl;
	int				r;

	if (fd < 0 || fd >= GNL_MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	c = &cache[fd];
	nl = find_nl(c);
	while (nl == (size_t)-1)
	{
		r = refill(fd, c);
		if (r < 0)
			return (givup(c));
		if (r == 0)
		{
			if (c->pos == c->len)
				return (givup(c));
			return (extract(c, c->len));
		}
		nl = find_nl(c);
	}
	return (extract(c, nl + 1));
}
