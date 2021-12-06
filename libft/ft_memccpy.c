/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:25:30 by mwen              #+#    #+#             */
/*   Updated: 2021/05/23 22:58:58 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char *)s1 = *(unsigned char *)s2;
		if (*(unsigned char *)s2 == (unsigned char)c)
		{
			*(unsigned char *)s1 = *(unsigned char *)s2;
			return (s1 + 1);
		}
		s1++;
		s2++;
	}
	return (NULL);
}
