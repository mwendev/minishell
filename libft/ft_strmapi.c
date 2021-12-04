/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 00:42:33 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:21:20 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*new_s;

	i = 0;
	len = ft_strlen(s);
	new_s = malloc((len + 1) * sizeof(char));
	if (new_s != 0)
	{
		while (*(s + i))
		{
			*(new_s + i) = (*f)(i, *(s + i));
			i++;
		}
		*(new_s + i) = '\0';
	}
	return (new_s);
}
