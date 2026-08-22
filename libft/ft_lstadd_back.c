/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_lstadd_back.c                                    +:      :+:    :+:   */
/*                                                       +:+ +:+         +:+  */
/*   By: anwar <anwar@student.42.fr>                     +#+  +:+       +#+   */
/*                                                       +#+#+#+#+#+   +#+    */
/*   Created: 2026/08/22 23:39:37 by anwar               #+#+    #+#          */
/*   Updated: 2026/08/22 23:39:37 by anwar               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new_node;
}
