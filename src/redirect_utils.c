/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:19:19 by mwen              #+#    #+#             */
/*   Updated: 2022/01/07 22:35:33 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_to_trim(t_data *data, int *i, int *flag, char *to_trim)
{
	int	j;

	j = 0;
	while (data->line[*i] == to_trim[j])
	{
		++*i;
		++j;
		if (j == ft_strlen(to_trim))
		{
			*flag = 1;
			break ;
		}
	}
}

void	trim_line(t_data *data, char *to_trim)
{
	char	*temp;
	int		i;
	int		k;
	int		flag;
	int		n;

	i = -1;
	k = 0;
	n = -1;
	flag = 0;
	temp = ft_calloc(ft_strlen(data->line), 1);
	if (!temp)
		error(data, "Malloc failed for new line", 0, 'p');
	while (data->line[++i])
	{
		k = i;
		if_to_trim(data, &i, &flag, to_trim);
		if (!flag)
			i = k;
		else
			flag = 0;
		temp[++n] = data->line[i];
	}
	free(data->line);
	data->line = temp;
}

char	**get_redir(t_data *data, char c)
{
	int		i;
	int		start_len[2];
	char	**ret;

	i = -1;
	start_len[1] = 0;
	while (data->line[++i] != c)
		continue ;
	start_len[0] = i;
	while (data->line[i] == c || data->line[i] == ' ')
		++i;
	while (data->line[i + start_len[1]] && data->line[i + start_len[1]] != ' ')
	{
		start_len[1]++;
		if (data->line[i + start_len[1]] == '>'
			|| data->line[i + start_len[1]] == '<')
			break ;
	}
	ret = create_redir_string(data, ret, i, start_len);
	if (ret)
		trim_line(data, ret[1]);
	return (ret);
}
