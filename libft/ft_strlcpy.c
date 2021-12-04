/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:24:01 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 23:52:42 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	size_src;
	size_t	i;

	size_src = ft_strlen(src);
	i = 0;
	while (*(src + i) && i + 1 < size)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (size != 0)
		*(dst + i) = '\0';
	return (size_src);
}
