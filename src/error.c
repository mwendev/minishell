/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:30:54 by mwen              #+#    #+#             */
/*   Updated: 2022/01/10 17:39:03 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(t_data *data, char *str, int end, char type)
{
	if (str && type == 'e')
		perror(str);
	else if (str && type == 'p')
		printf("%s", str);
	data->exit_status = 1;
	data->not_valid = 1;
	if (end)
	{
		destroy(data);
		exit(EXIT_FAILURE);
	}
	else
		destroy_redir(data);
}

int	free_split(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return (1);
	while (str[++i])
		free(str[i]);
	free(str);
	return (0);
}

void	destroy_redir(t_data *data)
{
	if (data->redir_from)
	{
		close(data->redir_from_fd);
		free_split(data->redir_from);
		data->redir_from = NULL;
	}
	else if (data->redir_stdin)
	{
		close(data->redir_stdin_fd);
		unlink("_tmp");
		free_split(data->redir_stdin);
		data->redir_stdin = NULL;
	}
	if (data->redir_append)
	{
		close(data->redir_append_fd);
		free_split(data->redir_append);
		data->redir_append = NULL;
	}
	else if (data->redir_to)
	{
		close(data->redir_to_fd);
		free_split(data->redir_to);
		data->redir_to = NULL;
	}
}

void	free_pipe(char **pipe_cmd, t_data *data)
{
	free_split(pipe_cmd);
	free(data->pipe_fd);
	data->pipe_fd = NULL;
}

void	close_pipe(int cmd_nb, t_data *data)
{
	close(data->pipe_fd[(cmd_nb - 1) * 2]);
	close(data->pipe_fd[(cmd_nb - 1) * 2 + 1]);
}
