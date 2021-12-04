/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 00:06:08 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 21:50:55 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_p;
	t_list	*next;

	lst_p = *lst;
	while (lst_p != 0)
	{
		next = lst_p->next;
		ft_lstdelone(lst_p, del);
		lst_p = next;
	}
	*lst = 0;
}
