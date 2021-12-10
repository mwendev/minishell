/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:13:07 by mwen              #+#    #+#             */
/*   Updated: 2021/12/10 17:09:02 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_data *data)
{
	printf("\n---------------------------------------------\n");
	printf("--------------- Minishell 0.0 ---------------\n");
	printf("---------------------------------------------\n\n");
	data->end = 0;
	data->line = NULL;
	data->cmd = NULL;
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

void	execute_command(char *line, t_data *data)
{
	pid_t	pid;
	char	**argv;

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

	//if you wanna check multiple commands here is what you coded
	/*
		data->argv = ft_split(line, ' ');
	data->argc = 0;
	while (*(data->argv + data->argc))
		data->argc++;
	printf("Number of arguments: %i\n", data->argc);
	*/
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

void	create_commands(t_data *data)
{
	int		i;
	char	*temp;

	data->cmd = ft_split(data->line, '|');
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
	char		path[PATH_MAX];
	t_data		data;
	int			i;
	extern char	**environ;

	initialize(&data);
	while (!data.end)
	{
		getcwd(path, PATH_MAX);
		promt = ft_strjoin(path, ":> ");
		data.line = readline(promt);
		free(promt);
		data.envp = environ;
		create_commands(&data);
		i = 0;
		while (*(data.cmd + i))
		{
			if (!check_command(*(data.cmd + i), &data))
				execute_command(*(data.cmd + i), &data);
			i++;
		}
		if (data.cmd)
			free(data.cmd);
	}
	destroy(&data);
	return (0);
}
