/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strncmp.c                                        +:      :+:    :+:   */
/*                                                       +:+ +:+         +:+  */
/*   By: anwar <anwar@student.42.fr>                     +#+  +:+       +#+   */
/*                                                       +#+#+#+#+#+   +#+    */
/*   Created: 2026/08/22 23:36:33 by anwar               #+#+    #+#          */
/*   Updated: 2026/08/22 23:36:33 by anwar               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
