/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 23:06:36 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/15 22:44:30 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop_front(t_list **lst)
{
	t_list	*first;

	first = *lst;
	if (first != NULL)
	{
		*lst = first->next;
		first->next = NULL;
	}
	return (first);
}
