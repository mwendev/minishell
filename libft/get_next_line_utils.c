/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:51:32 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/15 23:48:07 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int	get_len_line(const char *s)
{
	int		i;

	i = 0;
	while (i < BUFFER_SIZE && s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s, int len)
{
	char	*new_s;
	int		i;

	new_s = malloc((len + 1) * sizeof(char));
	if (new_s != 0)
	{
		i = 0;
		while (*(s + i) && i < len)
		{
			*(new_s + i) = *(s + i);
			i++;
		}
		*(new_s + i) = '\0';
	}
	return (new_s);
}

void	*ft_memmove_gnl(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst_p;

	dst_p = (char *) dest;
	i = 0;
	while (i < n)
	{
		*(dst_p + i) = *((char *) src + i);
		i++;
	}
	*(dst_p + i) = 0;
	return (dst_p);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
	{
		len++;
	}
	return (len);
}

void	ft_bzero_gnl(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		*(p + i) = '\0';
		i++;
	}
}
