/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:14:14 by mwen              #+#    #+#             */
/*   Updated: 2021/12/19 22:31:49 by mwen             ###   ########.fr       */
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

int	is_builtin(char *arg, t_data *data)
{
	int	ret;

	ret = 1;
	if (ft_strlen(arg) == 4 && !ft_strncmp(arg, "echo", ft_strlen(arg)))
	{
		if (!ft_strncmp(data->argv[1], "-n", ft_strlen(data->argv[1])))
			printf("%s", data->argv[2]);
		else
			printf("%s\n", data->argv[1]);
	}
	else if (ft_strlen(arg) == 2 && !ft_strncmp(arg, "cd", ft_strlen(arg)))
		change_directory(data);
	else if (ft_strlen(arg) == 3 && !ft_strncmp(arg, "pwd", ft_strlen(arg)))
	{
		getcwd(data->path, PATH_MAX);
		printf("%s\n", data->path);
	}
	else if (ft_strlen(arg) == 6 && !ft_strncmp(arg, "export", ft_strlen(arg)))
		change_env(data, 1, data->argv[1]);
	else if (ft_strlen(arg) == 5 && !ft_strncmp(arg, "unset", ft_strlen(arg)))
		change_env(data, 2, data->argv[1]);
	else if (ft_strlen(arg) == 3 && !ft_strncmp(arg, "env", ft_strlen(arg)))
		change_env(data, 0, NULL);
	else if (ft_strlen(arg) == 4 && !ft_strncmp(arg, "exit", ft_strlen(arg)))
		ret = 1;
	else
		ret = 0;
	return (ret);
}

void	execute_command(char *cmd, t_data *data, int cmd_nb, int end)
{
	data->argv = split_with_comma(cmd, ' ', data);
	if (is_builtin(data->argv[0], data))
		return ;
	else
	{
		if (!check_path(cmd, data))
			execute_fork(cmd, data, cmd_nb, end);
		if (data->cmd_with_path)
			free(data->cmd_with_path);
		free_split(data->argv);
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
			{
				free(data->pipe_fd);
				return (error(data, "pipe failed", 0));
			}
			else
				execute_command(pipe_cmd[i], data, i, 0);
		}
		else
			execute_command(pipe_cmd[i], data, i, 1);
		if (i >= 1)
			close_pipe(i, data);
		waitpid(-1, NULL, 0);
	}
	free(data->pipe_fd);
}
