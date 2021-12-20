/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:08:04 by mwen              #+#    #+#             */
/*   Updated: 2021/12/20 14:13:18 by mwen             ###   ########.fr       */
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
	env_paths = check_path_in_env(data->envp, data);
	if (!env_paths)
	{
		error(data, "no env path found", 0);
		return (2);
	}
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

/*int	check_line(t_data *data)
{
	int		var;
	int		i;
	char	*last_pipe;
	char	*last_quote;
	char	*last_dquote;

	if (check_quotes(data))
		return (1);
	last_pipe = ft_strrchr(data->line, '|');
	last_dquote = ft_strrchr(data->line, '"');
	last_quote = ft_strrchr(data->line, '\'');
	i = 0;
	var = 0;
	while (last_pipe && *(last_pipe + i) && !var)
		var = ft_isalpha((int) *(last_pipe + i++));
	if (last_pipe == NULL || (last_quote != NULL && last_pipe < last_quote)
		|| (last_dquote != NULL && last_pipe < last_dquote) || var)
		return (0);
	return (1);
}
*/