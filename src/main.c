/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:28:57 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/06 22:32:49 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_data *data)
{
	printf("\n---------------------------------------------\n");
	printf("--------------- Minishell 0.0 ---------------\n");
	printf("---------------------------------------------\n\n");
	data->end = 0;
	data->argv = NULL;
	data->argc = 0;
}

void	destroy(t_data *data)
{
	while ((data->argc)-- > 0)
		free(*(data->argv + data->argc));
	if (data->argv)
		free(data->argv);
}

int	execute_command(char *line, t_data *data)
{
	(void) data;
	free(line);
	return (1);
}

int	check_command(char *line, t_data *data)
{
	(void) data;
	data->argv = ft_split(line, ' ');
	data->argc = 0;
	while (*(data->argv + data->argc))
		data->argc++;
	printf("Number of arguments: %i\n", data->argc);
	printf("%s: command not found\n", line);
	free(line);
	return (1);
}

int	main(void)
{
	char	*line;
	char	*promt;
	char	path[PATH_MAX];
	t_data	data;

	initialize(&data);
	while (!data.end)
	{
		getcwd(path, PATH_MAX);
		promt = ft_strjoin(path, ":> ");
		line = readline(promt);
		free(promt);
		if (!check_command(line, &data))
			execute_command(line, &data);
	}
	destroy(&data);
	return (0);
}
