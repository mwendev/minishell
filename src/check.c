/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:08:04 by mwen              #+#    #+#             */
/*   Updated: 2021/12/12 17:52:13 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_nb(char *cmd, t_data *data)
{
	char	**pipe_cmd;
	int		i;

	i = -1;
	pipe_cmd = ft_split(cmd, '|');
	while (pipe_cmd[++i])
		continue;
	data->pipe_nb = i - 1;
	free_split(pipe_cmd);
	if (data->pipe_nb > 0)
		return (1);
	else
		return (0);
}

char	*check_path_in_env(char **envp, t_data *data)
{
	int		i;
	char	*path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])))
		{
			path = envp[i] + 5;
			return (path);
		}
	}
	error(data, "No path found in env", 0);
	return (NULL);
}

int	create_command(char *cmd, t_data *data)
{
	if (ft_strchr(cmd, '"') == NULL && ft_strchr(cmd, '\'') == NULL
		&& ft_strchr(cmd, ' '))
		data->argv = ft_split(cmd, ' ');
	else if (ft_strchr(cmd, ' '))
		data->argv = ft_split(cmd, ' '); //data->argv = split_with_comma(line);
	else
	{
		data->argv = ft_calloc(2, sizeof(char *));
		data->argv[0] = ft_strdup(cmd);
	}
	if (ft_strncmp(data->argv[0], "cd", ft_strlen(data->argv[0])) == 0
		&& (ft_strncmp(data->argv[0], "cd", 2) == 0))
	{
		data->cmd_with_path = ft_strdup(data->argv[0]);
		return (1);
	}
	return (0);
}

int	check_command(char *cmd, t_data *data)
{
	char	*env_paths;
	char	**split;
	char	*full_path;
	char	*add_slash;
	int		i;

	i = -1;
	env_paths = check_path_in_env(data->envp, data);
	if (!env_paths)
	{
		error(data, "no env path found", 0);
		return (2);
	}
	if (create_command(cmd, data))
		return (0);
	split = ft_split(env_paths, ':');
	while (split[++i])
	{
		if (ft_strchr(data->argv[0], '/'))
			full_path = ft_strdup(data->argv[0]);
		else
		{
			add_slash = ft_strjoin(split[i], "/");
			full_path = ft_strjoin(add_slash, data->argv[0]);
			free(add_slash);
		}
		if (!access(full_path, X_OK))
		{
			data->cmd_with_path = full_path;
			return (0);
		}
		free(full_path);
	}
	printf("%s: command not found\n", cmd);
	free(cmd);
	free_split(split);
	data->not_valid = 1;
	return (1);
}
