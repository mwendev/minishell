/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:32:04 by mbarut            #+#    #+#             */
/*   Updated: 2021/10/30 17:19:03 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_cd(t_data *d, char **args)
{
	if (d->n_pipe > 0)
		return ;
	handle_input(d, args);
	if (d->flag_input)
		ft_split_delete_last(args);
	handle_output(d, args);
	if (!args[1] || (args[1] && ft_strcmp(args[1], "~") == 0
			&& ft_strlen(args[1]) == 1))
		chdir(getenv("HOME"));
	else if (args[1])
	{
		if (args[2])
		{
			printf("bash: cd: too many arguments\n");
			d->exit_status = 1;
			return ;
		}
		else if (chdir(args[1]) != 0)
		{
			printf("bash: cd: %s: No such file or directory\n", args[1]);
			d->exit_status = 1;
			return ;
		}
	}
	d->exit_status = 0;
}

static int	find_unset(t_data *d, char **args)
{
	int		i;
	char	*env_tmp;

	i = 0;
	while (d->envv[i])
	{
		env_tmp = ft_strdup(d->envv[i]);
		*(ft_strchr(env_tmp, '=')) = '\0';
		if (ft_strcmp(env_tmp, args[1]) == 0)
		{
			free(env_tmp);
			return (i);
		}
		free(env_tmp);
		i++;
	}
	return (-1);
}

static char	**ft_unset_helper(char **arr, int index)
{
	char	**new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new = (char **)malloc(sizeof(char *) * (ft_strarrlen(arr) + 1));
	while (i < ft_strarrlen(arr))
	{
		if (i == index)
			i++;
		new[k] = ft_strdup(arr[i]);
		i++;
		k++;
	}
	new[k] = NULL;
	ft_split_free(arr);
	return (new);
}

void	ft_unset(t_data *d, char **args)
{
	if (d->n_pipe == 0)
	{
		handle_input(d, args);
		handle_output(d, args);
	}
	if (d->n_pipe > 0 || !args[1])
	{
		d->exit_status = 1;
		return ;
	}
	if (find_unset(d, args) > 0)
	{
		d->envv = ft_unset_helper(d->envv, find_unset(d, args));
		d->exit_status = 0;
	}
	else
	{
		d->exit_status = 1;
		return ;
	}
}

/* All built-ins go through here */
void	handle_builtins(t_data *d, char **args)
{
	char	*x;

	x = args[skip_to_executable(args)];
	x = check_env(d, x);
	if (!ft_strcmp(x, "echo"))
		ft_echo(d, args);
	else if (!ft_strcmp(x, "cd"))
		ft_cd(d, args);
	else if (!ft_strcmp(x, "pwd"))
		ft_pwd(d, args);
	else if (!ft_strcmp(x, "export"))
		ft_export(d, args);
	else if (!ft_strcmp(x, "unset"))
		ft_unset(d, args);
	else if (!ft_strcmp(x, "env"))
		ft_env(d, args);
	else if (!ft_strcmp(x, "exit"))
		ft_exit(args);
}
