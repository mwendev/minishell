/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:14:14 by mwen              #+#    #+#             */
/*   Updated: 2021/12/12 13:57:14 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_fd(int cmd_nb, t_data *data)
{
	if (cmd_nb == 0)
	{
		if (dup2(data->pipe_fd[1] , STDOUT_FILENO) < 0)
			return (error(data, "dup failed", 0));
		close(data->pipe_fd[0]);
	}
	else if (cmd_nb > 0)
	{
		if (dup2(data->pipe_fd[(cmd_nb - 1) * 2], STDIN_FILENO) < 0)
			return (error(data, "dup failed", 0));
		close(data->pipe_fd[(cmd_nb - 1) * 2 + 1]);
		if (cmd_nb != 999)
		{
			if (dup2(data->pipe_fd[cmd_nb * 2 + 1], STDOUT_FILENO) < 0)
				return (error(data, "dup failed", 0));
			close(data->pipe_fd[cmd_nb * 2]);
		}
	}
}

void	execute_fork(char *cmd, t_data *data, int cmd_nb)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (error(data, "fork failed", 0));
	else if (!pid)
	{
		if (cmd_nb >= 0)
			execute_fd(cmd_nb, data);
		// if (execve(data->cmd_with_path, data->argv, data->envp) < 0)
			// return (error(data, "exec failed", 0));
	}
	waitpid(-1, NULL, 0);
}

void	execute_pipe(char **pipe_cmd, t_data *data)
{
	int	i;

	data->pipe_fd = ft_calloc(data->pipe_nb * 2, sizeof(int));
	i = -1;
	while (pipe_cmd[++i])
	{
		if (pipe_cmd[i + 1])
		{
			if (pipe(data->pipe_fd + i * 2) == -1)
				return (error(data, "pipe failed", 0));
		}
		else
			i = 999;
		execute_fork(pipe_cmd[i], data, i);
	}
	i = data->pipe_nb * 2;
	while (i--)
		close(data->pipe_fd[i - 1]);
}

void	execute_command(char *cmd, t_data *data)
{
	char	**pipe_cmd;
	int		i;

	i = -1;
	if (ft_strchr(cmd, '|'))
	{
		pipe_cmd = ft_split(cmd, '|');
		while (pipe_cmd[++i])
			check_command(pipe_cmd[i], data);
		data->pipe_nb = i - 1;
	}
	else
		check_command(cmd, data);
	if (data->not_valid)
		return ;
	else if (ft_strlen(data->argv[0]) == 2
		&& ft_strncmp(data->argv[0], "cd", 2) == 0)
		return (change_directory(data));
	else if (data->pipe_nb)
		execute_fork(cmd, data, -1);
	else
		execute_pipe(pipe_cmd, data);
}