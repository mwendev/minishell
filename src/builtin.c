/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:30:16 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/29 13:19:25 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_dir_name(t_data *data)
{
	char	*dir;
	char	*temp;

	if (data->argv[1] == NULL)
		dir = ft_strdup(getenv("HOME"));
	else if (data->argv[1][0] == '~')
	{
		temp = ft_substr(data->argv[1], 1, ft_strlen(data->argv[1]) - 1);
		dir = ft_strjoin(getenv("HOME"), temp);
		free(temp);
	}
	else if (ft_strlen(data->argv[1]) == 1
		&& ft_strncmp(data->argv[1], "-", 1) == 0)
		dir = ft_strdup(data->prev_dir);
	else
		dir = ft_strdup(data->argv[1]);
	return (dir);
}

void	change_directory(t_data *data)
{
	int		i;
	char	*dir;

	i = 1;
	while (data->argv[i] != NULL)
		i++;
	if (i > 2)
	{
		data->exit_status = 1;
		printf("cd: too many arguments\n");
	}
	else
	{
		dir = get_dir_name(data);
		if (chdir(dir) == -1)
		{
			data->exit_status = 1;
			printf("cd: no such file or directory: %s\n", dir);
		}
		else
		{
			ft_strlcpy(data->prev_dir, data->path, PATH_MAX);
			getcwd(data->path, PATH_MAX);
		}
		free(dir);
	}
}

char	*has_target(char **envp, char *target)
{
	char	*ret;
	int		i;

	i = -1;
	ret = NULL;
	while (envp[++i])
	{
		ret = ft_strnstr(envp[i], target, ft_strlen(envp[i]));
		if (ret)
			return (ret);
	}
	return (ret);
}

char	*trim_target(char *target)
{
	char	*ret;
	char	**split;

	split = ft_split(target, '=');
	ret = ft_strdup(split[0]);
	free_split(split);
	return (ret);
}

void	change_env(t_data *data, int cmd, char *target)
{
	char	**old;
	char	*dup;
	int		i;

	old = data->envp;
	i = -1;
	if (cmd)
	{
		if (!has_target(old, target) && cmd == 2
			|| !ft_strchr(target, '=') && cmd == 1)
			return ;
		dup = ft_strdup(target);
		target = trim_target(target);
		if (has_target(old, target) && cmd == 2)
			data->envp_len--;
		else if (!has_target(old, target) && cmd == 1)
			data->envp_len++;
		data->envp = create_envp(old, data, target);
		if (cmd == 1)
			data->envp[data->envp_len - 1] = ft_strdup(dup);
		free(dup);
		free(target);
		free_split(old);
	}
	else
		while (old[++i])
			printf("%s\n", old[i]);
}
