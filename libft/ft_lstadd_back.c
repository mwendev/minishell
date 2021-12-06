/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:50:57 by mwen              #+#    #+#             */
/*   Updated: 2021/05/21 22:53:50 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *neew)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = neew;
		}
		else
			*lst = neew;
	}
}
