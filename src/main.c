/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:13:07 by mwen              #+#    #+#             */
/*   Updated: 2021/12/15 20:30:12 by aignacz          ###   ########.fr       */
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
	data->envp = create_envp(environ, data);
	data->prev_dir = ft_strdup(data->path);
	data->special_char_check = ft_calloc(4, sizeof(char *));
	if (!data->special_char_check)
		error(data, "malloc for special character check failed", 1);
	data->not_valid = 0;
	data->pipe_nb = 0;
}

void	destroy(char *promt, t_data *data)
{
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
	if (data->special_char_check)
	{
		free_split(data->special_char_check);
		data->special_char_check = ft_calloc(4, sizeof(char *));
		if (!data->special_char_check)
			error(data, "malloc for special character check failed", 1);
	}
	data->not_valid = 0;
}

int	main(void)
{
	char		*promt;
	t_data		data;
	int			i;
	extern char	**environ;

	initialize(&data, environ);
	while (1)
	{
		getcwd(data.path, PATH_MAX);
		promt = ft_strjoin(data.path, ":> ");
		data.line = readline(promt);
		if (data.line && *(data.line))
			add_history(data.line);
		data.cmd = split_with_comma(data.line, '|');
		if (*(data.cmd + 1))
			execute_pipe(&data);
		else
			execute_command(&data);
		destroy(promt, &data);
	}
	free_split(data.envp);
	return (0);
}
