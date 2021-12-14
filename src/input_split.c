/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:20:13 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/14 16:42:34 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	count_char(char *str, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (*(str + i))
	{
		if (*(str + i) == c && (i == 0 || *(str + i - 1) != '\\'))
			res++;
		i++;
	}	
	return (res);
}

void	word_count(char *line, int *words)
{
	int	i;

	i = 0;
	*words = 0;
	while (*(line + i))
	{
		if (i == 0 || (*(line + i) == ' ' && *(line + i + 1) != '\0'))
		{
			*words += 1;
			while (*(line + i) == ' ')
				i++;
			if (*(line + i) == '"')
			{
				i++;
				while (*(line + i) && *(line + i) != '"')
					i++;
				if (*(line + i) != '"')
					i++;
			}
			if (i == 0)
				i++;
		}
		else
			i++;
	}
}

char	*get_next_word(char **pointer_place)
{
	char	*new_str;
	char	*pointer;
	char	ch;
	int		start;
	int		len;

	pointer = *pointer_place;
	while (*pointer == ' ')
		pointer++;
	if (*pointer == '"')
		ch = '"';
	else
		ch = ' ';
	start = 0;
	while (*(pointer + start) == ch)
		start++;
	len = 0;
	while (*(pointer + start + len) && *(pointer + start + len) != ch)
		len++;
	new_str = ft_substr(pointer, start, len);
	if (*(pointer + start + len) == ch)
		*pointer_place = pointer + start + len + 1;
	else
		*pointer_place = pointer + start + len;
	return (new_str);
}

char	**split_with_comma(char *line)
{
	int		words;
	int		i;
	char	**argv;
	char	*pointer;

	word_count(line, &words);
	argv = (char **) malloc((words + 1) * sizeof(char *));
	i = 0;
	pointer = line;
	while (i < words)
	{
		*(argv + i) = get_next_word(&pointer);
		i++;
	}
	*(argv + i) = NULL;
	return (argv);
}
