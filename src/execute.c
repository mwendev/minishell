/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:14:14 by mwen              #+#    #+#             */
/*   Updated: 2021/12/11 22:34:38 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_fd(int *fd, int if_pipe, t_data *data)
{
	if (if_pipe == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (error(data, "dup failed", 0));
		close(fd[1]);
	}
	else if (if_pipe > 0)//dup multi pipes and close pipe
	{
		if (dup2(fd[0], STDIN_FILENO) < 0
			|| dup2(fd[1], STDOUT_FILENO) < 0)
			return (error(data, "dup failed", 0));
	}
	else if (if_pipe == 999)
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (error(data, "dup failed", 0));
}

void	execute_fork(char *cmd, t_data *data, int if_pipe)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (error(data, "pipe failed", 0));
	pid = fork();
	if (pid < 0)
		return (error(data, "fork failed", 0));
	else if (!pid)
	{
		if (if_pipe >= 0)
		{
			execute_fd(fd, if_pipe, data);
		}
		if (execve(data->cmd_with_path, data->argv, data->envp) < 0)
			return (error(data, "exec failed", 0));
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, 0);
}

void	execute_command(char *cmd, t_data *data)
{
	char	**pipe_cmd;
	int		i;

	if (ft_strlen(data->argv[0]) == 2
		&& ft_strncmp(data->argv[0], "cd", 2) == 0)
		return (change_directory(data));
	i = -1;
	pipe_cmd = NULL;
	if (ft_strchr(cmd, '|'))
	{
		pipe_cmd = ft_split(cmd, '|');
		while (pipe_cmd[++i])
			check_command(pipe_cmd[i], data);
		data->pipe_nb = i - 1;
		cmd = NULL;
	}
	else
		check_command(cmd, data);
	if (data->not_valid)
		return ;
	else
	{
		if (!pipe_cmd)
			execute_fork(cmd, data, -1);
		else
		{
			i = -1;
			while (pipe_cmd[++i])
			{
				if (!pipe_cmd[i + 1])
					i = 999;
				execute_fork(cmd, data, i);
			}
		}
	}
}