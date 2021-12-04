/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 00:25:27 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/11 22:06:41 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_putstr(char *str, int len)
{
	int	res;

	res = write(1, str, len);
	if (res < 0)
		res = 0;
	return (res);
}

int	ft_print_nulls(int *flags)
{
	char	*str;
	int		res;

	res = 0;
	if (flags[6] == -1 || flags[6] >= 6)
	{
		str = ft_strdup("(null)");
		if (!str)
			return (res);
		res = ft_padding_str(str, flags, 6, ' ');
		free(str);
	}
	else
	{
		str = ft_strdup("");
		if (!str)
			return (res);
		res = ft_padding_str(str, flags, 0, ' ');
		free(str);
	}
	return (res);
}

int	ft_print_nullp(int *flags)
{
	char	*str;
	int		res;

	res = 0;
	str = ft_strdup("0x0");
	if (!str)
		return (res);
	res = ft_padding_str(str, flags, 3, ' ');
	free(str);
	return (res);
}
