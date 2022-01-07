/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:20:13 by aignacz           #+#    #+#             */
/*   Updated: 2022/01/07 18:49:09 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_count_col(char *line, char c)
{
	int	i;
	int	inquote;
	int	words;

	i = 0;
	words = 0;
	inquote = 0;
	while (*(line + i) == ' ')
		i++;
	while (*(line + i))
	{
		if (!inquote && *(line + i) == c)
		{
			words++;
			while (*(line + i + 1) == c)
				i++;
		}
		else if (inquote < 2 && *(line + i) == '"')
			inquote = (inquote + 1) % 2;
		else if (inquote % 2 == 0 && *(line + i) == '\'')
			inquote = (inquote + 2) % 4;
		i++;
		if (ft_strchr(line + i, c) == NULL)
			return (words + 1);
	}
	return (words);
}

int	word_count(char *line, char c)
{
	int	i;
	int	inquote;
	int	words;

	i = 0;
	words = 0;
	inquote = 0;
	while (*(line + i) == ' ')
		i++;
	while (*(line + i))
	{
		if (!inquote && *(line + i) == c)
		{
			words++;
			while (c == ' ' && !inquote && *(line + i + 1) == c)
				i++;
		}
		else if (*(line + i) == '"')
			inquote = (inquote + 1) % 2;
		i++;
		if (*(line + i) && ft_strchr(line + i, c) == NULL)
			return (words + 1);
	}
	return (words);
}

char	*get_next_word_col(char **pointer_place)
{
	char	*new_str;
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
	new_str = ft_substr(pointer, start, len);
	if (*(pointer + start + len) == '|')
		*pointer_place = pointer + start + len + 1;
	else
		*pointer_place = pointer + start + len;
	return (new_str);
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
	int		inquote;

	pointer = *pointer_place;
	start = 0;
	len = 0;
	ch = ' ';
	inquote = 0;
	while (*(pointer + start) == ' ')
		start++;
	if (*(pointer + start) == '"' || *(pointer + start) == '\'')
	{
		if (*(pointer + start) == '\'' && *(pointer + start + 1) == '$')
			*flag = 0;
		ch = *(pointer + start);
		inquote = 1;
		start++;
	}
	if (*(pointer + start) == '$')
		len++;
	while (*(pointer + start + len) && (*(pointer + start + len) != ch
			&& (inquote || (*(pointer + start + len) != '"'
					&& *(pointer + start + len) != '\''
					&& *(pointer + start + len) != '$'))))
		len++;
	*pointer_place = pointer + start + len;
	pointer = ft_substr(pointer, start, len);
	pointer = create_expand(*flag, pointer, data);
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

	if (c == '|')
		words = word_count_col(line, c);
	else
		words = word_count(line, c);
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
		{
			*(argv + i) = get_next_word(&pointer, &flag, data);
			*(argv + i) = create_expand(flag, *(argv + i), data);
		}
		i++;
	}
	*(argv + i) = NULL;
	return (argv);
}
