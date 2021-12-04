/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:20:18 by mwen              #+#    #+#             */
/*   Updated: 2021/10/12 20:31:47 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	error_exit(char *msg, int i)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 1);
	exit (i);
}

void	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 1);
}
