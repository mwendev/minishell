/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 11:44:26 by mwen              #+#    #+#             */
/*   Updated: 2021/06/17 19:32:35 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*min_int(void)
{
	char	*output;

	output = (char *)malloc(20 * sizeof(char));
	if (!output)
		return (NULL);
	else
		ft_memcpy(output, "-9223372036854775807", 20);
	return (output);
}

static int	get_len(long long n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	convert(int len, int neg, long long n, char *output)
{
	char	nb;

	output[len] = '\0';
	len--;
	while (len > neg)
	{
		nb = (n % 10) + '0';
		output[len] = nb;
		n = n / 10;
		len--;
	}
	output[len] = n + '0';
	if (neg)
		output[0] = '-';
}

char	*ft_itoa(long long n)
{
	int		len;
	int		neg;
	char	*output;

	len = 0;
	neg = 0;
	if (n == -9223372036854775807)
		return (min_int());
	if (n < 0)
	{
		len++;
		n *= -1;
		neg = 1;
	}
	len += get_len(n);
	output = (char *)malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	convert(len, neg, n, output);
	return (output);
}
