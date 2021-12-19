/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:13:07 by mwen              #+#    #+#             */
/*   Updated: 2021/12/19 18:15:32 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_data *data, char **environ)
{
	printf("\n---------------------------------------------\n");
	printf("--------------- Minishell 0.0 ---------------\n");
	printf("---------------------------------------------\n\n");
	data->line = NULL;
	data->cmd = NULL;
	data->cmd_with_path = NULL;
	data->envp = create_envp(environ, data);
	ft_bzero(data->path, PATH_MAX);
	data->prev_dir = ft_strdup(data->path);
	data->not_valid = 0;
	data->pipe_nb = 0;
}

void	destroy(t_data *data)
{
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

void	read_command_line(t_data *data)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(data->path, ":> ");
	data->line = readline(temp1);
	free(temp1);
	if (data->line && *(data->line))
		add_history(data->line);
	while (check_line(data))
	{
		temp1 = ft_strjoin(data->line, "\n");
		free(data->line);
		temp2 = readline(">");
		data->line = ft_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
	}
}

int	main(void)
{
	char		*temp;
	t_data		data;
	int			i;
	extern char	**environ;

	initialize(&data, environ);
	while (1)
	{
		getcwd(data.path, PATH_MAX);
		read_command_line(&data);
		data.cmd = split_with_comma(data.line, '|', &data);
		if (*(data.cmd) && *(data.cmd + 1))
			execute_pipe(&data);
		else if (*(data.cmd))
			execute_command(&data);
		destroy(&data);
	}
	free_split(data.envp);
	return (0);
}
