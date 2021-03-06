/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 11:50:51 by mwen              #+#    #+#             */
/*   Updated: 2022/01/04 17:35:45 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!c)
		return (NULL);
	while (*s)
	{
		if (*(char *)s == c)
			return ((char *)s);
		s++;
	}
	if (*(char *)s == c)
		return ((char *)s);
	return (NULL);
}
