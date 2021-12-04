/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:15:17 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/11 23:35:00 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

int	ft_check_arg(char *base)
{
	int	i;
	int	j;
	int	good;

	i = 0;
	good = 1;
	while (base[i] && good)
	{
		if (base[i] == '-' || base[i] == '+' || base[i] < 33 || base[i] > 126)
			good = 0;
		else
		{
			j = 0;
			while (j < i && good)
			{
				if (base[i] == base[j])
					good = 0;
				j++;
			}
		}
		i++;
	}
	if (!good)
		i = 0;
	return (i);
}

int	ft_get_lennbr(unsigned long long nbr, int base_num)
{
	int	len;
	int	neg;

	if (nbr < 0)
		neg = 1;
	else
		neg = 0;
	len = neg + 1;
	while (neg == 0 && nbr >= (unsigned int) base_num)
	{
		len++;
		nbr = nbr / base_num;
	}
	return (len);
}

char	*ft_put_in_base(unsigned long long nbr, char *base, int bnum, char *str)
{
	char				c;
	unsigned long long	nb2;

	nb2 = nbr / bnum;
	if (nbr < 0)
	{
		*str = '-';
		str++;
		nb2 = -1 * nb2;
		nbr = nbr % bnum;
		nbr = -1 * nbr;
	}
	else
		nbr = nbr % bnum;
	if (nb2 > 0)
		str = ft_put_in_base(nb2, base, bnum, str);
	c = base[nbr];
	*str = c;
	str++;
	return (str);
}

char	*ft_putnbr_base(unsigned long long nbr, char *base, char *pre)
{
	unsigned int	base_num;
	int				res;
	int				len;
	char			*str;
	char			*end;

	base_num = ft_check_arg(base);
	res = 0;
	str = 0;
	if (base_num > 1)
	{
		len = ft_get_lennbr(nbr, base_num) + ft_strlen(pre);
		str = malloc((len + 1) * sizeof(char));
		if (str != 0)
		{
			ft_memcpy(str, pre, ft_strlen(pre));
			end = ft_put_in_base(nbr, base, base_num, str + ft_strlen(pre));
			*end = '\0';
		}
	}
	return (str);
}
