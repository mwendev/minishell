/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:36:50 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:00:53 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const char	*src_p;
	char		*dest_p;
	size_t		i;

	src_p = (char *) src;
	dest_p = (char *) dest;
	i = 0;
	while (i < n)
	{
		*dest_p = *(src_p + i);
		dest_p++;
		if (*(src_p + i) == c)
			i = n;
		else
		{
			i++;
			if (i == n)
				dest_p = 0;
		}
	}
	if (n == 0)
		dest_p = 0;
	return (dest_p);
}
