/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:20:41 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:16:36 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	c_char;

	p = (unsigned char *) s;
	c_char = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		*(p + i) = c_char;
		i++;
	}
	return (s);
}
