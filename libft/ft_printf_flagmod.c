/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flagmod.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 21:20:09 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/11 20:48:24 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <stdlib.h>

int	ft_padding_nbr(char *str, int flags[7])
{
	int		arr[4];
	char	c;

	c = ' ';
	ft_bzero(arr, 4 * sizeof(int));
	if (flags[1] == 1 && flags[2] == 0)
	{
		c = '0';
		if (*str == '-')
		{
			arr[1] += ft_putstr("-", 1);
			arr[2] = 1;
			flags[5] -= 1;
		}
		if (flags[0] == 1 && *str == '0')
		{
			arr[3] = 2;
			arr[1] += ft_putstr(str, arr[3]);
			flags[5] -= 2;
		}
	}
	arr[0] = ft_strlen(str + arr[2] + arr[3]);
	arr[1] += ft_padding_str(str + arr[2] + arr[3], flags, arr[0], c);
	free(str);
	return (arr[1]);
}

int	ft_padding_str(char *str, int *flags, int len, char c)
{
	int		res;

	res = 0;
	if (flags[2] == 0)
	{
		while (flags[5] > len)
		{
			res += ft_putstr(&c, 1);
			flags[5] -= 1;
		}
	}
	if ((int) ft_strlen(str) > 0 && (int) ft_strlen(str) < len)
		len = ft_strlen(str);
	res += ft_putstr(str, len);
	c = ' ';
	if (flags[2] == 1)
	{
		while (flags[5] > len)
		{
			res += ft_putstr(&c, 1);
			flags[5] -= 1;
		}
	}
	return (res);
}

char	*ft_print_handle_prec_A(char *str, int *flags, int len)
{
	int		i;
	char	*str1;
	char	*str2;

	len--;
	str1 = ft_substr(str, 1, len);
	free(str);
	str2 = malloc(((flags[6] - len) + 1 + 1) * sizeof(char));
	if (!str2)
		return (NULL);
	*str2 = '-';
	i = 1;
	while (i + len - 1 < flags[6])
	{
		*(str2 + i) = '0';
		i++;
	}
	*(str2 + i) = '\0';
	str = ft_strjoin(str2, str1);
	free(str1);
	free(str2);
	flags[1] = 0;
	return (str);
}

char	*ft_strjoin_wfree(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (str);
}

char	*ft_print_handle_prec(char *str, int *flags)
{
	int		i;
	int		len;
	char	*str1;
	char	*str2;

	len = (int) ft_strlen(str);
	if (flags[6] != -1 && len - 1 < flags[6] && *str == '-')
		str = ft_print_handle_prec_A(str, flags, len);
	else if (flags[6] != -1 && len < flags[6])
	{
		str1 = str;
		str2 = malloc(((flags[6] - len) + 1) * sizeof(char));
		if (!str2)
			return (NULL);
		i = 0;
		while (i + len < flags[6])
		{
			*(str2 + i) = '0';
			i++;
		}
		*(str2 + i) = '\0';
		str = ft_strjoin_wfree(str2, str1);
		flags[1] = 0;
	}
	return (str);
}
