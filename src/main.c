/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:13:07 by mwen              #+#    #+#             */
/*   Updated: 2021/12/12 21:05:12 by mwen             ###   ########.fr       */
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

void	destroy(t_data *data)
{
	int	i;

	if (*(data->cmd))
	{
		i = 0;
		while (*(data->cmd + i))
			i++;
		while (i-- > 0)
			free(*(data->cmd + i));
		free(data->cmd);
	}
}

void	split_commands(t_data *data)
{
	int		i;
	char	*temp;

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
		free(promt);
		split_commands(&data);
		i = -1;
		while (*(data.cmd + (++i)) && !data.not_valid)
			execute_command(*(data.cmd + i), &data);
	}
	destroy(&data);
	return (0);
}
