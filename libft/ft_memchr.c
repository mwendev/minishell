/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:15:25 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:01:30 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*out;
	unsigned char	ch;
	size_t			i;

	ch = (unsigned char) c;
	p = (unsigned char *) s;
	i = 0;
	out = 0;
	while (i < n)
	{
		if (*(p + i) == ch)
		{
			out = (p + i);
			i = n;
		}
		else
			i++;
	}
	return ((void *) out);
}
