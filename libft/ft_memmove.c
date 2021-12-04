/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:34:50 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:10:45 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	int		ni;
	char	*dst_p;

	dst_p = (char *) dest;
	ni = n;
	if (((char *) src) < dst_p && ((char *) src) + ni > dst_p)
	{
		i = ni - 1;
		while (i >= 0)
		{
			*(dst_p + i) = *((char *) src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < ni)
		{
			*(dst_p + i) = *((char *) src + i);
			i++;
		}
	}
	return (dst_p);
}
