/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:17:54 by mwen              #+#    #+#             */
/*   Updated: 2021/05/22 00:02:28 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	if (!lst)
		return (NULL);
	node = ft_lstnew(f(lst->content));
	if (!node)
		return (NULL);
	head = node;
	while (lst)
	{
		if (lst->next)
		{
			node->next = ft_lstnew(f(lst->next->content));
			if (!(node->next))
			{
				ft_lstclear(&node, del);
				return (NULL);
			}
			node = node->next;
		}
		lst = lst->next;
	}
	node->next = NULL;
	return (head);
}
