/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_memcpy.c                                         +:      :+:    :+:   */
/*                                                       +:+ +:+         +:+  */
/*   By: anwar <anwar@student.42.fr>                     +#+  +:+       +#+   */
/*                                                       +#+#+#+#+#+   +#+    */
/*   Created: 2026/08/22 23:37:05 by anwar               #+#+    #+#          */
/*   Updated: 2026/08/22 23:37:05 by anwar               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!d && !s)
		return (NULL);
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dst);
}
