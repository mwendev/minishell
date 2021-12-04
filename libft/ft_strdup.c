/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:58:01 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:19:18 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_s;

	len = ft_strlen(s);
	new_s = malloc((len + 1) * sizeof(char));
	if (new_s != 0)
		ft_strlcpy(new_s, s, len + 1);
	return (new_s);
}
