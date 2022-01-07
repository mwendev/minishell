/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:09:54 by mwen              #+#    #+#             */
/*   Updated: 2022/01/07 19:34:29 by aignacz          ###   ########.fr       */
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

char	*create_expand_helper(char *src, size_t len, t_data *data)
{
	char	*temp;
	char	*ret;

	temp = ft_substr(src, 1, len - 1);
	ret = check_in_env(data->envp, temp, data);
	free(temp);
	if (ret)
	{
		ret = ft_strdup(ret);
		temp = ft_substr(src, len, ft_strlen(src) - len);
		free(src);
		src = ft_strjoin(ret, temp);
		free(ret);
		free(temp);
	}
	return (src);
}

char	*create_expand(int flag, char *src, t_data *data)
{
	char	*ret;
	size_t	len;

	if (flag && src[0] == '$' && ft_strncmp(src, "$?", ft_strlen(src)))
	{
		len = 1;
		while (*(src + len) && (ft_isalnum((int) *(src + len))
				|| *(src + len) == '_'))
			len++;
		if (len < ft_strlen(src))
			return (create_expand_helper(src, len, data));
		else
		{
			ret = check_in_env(data->envp, src + 1, data);
			if (ret)
			{
				free(src);
				return (ft_strdup(ret));
			}
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

void	create_stdin(t_data *data, int fd)
{
	int		i;
	char	*line[2048];
	char	*eof;

	i = 0;
	eof = data->redir_stdin[0];
	fd = open("_tmp", O_RDWR | O_CREAT, 0644);
	if (fd != -1)
	{
		while (get_next_line(STDIN_FILENO, line)
			&& ft_strncmp(*line, eof, ft_strlen(eof)))
		{
			if (write(fd, *line, ft_strlen(*line)) == -1
				|| write(fd, "\n", 1) == -1)
				return (error(data, "Write failed", 1, 'e'));
			free(*line);
			if (++i == 2048)
				return (error(data, "Max 2048 lines\n", 0, 'p'));
		}
		free(*line);
	}
	else
		error(data, "Open failed", 1, 'e');
}
