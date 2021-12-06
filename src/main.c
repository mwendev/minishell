/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:28:57 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/06 23:04:12 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_data *data)
{
	printf("Minishell 0.0\n");
	data->end = 0;
}

void	execute_command(char *line, t_data *data)
{
	pid_t pid;
	char **argv;

	if (ft_strchr(line, ' '))
		argv = ft_split(line, ' ');
	else
	{
		argv = ft_calloc (2, sizeof(char *));
		argv[0] = ft_strdup(line);
	}
	pid = fork();
	if (pid < 0)
		perror("fork failed");
	else if (!pid)
	{
		if (execve(data->cmd_with_path, argv, data->envp) < 0)
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
	path = NULL;
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

int	check_command(char *line, t_data *data)
{
	char	*env_paths;
	char	**split;
	char	*add_slash;
	char	*full_path;
	int		i;

	i = -1;
	env_paths = check_path_in_env(data->envp);
	if (!env_paths)
		return (2);
	split = ft_split(env_paths, ':');
	while (split[++i])
	{
		add_slash = ft_strjoin(split[i], "/");
		full_path = ft_strjoin(add_slash, line);
		free(add_slash);
		if (!access(full_path, X_OK))
		{
			free(line);
			data->cmd_with_path = full_path;
			return (0);
		}
		free(full_path);
	}
	printf("%s: command not found\n", line);
	free(line);
	return (1);
}

int	main(void)
{
	char	*line;
	t_data	data;
	extern char	**environ;

	data.end = 0;
	while (!data.end)
	{
		printf(">>>");
		line = readline(NULL);
		data.envp = environ;
		if (!check_command(line, &data))
			execute_command(line, &data);
	}
	return (0);
}
