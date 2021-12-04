/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:59:13 by mwen              #+#    #+#             */
/*   Updated: 2021/10/12 18:00:56 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strchr(const char *s, int c)
{
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
