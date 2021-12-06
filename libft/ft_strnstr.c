/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:21:34 by mwen              #+#    #+#             */
/*   Updated: 2021/06/14 19:57:46 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	llen;

	i = 0;
	llen = ft_strlen((char *)little);
	if (llen == 0 || big == little)
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] && j < llen && i + j < len
			&& big[i + j] == little[j])
			j++;
		if (j == llen)
			return ((char *)big + i);
		i++;
	}
	return (0);
}
