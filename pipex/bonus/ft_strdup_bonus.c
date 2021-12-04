/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:58:17 by mwen              #+#    #+#             */
/*   Updated: 2021/10/12 20:32:03 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = (char *)malloc(ft_strlen(s + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = ((char *)s)[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
