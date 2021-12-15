/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:09:54 by mwen              #+#    #+#             */
/*   Updated: 2021/12/15 17:33:40 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_command(char *cmd, t_data *data)
{
	int		start;
	int		end;

	start = 0;
	while (*(cmd + start) == '{' || *(cmd + start) == '(')
		start++;
	while (*(cmd + start) == '\'' || *(cmd + start) == '"')
		start++;
	end = ft_strlen(cmd) - 1;
	while (end > start && (*(cmd + end) == '}' || *(cmd + start) == ')'))
		end--;
	while (end > start && (*(cmd + end) == '\'' || *(cmd + end) == '"'))
		end--;
	cmd = ft_substr(cmd, start, end - start + 1);
	if (ft_strchr(cmd, '"') == NULL && ft_strchr(cmd, '\'') == NULL
		&& ft_strchr(cmd, ' '))
		data->argv = ft_split(cmd, ' ');
	else if (ft_strchr(cmd, ' '))
		data->argv = split_with_comma(cmd);
	else
	{
		data->argv = ft_calloc(2, sizeof(char *));
		data->argv[0] = ft_strdup(cmd);
	}
	free(cmd);
	if (ft_strncmp(data->argv[0], "cd", ft_strlen(data->argv[0])) == 0
		&& (ft_strncmp(data->argv[0], "cd", 2) == 0))
	{
		data->cmd_with_path = ft_strdup(data->argv[0]);
		return (1);
	}
	return (0);
}

char	**create_envp(char **environ, t_data *data)
{
	int		len;
	int		i;
	char	**dup;

	len = 0;
	while (environ[len])
		len++;
	data->envp_len = len;
	i = -1;
	dup = (char **)malloc(sizeof(char *) * (len + 1));
	if (dup)
	{
		while (environ[++i])
			dup[i] = ft_strdup(environ[i]);
		dup[i] = NULL;
	}
	else
		error(data, "malloc for envp failed", 1);
	return (dup);
}

char	*create_string(int count, char c, int len, t_data *data)
{
	char	*str;

	str = malloc(len + 1 * sizeof(char));
	if (str)
	{
		str[len] = 0;
		str = ft_memset(str, c, len);
		data->special_char_check[count] = str;
	}
	else
		error(data, "malloc for check special characters failed", 1);
	return (str);
}
