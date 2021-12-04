/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:28:19 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/04 23:17:54 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	int		found;
	size_t	little_len;
	size_t	i;
	char	*res;

	found = -1;
	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		found = 0;
	while ((i + little_len) <= len && *(big + i) && found != 0)
	{
		found = ft_memcmp(big + i, little, little_len);
		if (found != 0)
			i++;
	}
	if (found == 0)
		res = (char *) big + i;
	else
		res = 0;
	return (res);
}
