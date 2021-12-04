/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 23:53:13 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 21:50:10 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop_back(t_list **lst)
{
	t_list	*last;
	t_list	*prev_last;

	last = ft_lstlast(*lst);
	if (last != 0)
	{
		prev_last = *lst;
		if (prev_last != last)
		{
			while (prev_last->next != last)
				prev_last = prev_last->next;
			prev_last->next = NULL;
		}
		else
			*lst = NULL;
	}
	return (last);
}
