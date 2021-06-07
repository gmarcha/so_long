/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:17:26 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:17:26 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_freelst(t_list *lst, void (*del)(void *))
{
	t_list			*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (del)
			del(tmp->content);
		free(tmp);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*new;
	t_list			*node;

	if (!lst)
		return (0);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == 0)
		return (0);
	new->content = f(lst->content);
	new->next = 0;
	node = new;
	lst = lst->next;
	while (lst)
	{
		node->next = (t_list *)malloc(sizeof(t_list));
		if (node->next == 0)
			return (ft_freelst(new, del));
		node->next->content = f(lst->content);
		node->next->next = 0;
		node = node->next;
		lst = lst->next;
	}
	return (new);
}
