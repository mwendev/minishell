/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 20:31:24 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/10 20:54:28 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

static int	ft_get_len_ll(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static int	ft_get_len_ull(unsigned long long n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa_ll(long long n)
{
	int		len;
	int		pre;
	char	*str;

	len = ft_get_len_ll(n);
	str = malloc((len + 2) * sizeof(char));
	if (str != 0)
	{
		*(str + len + 1) = '\0';
		pre = 1;
		if (n < 0)
		{
			*str = '-';
			pre = -1;
		}
		*(str + len) = pre * (n % 10) + '0';
		while (n / 10 != 0)
		{
			n = n / 10;
			len--;
			*(str + len) = pre * (n % 10) + '0';
		}
	}
	return (str);
}

char	*ft_itoa_ull(unsigned long long n)
{
	int		len;
	int		pre;
	char	*str;

	len = ft_get_len_ull(n);
	str = malloc((len + 2) * sizeof(char));
	if (str != 0)
	{
		*(str + len + 1) = '\0';
		pre = 1;
		if (n < 0)
		{
			*str = '-';
			pre = -1;
		}
		*(str + len) = pre * (n % 10) + '0';
		while (n / 10 != 0)
		{
			n = n / 10;
			len--;
			*(str + len) = pre * (n % 10) + '0';
		}
	}
	return (str);
}
