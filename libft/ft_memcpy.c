/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:32:46 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:02:43 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*src_p;
	char		*dest_p;
	size_t		i;

	src_p = (const char *) src;
	dest_p = (char *) dest;
	i = 0;
	while (i < n)
	{
		*(dest_p + i) = *(src_p + i);
		i++;
	}
	return (dest);
}
