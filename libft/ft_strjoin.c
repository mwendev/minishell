/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:08:49 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:19:39 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_s;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_s = malloc((len1 + len2 + 1) * sizeof(char));
	if (new_s != 0)
	{
		ft_strlcpy(new_s, s1, len1 + 1);
		ft_strlcpy(new_s + len1, s2, len2 + 1);
	}
	return (new_s);
}
