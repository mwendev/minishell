/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 20:31:24 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/10 22:51:09 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <stdlib.h>

char	*ft_putnbr_ll(long long nbr, char *pre)
{
	char	*str;
	char	*str1;
	char	*str2;

	str = ft_itoa_ll(nbr);
	if (pre != 0)
	{
		str2 = ft_strdup(pre);
		if (str2 != 0)
		{
			str1 = str;
			str = ft_strjoin(str2, str1);
			free(str1);
			free(str2);
		}
	}
	return (str);
}

char	*ft_putnbr_ull(unsigned long long nbr, char *pre)
{
	char	*str;
	char	*str1;
	char	*str2;

	str = ft_itoa_ull(nbr);
	if (pre != 0)
	{
		str2 = ft_strdup(pre);
		if (str2 != 0)
		{
			str1 = str;
			str = ft_strjoin(str2, str1);
			free(str1);
			free(str2);
		}
	}
	return (str);
}
