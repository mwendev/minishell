/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:59:13 by mwen              #+#    #+#             */
/*   Updated: 2021/10/12 20:32:00 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

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
