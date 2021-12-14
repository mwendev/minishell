/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:13:07 by mwen              #+#    #+#             */
/*   Updated: 2021/12/14 18:00:58 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_data *data, char **environ)
{
	printf("\n---------------------------------------------\n");
	printf("--------------- Minishell 0.0 ---------------\n");
	printf("---------------------------------------------\n\n");
	data->end = 0;
	data->line = NULL;
	data->cmd = NULL;
	data->envp = environ;
	getcwd(data->path, PATH_MAX);
	data->prev_dir = ft_strdup(data->path);
	data->not_valid = 0;
	data->pipe_nb = 0;
}

void	destroy(char *promt, t_data *data)
{
	// int	i;

	// if (*(data->cmd))
	// {
	// 	i = 0;
	// 	while (*(data->cmd + i))
	// 		i++;
	// 	while (i-- > 0)
	// 		free(*(data->cmd + i));
	// 	free(data->cmd);
	// }
	free(promt);
	if (data->cmd)
	{
		free_split(data->cmd);
		data->cmd = NULL;
	}
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	data->not_valid = 0;
}

char	*create_string(char c, int len, t_data *data)
{
	char	*str;

	str = malloc(len + 1 * sizeof(char));
	if (!str)
	{
		error(data, "malloc failed", 0);
		return (NULL);
	}
	str[len] = 0;
	str = ft_memset(str, c, len);
	return (str);
}

void	process_line(t_data *data)
{
	int		i;
	int		l;
	char	*temp;

	l = ft_strlen(data->line);
	if (data->line[0] == '|' || data->line[0] == '^' || data->line[0] == ')'
		|| data->line[0] == '&' || data->line[0] == '!' || data->line[0] == '/'
		|| data->line[0] == '%' || data->line[0] == ';' || data->line[0] == '#'
		|| !ft_strncmp(data->line, "}", l) || !ft_strncmp(data->line, "~", l)
		|| !ft_strncmp(data->line, ".", l) || !ft_strncmp(data->line, ":", l)
		|| !ft_strncmp(data->line, create_string(' ', l, data), l)
		|| !ft_strncmp(data->line, create_string('*', l, data), l))
	{
		data->not_valid = 1;
		return ;
	}
	data->cmd = ft_split(data->line, ';');
	i = 0;
	while (*(data->cmd + i))
	{
		temp = ft_strtrim(*(data->cmd + i), " ");
		free(*(data->cmd + i));
		*(data->cmd + i) = temp;
		i++;
	}
}

int	main(void)
{
	char		*promt;
	t_data		data;
	int			i;
	extern char	**environ;

	initialize(&data, environ);
	while (!data.end)
	{
		getcwd(data.path, PATH_MAX);
		promt = ft_strjoin(data.path, ":> ");
		data.line = readline(promt);
		if (data.line && *(data.line))
			add_history(data.line);
		process_line(&data);
		i = -1;
		while (data.cmd && *(data.cmd + (++i)) && !data.not_valid)
			execute_command(*(data.cmd + i), &data);
		destroy(promt, &data);
	}
	return (0);
}
