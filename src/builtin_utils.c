/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:59:35 by mwen              #+#    #+#             */
/*   Updated: 2022/01/06 23:07:39 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_fd(int cmd_nb, t_data *data, int end)
{
	if (!end)
	{
		if (dup2(data->pipe_fd[cmd_nb * 2 + 1], STDOUT_FILENO) < 0)
			return (error(data, "Dup failed", 1, 'e'));
	}
	else
	{
		if (data->redir_append)
			redir_fd(data, data->redir_append_fd, 2);
		else if (data->redir_to)
			redir_fd(data, data->redir_to_fd, 3);
	}
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
