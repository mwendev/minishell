/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:57:21 by mwen              #+#    #+#             */
/*   Updated: 2021/10/12 17:31:59 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	double_free(char **double_pointer)
{
	int	i;

	i = -1;
	while (double_pointer[++i])
		free(double_pointer[i]);
	free(double_pointer);
}

void	free_data(t_pd pdata)
{
	double_free(pdata.cmd);
	double_free(pdata.path);
}
