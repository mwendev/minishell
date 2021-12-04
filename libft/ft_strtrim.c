/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:21:56 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/26 19:56:03 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new_s;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (*(s1 + start) && ft_strchr(set, *(s1 + start)) != 0)
		start++;
	while (end > start && ft_strchr(set, *(s1 + end)) != 0)
		end--;
	new_s = ft_substr(s1, start, end - start + 1);
	return (new_s);
}
