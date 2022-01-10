/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:20:13 by aignacz           #+#    #+#             */
/*   Updated: 2022/01/10 15:28:29 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_word_col(char **pointer_place)
{
	char	*pointer;
	char	c;
	int		start;
	int		len;

	pointer = *pointer_place;
	start = 0;
	len = 0;
	while (*(pointer + start + len) && *(pointer + start + len) != '|')
	{
		c = *(pointer + start + len++);
		if (c == '"' || c == '\'')
		{
			while (*(pointer + start + len) && *(pointer + start + len) != c)
				len++;
			if (*(pointer + start + len))
				len++;
		}
	}
	if (*(pointer + start + len) == '|')
		*pointer_place = pointer + start + len + 1;
	else
		*pointer_place = pointer + start + len;
	return (ft_substr(pointer, start, len));
}

char	*get_next_if_needed(char *pointer, char **pp, t_data *data)
{
	char	*temp1;
	char	*temp2;
	int		flag;

	if (**pp && **pp != ' ')
	{
		flag = 1;
		temp1 = get_next_word(pp, &flag, data);
		temp2 = ft_strjoin(pointer, temp1);
		free(temp1);
		free(pointer);
		pointer = temp2;
	}
	return (pointer);
}

char	*get_next_word(char **pointer_place, int *flag, t_data *data)
{
	char	*pointer;
	char	ch;
	int		start;
	int		len;

	pointer = *pointer_place;
	start = 0;
	ch = ' ';
	while (*(pointer + start) == ' ')
		start++;
	len = get_len_next_word(pointer, &start, &ch, flag);
	*pointer_place = pointer + start + len;
	pointer = create_expand(*flag, ft_substr(pointer, start, len), data);
	if (ch != ' ' && **pointer_place == ch)
		*pointer_place += 1;
	pointer = get_next_if_needed(pointer, pointer_place, data);
	return (pointer);
}

char	**split_input(char *line, char c, t_data *data)
{
	int		words;
	int		i;
	int		flag;
	char	**argv;
	char	*pointer;

	words = get_word_count_helper(line, c);
	if (c == '|' && words != 1)
		data->pipe_nb = words;
	argv = (char **) malloc((words + 1) * sizeof(char *));
	if (!argv)
		error(data, "Malloc failed for input data argv\n", 0, 'p');
	i = 0;
	pointer = line;
	while (i < words)
	{
		flag = 1;
		if (c == '|')
			*(argv + i) = get_next_word_col(&pointer);
		else
			*(argv + i) = get_next_word(&pointer, &flag, data);
		i++;
	}
	*(argv + i) = NULL;
	return (argv);
}
