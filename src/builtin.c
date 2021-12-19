/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:30:16 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/19 17:49:19 by mwen             ###   ########.fr       */
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
		printf("cd: too many arguments\n");
	else
	{
		dir = get_dir_name(data);
		if (chdir(dir) == -1)
			printf("cd: no such file or directory: %s\n", dir);
		else
		{
			free(data->prev_dir);
			data->prev_dir = ft_strdup(data->path);
			getcwd(data->path, PATH_MAX);
		}
		free(dir);
	}
}

void	change_env(t_data *data)
{
	char	**old;

	old = data->envp;
	/*if export*/
	data->envp = ft_calloc(data->envp_len + 2, sizeof(char *));
	if (data->envp)
	{
		data->envp = create_envp(old, data);
		
	}
}

