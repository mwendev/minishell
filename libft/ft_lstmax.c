/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:42:02 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/19 22:37:54 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstmax(t_list *lst)
{
	int max;

	max = 0;
	if (lst != NULL)
		max = *(int *)lst->content;
	while (lst != NULL)
	{
		if (max < *(int *) lst->content)
			max = *(int *) lst->content;
		lst = lst->next;
	}
	return (max);
}
