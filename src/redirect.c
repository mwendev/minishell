/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:19:11 by mwen              #+#    #+#             */
/*   Updated: 2022/01/04 19:42:32 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_stdin(t_data *data, int fd)
{
	int		i;
	char	*line[2048];
	char	*eof;

	i = 0;
	eof = data->redir_append[0];
	fd = open("_tmp", O_RDWR | O_CREAT);
	if (fd != -1)
	{
		while (get_next_line(STDIN_FILENO, line) != 0
		&& ft_strncmp(*line, eof, ft_strlen(eof)) != 0)
		{
			if (write(fd, *line, ft_strlen(*line)) == -1
				|| write(fd, "\n", 1) == -1)
				return (error(data, "Write failed", 0, 'e'));
			free(*line);
			if (++i == 2048)
			{
				error(data, "Max 2048 lines\n", 0, 'p');
				return ;
			}
		}
		free(*line);
	}
	else
		error(data, "Open failed", 0, 'e');
}

void	redir_fd(t_data *data, int fd, int redir_type)
{
		if (redir_type == 1)
			write_stdin(data, fd);
		else if (redir_type == 2)
		{
			fd = open(data->redir_from[0], O_RDONLY | O_CLOEXEC, 0644);
			if (fd == -1)
				error(data, "Open failed", 1, 'e');
		}
		if (redir_type <= 2 && dup2(fd, STDIN_FILENO) < 0)
			return (error(data, "Dup failed", 1, 'e'));
		if (redir_type == 3)
			fd = open(data->redir_append[0], O_RDWR | O_CREAT | O_APPEND
				| O_CLOEXEC, 0777);
		else if (redir_type == 4)
			fd = open(data->redir_to[0], O_RDWR | O_CREAT | O_TRUNC
				| O_CLOEXEC, 0777);
		if (redir_type > 2 && fd == -1)
			error(data, "Open failed", 1, 'e');
		if (redir_type > 2 && dup2(fd, STDOUT_FILENO) < 0)
			return (error(data, "Dup failed", 1, 'e'));
}

void	trim_line(t_data *data, char *to_trim)
{
	char	*temp;
	int		i = -1;
	int		j = 0;
	int		k = 0;
	int		n = -1;
	int		flag = 0;

	temp = ft_calloc(ft_strlen(data->line), 1);
	while (data->line[++i])
	{
		k = i;
		while (data->line[i] == to_trim[j])
		{
			++i;
			++j;
			if (j == ft_strlen(to_trim))
			{
				flag = 1;
				break ;
			}
		}
		j = 0;
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
	int		start;
	int		len;
	char	**ret;

	i = -1;
	len = 0;
	ret = ft_calloc(3, sizeof(char *));
	if (!ret)
		error(data, "Malloc fail for redirection data", 1, 'p');
	while (data->line[++i] != c)
		continue ;
	start = i;
	while (data->line[i] == c || data->line[i] == ' ')
		++i;
	while (data->line[i + len] != ' ')
		len++;
	ret[0] = ft_calloc(len + 1, 1);
	ft_strlcpy(ret[0], data->line + i, len + 1);
	ret[1] = ft_calloc(len + 1, 1);
	ft_strlcpy(ret[1], data->line + start, i - start + len + 1);
	trim_line(data, ret[1]);
	printf("|%s| |%s| |%s|\n", ret[0], ret[1], data->line);
	return (ret);
}

/*by chance < to-do ls >> abc seg fault*/
void	redirect(t_data *data)
{
	if (ft_strnstr(data->line, "<<", ft_strlen(data->line)))
		data->redir_stdin = get_redir(data, '<');
	else if	(ft_strchr(data->line, '<'))
		data->redir_from = get_redir(data, '<');
	if (ft_strnstr(data->line, ">>", ft_strlen(data->line)))
		data->redir_append = get_redir(data, '>');
	else if (ft_strchr(data->line, '>'))
		data->redir_to = get_redir(data, '>');
}
