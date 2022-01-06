/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:09:54 by mwen              #+#    #+#             */
/*   Updated: 2022/01/06 23:21:39 by mwen             ###   ########.fr       */
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
	dup = ft_calloc(data->envp_len + 1, sizeof(char *));
	if (dup)
	{
		while (envp[++i])
		{
			if (!target || ft_strncmp(envp[i], target, ft_strlen(target)))
				dup[++j] = ft_strdup(envp[i]);
		}
	}
	else
		error(data, "Malloc for envp failed", 1, 'e');
	return (dup);
}

char	*create_expand(int flag, char *src, t_data *data)
{
	char	*ret;
	char	*temp;

	if (flag && src[0] == '$' && ft_strncmp(src, "$?", ft_strlen(src)))
	{
		ret = check_in_env(data->envp, src + 1, data);
		if (ret)
		{
			free(src);
			return (ft_strdup(ret));
		}
	}
	return (src);
}

void	create_redir_string(t_data *data, char **ret, int i, int *start_len)
{
	ret[0] = ft_calloc(start_len[1] + 1, 1);
	ft_strlcpy(ret[0], data->line + i, start_len[1] + 1);
	ret[1] = ft_calloc(start_len[1] + i + 1, 1);
	ft_strlcpy(ret[1], data->line + start_len[0],
		i - start_len[0] + start_len[1] + 1);
}
