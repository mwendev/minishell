/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:04:33 by mwen              #+#    #+#             */
/*   Updated: 2021/05/20 22:03:10 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		n = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
