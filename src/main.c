/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:28:57 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/04 17:43:50 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_data *data)
{
	printf("Minishell 0.0\n");
	data->end = 0;
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
	printf("%s: command not found\n", line);
	free(line);
	return (1);
}

int	main(void)
{
	char	*line;
	t_data	data;

	while (!data.end)
	{
		printf(">>>");
		line = readline(NULL);
		if (!check_command(line, &data))
			execute_command(line, &data);
	}
	return (0);
}
