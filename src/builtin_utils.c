/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:59:35 by mwen              #+#    #+#             */
/*   Updated: 2022/01/05 20:06:31 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_target(char *target)
{
	char	*ret;
	char	**split;

	split = ft_split(target, '=');
	ret = ft_strdup(split[0]);
	free_split(split);
	return (ret);
}

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
