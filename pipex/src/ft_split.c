/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:55:58 by mwen              #+#    #+#             */
/*   Updated: 2021/10/12 18:04:17 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	get_output_len(const char *s, char c)
{
	int	i;
	int	is_string;

	i = 0;
	is_string = 0;
	while (*s)
	{
		if (*s != c && is_string == 0)
		{
			is_string = 1;
			i++;
		}
		else if (*s == c)
			is_string = 0;
		s++;
	}
	return (i);
}

static char	*make_string(const char *s, int start, int finish)
{
	char	*string;
	int		i;

	i = 0;
	string = (char *)malloc((finish - start + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (start < finish)
		string[i++] = s[start++];
	string[i] = '\0';
	return (string);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		start;
	char	**output;

	output = (char **)malloc((get_output_len(s, c) + 1) * sizeof(char *));
	if (!s || !output)
		return (NULL);
	i = 0;
	j = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			output[j++] = make_string(s, start, i);
			start = -1;
		}
		i++;
	}
	output[j] = 0;
	return (output);
}
