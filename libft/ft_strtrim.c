/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:28:00 by mwen              #+#    #+#             */
/*   Updated: 2021/05/17 03:18:44 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*x;

	if (!s1)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len - 1]))
		len--;
	x = ft_substr(s1, 0, len);
	return (x);
}
