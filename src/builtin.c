/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:30:16 by aignacz           #+#    #+#             */
/*   Updated: 2022/01/05 21:02:31 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	print_echo(t_data *data)
{
	int	i;

	if (!ft_strncmp(data->argv[1], "-n", ft_strlen(data->argv[1])))
		i = 1;
	else
		i = 0;
	while (data->argv[++i])
		printf("%s ", data->argv[i]);
	printf("\n");
	data->exit_status = 0;
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
