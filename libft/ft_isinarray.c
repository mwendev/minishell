/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinarray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:22:53 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/15 20:24:42 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isinarray(int *arr, int value, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (*(arr + i) == value)
			return (i);
		i++;
	}
	return (-1);
}
