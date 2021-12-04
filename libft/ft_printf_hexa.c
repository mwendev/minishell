/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 23:11:12 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/11 23:27:15 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_xXp_to_str(unsigned long long p, int *flags, char c)
{
	char	*str;

	if (c == 'X')
	{
		if (flags[0] == 1)
			str = ft_putnbr_base(p, "0123456789ABCDEF", "0X");
		else
			str = ft_putnbr_base(p, "0123456789ABCDEF", NULL);
	}
	else
	{
		if (c == 'p' || flags[0] == 1)
			str = ft_putnbr_base(p, "0123456789abcdef", "0x");
		else
			str = ft_putnbr_base(p, "0123456789abcdef", NULL);
	}
	return (str);
}

int	ft_print_xXp(va_list *arg_list, int *flags, char c)
{
	unsigned long long	p;
	int					res;
	char				*str;

	res = 0;
	if (c == 'p')
		p = (unsigned long long) va_arg(*arg_list, void *);
	else
		p = (unsigned long long) va_arg(*arg_list, unsigned int);
	if (c == 'p' && p == 0)
	{
		res = ft_print_nullp(flags);
		return (res);
	}
	if (p == 0 && flags[6] == 0)
		str = ft_strdup("");
	else
		str = ft_xXp_to_str(p, flags, c);
	if (str == 0)
		return (0);
	if (c != 'p')
		str = ft_print_handle_prec(str, flags);
	res = ft_padding_nbr(str, flags);
	return (res);
}
