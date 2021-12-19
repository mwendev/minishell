/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:20:13 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/19 20:08:25 by aignacz          ###   ########.fr       */
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

char	*get_next_word(char **pointer_place)
{
	char	*pointer;
	char	ch;
	int		start;
	int		len;

	pointer = *pointer_place;
	start = 0;
	len = 0;
	ch = ' ';
	while (*(pointer + start) == ' ')
		start++;
	if (*(pointer + start) == '"' || *(pointer + start) == '\'')
	{
		ch = *(pointer + start);
		start++;
	}
	while (*(pointer + start + len) && *(pointer + start + len) != ch)
		len++;
	*pointer_place = pointer + start + len;
	if (**pointer_place)
		*pointer_place += 1;
	while (**pointer_place && **pointer_place == ' ')
		*pointer_place += 1;
	return (ft_substr(pointer, start, len));
}

char	**split_with_comma(char *line, char c, t_data *data)
{
	int		words;
	int		i;
	char	**argv;
	char	*pointer;

	if (c == '|')
		words = word_count_col(line, c);
	else
		words = word_count(line, c);
	if (c == '|')
		data->pipe_nb = words;
	argv = (char **) malloc((words + 1) * sizeof(char *));
	i = 0;
	pointer = line;
	while (i < words)
	{
		if (c == '|')
			*(argv + i) = get_next_word_col(&pointer);
		else
			*(argv + i) = get_next_word(&pointer);
		i++;
	}
	*(argv + i) = NULL;
	return (argv);
}
