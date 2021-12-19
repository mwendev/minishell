/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:09:54 by mwen              #+#    #+#             */
/*   Updated: 2021/12/19 22:21:13 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**create_envp(char **envp, t_data *data, char *target)
{
	int		i;
	char	**dup;

	i = -1;
	dup = (char **)malloc(sizeof(char *) * (data->envp_len + 1));
	if (dup)
	{
		dup[data->envp_len] = NULL;
		while (envp[++i])
			if (!target || ft_strncmp(envp[i], target, ft_strlen(target)))
				dup[i] = ft_strdup(envp[i]);
	}
	else
		error(data, "malloc for envp failed", 1);
	return (dup);
}
