/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:14:14 by mwen              #+#    #+#             */
/*   Updated: 2021/12/19 17:30:15 by aignacz          ###   ########.fr       */
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
		//else
			//run_builtin();
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
		if (!create_command(pipe_cmd[i], data))
			check_path(pipe_cmd[i], data);
		if (pipe_cmd[i + 1])
		{
			if (pipe(data->pipe_fd + i * 2) == -1)
				return (error(data, "pipe failed", 0));
			else
				execute_fork(pipe_cmd[i], data, i, 0);
		}
		else
			execute_fork(pipe_cmd[i], data, i, 1);
		if (i >= 1)
			close_pipe(i, data);
		//free(data->cmd_with_path);
		waitpid(-1, NULL, 0);
	}
	//free_pipe(pipe_cmd, data);
}

void	execute_command(t_data *data)
{
	char	*cmd;

	cmd = *(data->cmd);
	if (!create_command(cmd, data))
		check_path(cmd, data);
	//then check if it's builtin:
	if (ft_strlen(data->argv[0]) == 2
		&& ft_strncmp(data->argv[0], "cd", 2) == 0)
		return (change_directory(data));
	execute_fork(cmd, data, -1, 1);
	free(data->cmd_with_path);
	waitpid(-1, NULL, 0);
}
