/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:28:00 by mwen              #+#    #+#             */
/*   Updated: 2022/01/04 19:44:32 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;

	if (!s1 || !set)
		return (0);
	i = ft_strlen((char *)s1);
	--i;
	k = 0;
	while (i && ft_strchr(set, s1[i]) && (ft_strchr(set, s1[i + 1])
		|| ft_strchr(set, s1[i - 1])))
		i--;
	while (s1[k] && ft_strchr(set, s1[k]) && (ft_strchr(set, s1[k + 1])
		|| ft_strchr(set, s1[k - 1])))
		k++;
	if (k > i)
		return (ft_substr(s1, 0, 0));
	return (ft_substr(s1, k, i - k + 1));
}
