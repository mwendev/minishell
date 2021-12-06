/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:06:59 by mwen              #+#    #+#             */
/*   Updated: 2021/05/17 14:35:21 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	dst = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < ft_strlen(s))
	{
		dst[i] = (*f)(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
