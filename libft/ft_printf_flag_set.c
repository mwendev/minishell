/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_set.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 23:31:25 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/11 21:24:47 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_get_flags(const char *arr, int *i, int *flag)
{
	int	stop;

	stop = 0;
	while (!stop && arr[*i])
	{
		if (arr[*i] == '#')
			flag[0] = 1;
		else if (arr[*i] == '0')
			flag[1] = 1;
		else if (arr[*i] == '-')
			flag[2] = 1;
		else if (arr[*i] == ' ')
			flag[3] = 1;
		else if (arr[*i] == '+')
			flag[4] = 1;
		else if (arr[*i] != '#' && arr[*i] != '0' && arr[*i] != '-'
			&& arr[*i] != '+' && arr[*i] != ' ')
			stop = 1;
		*i += 1;
	}
	if (stop)
		*i -= 1;
}

void	ft_get_width(const char *arr, int *i, int *flag, va_list *list)
{
	if (arr[*i] == '*')
	{
		flag[5] = va_arg(*list, int);
		*i += 1;
		if (flag[5] < 0)
		{
			flag[2] = 1;
			flag[5] = -1 * flag[5];
		}
	}
	else
	{
		while ((arr[*i] >= '0') && (arr[*i] <= '9'))
		{
			flag[5] = (flag[5] * 10) + ((arr[*i]) - '0');
			*i += 1;
		}
	}
}

void	ft_get_precision(const char *arr, int *i, int *flag, va_list *list)
{
	if (arr[*i] == '.')
	{
		*i += 1;
		if (arr[*i] == '*')
		{
			flag[6] = va_arg(*list, int);
			*i += 1;
		}
		else
		{
			if (arr[*i] == '-')
				flag[6] = -1;
			while (flag[6] >= 0 && (arr[*i] >= '0') && (arr[*i] <= '9'))
			{
				flag[6] = (flag[6] * 10) + ((arr[*i]) - '0');
				*i += 1;
			}
		}
	}
	else
		flag[6] = -1;
	if (flag[6] < 0)
		flag[6] = -1;
	else
		flag[1] = 0;
}

void	ft_get_conversion(const char *arr, int *i, int *flag)
{
	if (arr[*i] == 'l')
	{
		*i += 1;
		if (arr[*i] == 'l')
		{
			flag[7] = 2;
			*i += 1;
		}
		else
			flag[7] = 1;
	}
	else if (arr[*i] == 'h')
	{
		*i += 1;
		if (arr[*i] == 'h')
		{
			flag[7] = 4;
			*i += 1;
		}
		else
			flag[7] = 3;
	}
}
