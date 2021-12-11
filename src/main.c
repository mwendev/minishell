/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:13:07 by mwen              #+#    #+#             */
/*   Updated: 2021/12/11 20:31:57 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_data *data, char **environ)
{
	printf("\n---------------------------------------------\n");
	printf("--------------- Minishell 0.0 ---------------\n");
	printf("---------------------------------------------\n\n");
	data->end = 0;
	data->line = NULL;
	data->cmd = NULL;
	data->envp = environ;
	getcwd(data->path, PATH_MAX);
	data->prev_dir = ft_strdup(data->path);
}

void	destroy(t_data *data)
{
	int	i;

	if (*(data->cmd))
	{
		i = 0;
		while (*(data->cmd + i))
			i++;
		while (i-- > 0)
			free(*(data->cmd + i));
		free(data->cmd);
	}
}

void	execute_command(t_data *data)
{
	pid_t	pid;

	if (ft_strlen(data->argv[0]) == 2
		&& ft_strncmp(data->argv[0], "cd", 2) == 0)
		return (change_directory(data));
	pid = fork();
	if (pid < 0)
		perror("fork failed");
	else if (!pid)
	{
		if (execve(data->cmd_with_path, data->argv, data->envp) < 0)
			perror("exec failed");
		data->end = 1;
	}
	else
		waitpid(-1, NULL, 0);
}

char	*check_path_in_env(char **envp)
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
	perror("No path found in env");
	return (NULL);
}

int	create_command(char *line, t_data *data)
{
	if (ft_strchr(line, '"') == NULL && ft_strchr(line, '\'') == NULL
		&& ft_strchr(line, ' '))
		data->argv = ft_split(line, ' ');
	else if (ft_strchr(line, ' '))
		data->argv = ft_split(line, ' '); //data->argv = split_with_comma(line);
	else
	{
		data->argv = ft_calloc(2, sizeof(char *));
		data->argv[0] = ft_strdup(line);
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
	env_paths = check_path_in_env(data->envp);
	if (!env_paths)
		return (2);
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
	return (1);
}

void	split_commands(t_data *data)//path
{
	int		i;
	char	*temp;

	data->cmd = ft_split(data->line, ';');
	i = 0;
	while (*(data->cmd + i))
	{
		temp = ft_strtrim(*(data->cmd + i), " ");
		free(*(data->cmd + i));
		*(data->cmd + i) = temp;
		i++;
	}
}

int	main(void)
{
	char		*promt;
	t_data		data;
	int			i;
	extern char	**environ;

	initialize(&data, environ);
	while (!data.end)
	{
		getcwd(data.path, PATH_MAX);
		promt = ft_strjoin(data.path, ":> ");
		data.line = readline(promt);
		if (data.line && *(data.line))
			add_history(data.line);
		free(promt);
		split_commands(&data);
		i = 0;
		while (*(data.cmd + i))
		{
			if (!check_command(*(data.cmd + i), &data))
				execute_command(&data);
			i++;
		}
		if (data.cmd)
			free(data.cmd);
	}
	destroy(&data);
	return (0);
}
