/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:17:04 by mwen              #+#    #+#             */
/*   Updated: 2021/06/15 18:57:31 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	i = 0;
	if ((size_t)s1 - (size_t)s2 < n)
	{
		i = n - 1;
		while (i < n)
		{
			((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
			i++;
		}
	}
	return (s1);
}
