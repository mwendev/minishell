/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:20:42 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/10 20:22:04 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		flags[9];
	va_list	arg_list;

	va_start(arg_list, str);
	i = 0;
	ft_bzero(flags, 9 * sizeof(int));
	while (*(str + i))
	{
		if (str[i] == '%')
		{
			i++;
			ft_bzero(flags, 8 * sizeof(int));
			ft_get_flags(str, &i, flags);
			ft_get_width(str, &i, flags, &arg_list);
			ft_get_precision(str, &i, flags, &arg_list);
			flags[8] += ft_print_handler(str, &i, &arg_list, flags);
		}
		else
			flags[8] += ft_putstr((char *)(str + i), 1);
		i++;
	}
	va_end(arg_list);
	return (flags[8]);
}
