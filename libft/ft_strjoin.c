/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strjoin.c                                        +:      :+:    :+:   */
/*                                                       +:+ +:+         +:+  */
/*   By: anwar <anwar@student.42.fr>                     +#+  +:+       +#+   */
/*                                                       +#+#+#+#+#+   +#+    */
/*   Created: 2026/08/22 23:37:49 by anwar               #+#+    #+#          */
/*   Updated: 2026/08/22 23:37:49 by anwar               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	joined = (char *)malloc(l1 + l2 + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, l1);
	ft_memcpy(joined + l1, s2, l2);
	joined[l1 + l2] = '\0';
	return (joined);
}
