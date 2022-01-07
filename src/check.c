/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:08:04 by mwen              #+#    #+#             */
/*   Updated: 2022/01/07 22:45:37 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_envplen(char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

char	*check_in_env(char **envp, char *to_check, t_data *data)
{
	int		i;
	int		j;
	char	*expanded_value;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], to_check, ft_strlen(to_check)))
		{
			while (envp[i][j] != '=')
				++j;
			expanded_value = envp[i] + j + 1;
			return (expanded_value);
		}
	}
	printf("%s: ", to_check);
	error(data, "not found in env\n", 0, 'p');
	return (NULL);
}

int	check_full_path(char *env_paths, char **split, t_data *data)
{
	char	*full_path;
	char	*add_slash;
	int		i;

	i = -1;
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
			return (1);
		}
		free(full_path);
		data->cmd_with_path = NULL;
	}
	return (0);
}

int	check_path(t_data *data)
{
	char	*env_paths;
	char	**split;
	int		i;

	i = -1;
	env_paths = check_in_env(data->envp, "PATH", data);
	if (!env_paths)
		return (2);
	split = ft_split(env_paths, ':');
	if (check_full_path(env_paths, split, data))
		return (free_split(split));
	else
	{
		free_split(split);
		data->not_valid = 1;
		data->exit_status = 127;
		return (printf("%s: command not found\n", data->argv[0]));
	}
}

int	check_line(t_data *data)
{
	int		inqoute;
	int		i;
	char	c;

	i = 0;
	inqoute = 0;
	while (*(data->line + i))
	{
		if (!inqoute && (*(data->line + i) == '"' || *(data->line + i) == '\''))
		{
			inqoute = 1;
			c = *(data->line + i);
		}
		else if (inqoute && *(data->line + i) == c)
			inqoute = 0;
		i++;
	}
	return (inqoute);
	while (!inqoute && --i >= 0 && *(data->line + i) != '|')
	{
		if (ft_isalpha((int) *(data->line + i)) || *(data->line + i) == '"'
			|| *(data->line + i) == '\'')
			return (0);
	}
	return (1);
}
