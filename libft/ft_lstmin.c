/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:42:02 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/26 12:32:55 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstmin(t_list *lst)
{
	int	min;

	min = 0;
	if (lst != NULL)
		min = *(int *)lst->content;
	while (lst != NULL)
	{
		if (min > *(int *) lst->content)
			min = *(int *) lst->content;
		lst = lst->next;
	}
	return (min);
}
