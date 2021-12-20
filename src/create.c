/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:09:54 by mwen              #+#    #+#             */
/*   Updated: 2021/12/20 12:31:09 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**create_envp(char **envp, t_data *data, char *target)
{
	int		i;
	int		j;
	char	**dup;

	i = -1;
	j = -1;
	dup = (char **)malloc(sizeof(char *) * (data->envp_len + 1));
	if (dup)
	{
		dup[data->envp_len] = NULL;
		while (envp[++i])
			if (!target || ft_strncmp(envp[i], target, ft_strlen(target)))
				dup[++j] = ft_strdup(envp[i]);
	}
	else
		error(data, "malloc for envp failed", 1);
	return (dup);
}

char	*create_echo_arg(char *str, t_data *data)
{
	char	*ret;
	char	**split;

	ret = NULL;
	if (data->echo_quote == 1)
		return (str);
	else
		ret = has_target(data->envp, str + 1);
		if (!ret)
		{
			if (ft_strnstr(str, "$?", ft_strlen(str)))
				return (ft_itoa(data->exit_status));
			else
				return ("");
		}
		else
			return (ret + ft_strlen(str));
}
