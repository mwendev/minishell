/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 00:34:16 by mwen              #+#    #+#             */
/*   Updated: 2021/05/20 22:11:16 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	len;

	if (!dst || !src)
		return (0);
	len = ft_strlen(src);
	if (dstsize != 0)
	{
		while (dstsize > 1 && *src)
		{
			*dst = *src;
			dst++;
			src++;
			dstsize--;
		}
		*dst = '\0';
	}
	return (len);
}
