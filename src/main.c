/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:13:07 by mwen              #+#    #+#             */
/*   Updated: 2021/12/11 15:59:20 by aignacz          ###   ########.fr       */
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

char	*create_command(char *line, char *split, t_data *data)
{
	char	*full_path;
	char	*add_slash;

	if (ft_strchr(line, ' '))
		data->argv = ft_split(line, ' ');
	else
	{
		data->argv = ft_calloc (2, sizeof(char *));
		data->argv[0] = ft_strdup(line);
	}
	if (ft_strchr(data->argv[0], '/'))
		full_path = ft_strdup(data->argv[0]);
	else
	{
		add_slash = ft_strjoin(split, "/");
		full_path = ft_strjoin(add_slash, data->argv[0]);
		free(add_slash);
	}
	return (full_path);
}

int	check_command(char *line, t_data *data)
{
	char	*env_paths;
	char	**split;
	char	*full_path;
	int		i;

	i = -1;
	env_paths = check_path_in_env(data->envp);
	if (!env_paths)
		return (2);
	split = ft_split(env_paths, ':');
	while (split[++i])
	{
		full_path = create_command(line, split[i], data);
		if (!access(full_path, X_OK))
		{
			data->cmd_with_path = full_path;
			return (0);
		}
		free(full_path);
	}
	printf("%s: command not found\n", line);
	free(line);
	return (1);
}

void	split_commands(t_data *data)//path
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

	initialize(&data, environ);
	while (!data.end)
	{
		getcwd(path, PATH_MAX);
		promt = ft_strjoin(path, ":> ");
		data.line = readline(promt);
		if (data.line && *(data.line))
			add_history(data.line);
		free(promt);
		split_commands(&data);
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
