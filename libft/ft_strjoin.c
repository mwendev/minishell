/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:15:53 by mwen              #+#    #+#             */
/*   Updated: 2022/01/10 17:52:58 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
