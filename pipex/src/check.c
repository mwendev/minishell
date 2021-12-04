/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:45:10 by mwen              #+#    #+#             */
/*   Updated: 2021/10/13 21:25:10 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_args(int argc, char **argv)
{
	int	hyphen_num;
	int	i;

	hyphen_num = 0;
	i = 1;
	while (++i != (argc - 1))
	{
		if (argv[i][0] == '-')
			hyphen_num++;
	}
	if ((hyphen_num == 0 && argc != 5)
		|| (hyphen_num != 0 && argc - hyphen_num != 5))
		error_exit("Error: Invalid number of arguments", 0);
}

char	*check_flag(char *cmd)
{
	char	**split;
	char	*cmd_noflag;

	split = NULL;
	cmd_noflag = NULL;
	if (ft_strchr(cmd, ' '))
	{
		split = ft_split(cmd, ' ');
		{
			cmd_noflag = ft_strdup(split[0]);
			double_free(split);
			return (cmd_noflag);
		}
	}
	else
		return (ft_strdup(cmd));
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
	error("Error: No path found in env");
	return (NULL);
}

char	*check_path(char **path, char *cmd)
{
	int		i;
	char	*add_slash;
	char	*full_path;

	i = -1;
	cmd = check_flag(cmd);
	while (path[++i])
	{
		add_slash = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (!access(full_path, X_OK))
		{
			free(cmd);
			return (full_path);
		}
		free(full_path);
	}
	free(cmd);
	return (NULL);
}
