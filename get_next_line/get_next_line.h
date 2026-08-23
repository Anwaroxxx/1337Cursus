/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 21:14:03 by anwar             #+#    #+#             */
/*   Updated: 2026/08/20 11:52:07 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define GNL_MAX_FD 1024

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	char	*buf;
	size_t	len;
	size_t	pos;
	size_t	cap;
}	t_gnl;

char	*get_next_line(int fd);

int		gnl_grow(t_gnl *g);
void	gnl_copy(char *dst, const char *src, size_t n);

#endif
