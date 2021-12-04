/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:37:04 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:26:37 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	int	out;

	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		out = 1;
	else
		out = 0;
	return (out);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	neg;

	i = 0;
	while (ft_isspace(*(nptr + i)) != 0)
		i++;
	result = 0;
	if (*(nptr + i) == '-')
		neg = 1;
	else
		neg = 0;
	if (*(nptr + i) == '-' || *(nptr + i) == '+')
		i++;
	while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		if (neg)
			result = (result * 10) - (*(nptr + i) - '0');
		else
			result = (result * 10) + (*(nptr + i) - '0');
		i++;
	}
	return (result);
}
