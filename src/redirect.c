/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:19:11 by mwen              #+#    #+#             */
/*   Updated: 2022/01/07 21:35:05 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_fd(t_data *data, int fd, int redir_type)
{
	if (redir_type == 1)
	{
		create_stdin(data, fd);
		close(fd);
		close(0);
		fd = open("_tmp", O_RDONLY, 0644);
	}
	else if (redir_type == 2)
	{
		close(0);
		fd = open(data->redir_from[0], O_RDONLY, 0644);
	}
	if (redir_type == 3)
	{
		close (1);
		fd = open(data->redir_append[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else if (redir_type == 4)
	{
		close (1);
		fd = open(data->redir_to[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	if (fd == -1)
		error(data, "Open failed", 0, 'e');
}

void	if_to_trim(t_data *data, int *i, int *flag, char *to_trim)
{
	int	j;

	j = 0;
	while (data->line[*i] == to_trim[j])
	{
		++*i;
		++j;
		if (j == ft_strlen(to_trim))
		{
			*flag = 1;
			break ;
		}
	}
}

void	trim_line(t_data *data, char *to_trim)
{
	char	*temp;
	int		i;
	int		k;
	int		flag;
	int		n;

	i = -1;
	k = 0;
	n = -1;
	flag = 0;
	temp = ft_calloc(ft_strlen(data->line), 1);
	if (!temp)
		error(data, "Malloc failed for new line", 0, 'p');
	while (data->line[++i])
	{
		k = i;
		if_to_trim(data, &i, &flag, to_trim);
		if (!flag)
			i = k;
		else
			flag = 0;
		temp[++n] = data->line[i];
	}
	free(data->line);
	data->line = temp;
}

char	**get_redir(t_data *data, char c)
{
	int		i;
	int		start_len[2];
	char	**ret;

	i = -1;
	start_len[1] = 0;
	if (!data->line)
		return (NULL);
	ret = ft_calloc(3, sizeof(char *));
	if (!ret)
		error(data, "Malloc failed for redirection data", 0, 'p');
	while (data->line[++i] != c)
		continue ;
	start_len[0] = i;
	while (data->line[i] == c || data->line[i] == ' ')
		++i;
	while (data->line[i + start_len[1]] && data->line[i + start_len[1]] != ' ')
	{
		start_len[1]++;
		if (data->line[i + start_len[1]] == '>'
			|| data->line[i + start_len[1]] == '<')
			break ;
	}
	if (!start_len[1])
		return (NULL);
	create_redir_string(data, ret, i, start_len);
	trim_line(data, ret[1]);
	return (ret);
}

void	redirect(t_data *data)
{
	if (!ft_strncmp(data->line, "<<", ft_strlen(data->line))
		|| !ft_strncmp(data->line, "<", ft_strlen(data->line))
		|| !ft_strncmp(data->line, ">>", ft_strlen(data->line))
		|| !ft_strncmp(data->line, ">", ft_strlen(data->line)))
	{
		error(data, "bash: syntax error near unexpected token `newline'\n",
			0, 'p');
		return ;
	}
	if (ft_strnstr(data->line, "<<", ft_strlen(data->line)))
	{
		data->redir_stdin = get_redir(data, '<');
		redir_fd(data, data->redir_stdin_fd, 1);
	}
	else if (ft_strchr(data->line, '<'))
	{
		data->redir_from = get_redir(data, '<');
		redir_fd(data, data->redir_from_fd, 2);
	}
	if (ft_strnstr(data->line, ">>", ft_strlen(data->line)))
	{
		data->redir_append = get_redir(data, '>');
		redir_fd(data, data->redir_append_fd, 3);
	}
	else if (ft_strchr(data->line, '>'))
	{
		data->redir_to = get_redir(data, '>');
		redir_fd(data, data->redir_to_fd, 4);
	}
}
