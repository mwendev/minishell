/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 00:22:58 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/28 22:41:37 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;
	int		stop;

	stop = 0;
	if (lst == 0)
		return (0);
	new_lst = ft_lstnew((*f)(lst->content));
	while (lst->next != 0 && !stop)
	{
		lst = lst->next;
		temp = ft_lstnew((*f)(lst->content));
		if (temp != 0)
			ft_lstadd_back(&new_lst, temp);
		else
			stop = 1;
	}
	if (stop)
		ft_lstclear(&new_lst, del);
	return (new_lst);
}
