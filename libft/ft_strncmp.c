/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:08:40 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/19 00:26:21 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;
	int				out;

	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	i = 0;
	out = 0;
	if (n == 0)
		out = 0;
	else
	{
		while (i < n - 1 && *(c1 + i) && *(c2 + i) && *(c1 + i) == *(c2 + i))
			i++;
		out = *(c1 + i) - *(c2 + i);
	}
	return (out);
}
