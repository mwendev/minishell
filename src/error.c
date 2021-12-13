/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:30:54 by mwen              #+#    #+#             */
/*   Updated: 2021/12/13 21:05:06 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(t_data *data, char *str, int end)
{
	perror(str);
	data->not_valid = 1;
	if (end)
		data->end = 1;
	return ;
}

void	free_split(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	close_pipe(int cmd_nb, t_data *data)
{
	close(data->pipe_fd[(cmd_nb - 1) * 2]);
	close(data->pipe_fd[(cmd_nb - 1) * 2 + 1]);
}
