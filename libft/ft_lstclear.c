/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:16:58 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:16:58 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list			*tmp;
	t_list			*node;

	if (!*lst)
		return ;
	node = *lst;
	while (node)
	{
		tmp = node;
		node = node->next;
		if (del)
			del(tmp->content);
		free(tmp);
	}
	*lst = 0;
}
