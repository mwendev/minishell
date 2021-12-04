/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:37:29 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/11 22:53:31 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

char	*ft_printf_utoa(va_list *arg_list, int *flags)
{
	unsigned long long	ull;
	char				*str;

	if (flags[7] == 1)
		ull = (unsigned long long) va_arg(*arg_list, unsigned long);
	else if (flags[7] == 2)
		ull = (unsigned long long) va_arg(*arg_list, unsigned long long);
	else if (flags[7] == 3)
		ull = (unsigned long long) va_arg(*arg_list, unsigned int);
	else
		ull = (unsigned long long) va_arg(*arg_list, unsigned int);
	if (ull == 0 && flags[6] == 0)
		str = ft_strdup("");
	else if (flags[3] == 1 && ull >= 0)
		str = ft_putnbr_ull(ull, " ");
	else
		str = ft_putnbr_ull(ull, NULL);
	return (str);
}

char	*ft_printf_itoa(va_list *arg_list, int *flags)
{
	long long	ull;
	char		*str;

	if (flags[7] == 1)
		ull = (long long) va_arg(*arg_list, long);
	else if (flags[7] == 2)
		ull = (long long) va_arg(*arg_list, long long);
	else if (flags[7] == 3)
		ull = (long long) va_arg(*arg_list, int);
	else
		ull = (long long) va_arg(*arg_list, int);
	if (ull == 0 && flags[6] == 0)
		str = ft_strdup("");
	else if (flags[3] == 1 && ull >= 0)
		str = ft_putnbr_ll(ull, " ");
	else
		str = ft_putnbr_ll(ull, NULL);
	return (str);
}

int	ft_print_diu(va_list *arg_list, int *flags, char c)
{
	int			res;
	char		*str;

	if (c == 'u' && flags[7] == 0)
		str = ft_printf_utoa(arg_list, flags);
	else
		str = ft_printf_itoa(arg_list, flags);
	str = ft_print_handle_prec(str, flags);
	res = ft_padding_nbr(str, flags);
	return (res);
}
