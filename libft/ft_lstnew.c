/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 14:33:17 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 21:58:29 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = (t_list *) malloc(sizeof(t_list));
	if (new_lst != 0)
	{
		new_lst->content = content;
		new_lst->next = 0;
	}
	return (new_lst);
}
