/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:30:16 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/11 19:40:10 by aignacz          ###   ########.fr       */
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
