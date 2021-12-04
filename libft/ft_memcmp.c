/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:29:19 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:02:06 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;
	int				out;

	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	i = 0;
	out = 0;
	while (i < n)
	{
		if (*(c1 + i) != *(c2 + i))
		{
			out = *(c1 + i) - *(c2 + i);
			i = n;
		}
		i++;
	}
	return (out);
}
