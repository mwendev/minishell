/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 00:01:24 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/12 02:32:54 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_print_handler(const char *str, int *i, va_list *alist, int *flags)
{
	int	result;

	result = 0;
	ft_get_conversion(str, i, flags);
	if (*(str + *i) == 'c')
		result = ft_print_c(alist, flags);
	else if (*(str + *i) == 's')
		result = ft_print_s(alist, flags);
	else if (*(str + *i) == 'd' || *(str + *i) == 'i' || *(str + *i) == 'u')
		result = ft_print_diu(alist, flags, *(str + *i));
	else if (*(str + *i) == 'x' || *(str + *i) == 'X' || *(str + *i) == 'p')
		result = ft_print_xXp(alist, flags, *(str + *i));
	else if (*(str + *i) == 'n')
		ft_print_n(alist, flags);
	else if (*(str + *i) == '%')
		result = write(1, (str + *i), 1);
	else
		i--;
	i++;
	return (result);
}

int	ft_print_c(va_list *arg_list, int *flags)
{
	int		res;
	char	ch;

	ch = (char) va_arg(*arg_list, int);
	res = ft_padding_str(&ch, flags, 1, ' ');
	return (res);
}

int	ft_print_s(va_list *arg_list, int *flags)
{
	int		res;
	int		len;
	char	*str;

	str = va_arg(*arg_list, char *);
	if (str == NULL)
		res = ft_print_nulls(flags);
	else
	{
		len = ft_strlen(str);
		if (flags[6] != -1 && flags[6] < len)
			len = flags[6];
		res = ft_padding_str(str, flags, len, ' ');
	}
	return (res);
}

void	ft_print_n(va_list *arg_list, int *flags)
{
	int			*p;
	signed char	*pu;
	long		*pl;
	long long	*pll;

	if (flags[7] == 2)
	{
		pu = va_arg(*arg_list, signed char *);
		*pu = (signed char) flags[8];
	}
	else if (flags[7] == 3)
	{
		pl = va_arg(*arg_list, long *);
		*pl = (long) flags[8];
	}
	else if (flags[7] == 4)
	{
		pll = va_arg(*arg_list, long long *);
		*pll = (long long) flags[8];
	}
	else
	{
		p = va_arg(*arg_list, int *);
		*p = flags[8];
	}
}
