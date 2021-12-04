/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 21:14:25 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:20:02 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	size_src;
	size_t	i;
	size_t	out;

	size_dst = ft_strlen(dst);
	size_src = ft_strlen(src);
	if (size <= size_dst)
		out = size + size_src;
	else
	{
		i = 0;
		while (i + size_dst + 1 < size && *(src + i))
		{
			*(dst + size_dst + i) = *(src + i);
			i++;
		}
		*(dst + size_dst + i) = '\0';
		out = size_dst + size_src;
	}
	return (out);
}
