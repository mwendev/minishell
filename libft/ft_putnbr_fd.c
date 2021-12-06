/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:56:51 by mwen              #+#    #+#             */
/*   Updated: 2021/05/12 14:04:05 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	covert_print(int n, int fd)
{
	int	a;
	int	b;

	if (n > 0)
	{
		a = n % 10;
		b = a + '0';
		a = n / 10;
		covert_print(a, fd);
		ft_putchar_fd(b, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n > 0)
		covert_print(n, fd);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
		covert_print(n, fd);
	}
	else if (n == 0)
		ft_putchar_fd('0', fd);
}
