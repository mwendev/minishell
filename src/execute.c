/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:14:14 by mwen              #+#    #+#             */
/*   Updated: 2021/12/19 18:18:57 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_fd(int cmd_nb, t_data *data, int end)
{
	if (cmd_nb > 0)
	{
		if (dup2(data->pipe_fd[(cmd_nb - 1) * 2], STDIN_FILENO) < 0)
			return (error(data, "dup failed", 0));
		close(data->pipe_fd[(cmd_nb - 1) * 2 + 1]);
	}
	if (!end)
	{
		if (dup2(data->pipe_fd[cmd_nb * 2 + 1], STDOUT_FILENO) < 0)
			return (error(data, "dup failed", 0));
		close(data->pipe_fd[cmd_nb * 2]);
	}
}

void	execute_fork(char *cmd, t_data *data, int cmd_nb, int end)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (error(data, "fork failed", 0));
	else if (!pid)
	{
		execute_fd(cmd_nb, data, end);
		if (execve(data->cmd_with_path, data->argv, data->envp) < 0)
			error(data, "exec failed", 0);
	}
}

int	is_builtin(char *cmd, t_data *data)
{
	int		ret;

	ret = 1;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		ret = 1;
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		change_directory(data);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		ret = 1;
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		ret = 1;
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ret = 1;
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		ret = 1;
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		ret = 1;
	else
		ret = 0;
	return (ret);
}

void	execute_command(char *cmd, t_data *data, int cmd_nb, int end)
{
	if (is_builtin(cmd, data))
		return ;
	else if (!create_command(cmd, data))
	{
		check_path(cmd, data);
		execute_fork(cmd, data, cmd_nb, end);
		free(data->cmd_with_path);
		waitpid(-1, NULL, 0);
	}
}

void	execute_pipe(t_data *data)
{
	char	**pipe_cmd;
	int		i;

	data->pipe_fd = malloc(data->pipe_nb * 2 * sizeof(int));
	pipe_cmd = data->cmd;
	i = -1;
	while (pipe_cmd[++i])
	{
		if (pipe_cmd[i + 1])
		{
			if (pipe(data->pipe_fd + i * 2) == -1)
				return (error(data, "pipe failed", 0));
			else
				execute_command(pipe_cmd[i], data, i, 0);
		}
		else
			execute_command(pipe_cmd[i], data, i, 1);
		if (i >= 1)
			close_pipe(i, data);
		waitpid(-1, NULL, 0);
	}
}

