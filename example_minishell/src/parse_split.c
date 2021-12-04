/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 08:42:05 by ioleinik          #+#    #+#             */
/*   Updated: 2021/10/30 14:04:13 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_quot_count(const char *s, size_t *i)
{
	if (s[*i] == '\"' && ft_strchr(&s[*i + 1], '\"'))
	{
		(*i)++;
		while (s[*i] != '\"')
			(*i)++;
	}
	if (s[*i] == '\'' && ft_strchr(&s[*i + 1], '\''))
	{
		(*i)++;
		while (s[*i] != '\'')
			(*i)++;
	}
}

static void	handle_quot_siz(char **next_str, size_t *i, size_t *next_len)
{
	if ((*next_str)[*i] == '\"' && ft_strchr(&(*next_str)[*i + 1], '\"'))
	{
		(*next_len)++;
		(*i)++;
		while ((*next_str)[*i] != '\"')
		{
			(*i)++;
			(*next_len)++;
		}
	}
	if ((*next_str)[*i] == '\'' && ft_strchr(&(*next_str)[*i + 1], '\''))
	{
		(*next_len)++;
		(*i)++;
		while ((*next_str)[*i] != '\'')
		{
			(*i)++;
			(*next_len)++;
		}
	}
}

static size_t	ft_argcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		handle_quot_count(s, &i);
		if (s[i] == c)
		{
			count++;
			while (s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static void	get_nextarg(char **next_str, size_t *next_len, char c)
{
	size_t	i;

	*next_str += *next_len;
	*next_len = 0;
	i = 0;
	while ((*next_str)[i] == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		handle_quot_siz(&(*next_str), &i, next_len);
		if ((*next_str)[i] == c)
			return ;
		(*next_len)++;
		i++;
	}
}

char	**ft_splitarg(char const *s, char c)
{
	char	**str_arr;
	char	*next_str;
	size_t	next_len;
	size_t	i;

	str_arr = (char **)malloc(sizeof(char *) * (ft_argcount(s, c) + 1));
	if (NULL == str_arr)
		return (str_arr);
	i = 0;
	next_str = (char *)s;
	next_len = 0;
	while (i < ft_argcount(s, c))
	{
		get_nextarg(&next_str, &next_len, c);
		str_arr[i] = (char *)malloc(sizeof(char) * (next_len + 1));
		if (NULL == str_arr[i])
			return (NULL);
		ft_strlcpy(str_arr[i], next_str, next_len + 1);
		i++;
	}
	str_arr[i] = NULL;
	return (str_arr);
}
