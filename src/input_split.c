/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:20:13 by aignacz           #+#    #+#             */
/*   Updated: 2021/12/11 20:37:42 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**split_with_comma(char *line)
{
	int	i;
	int	

	i = 0;

	while ()
	{
		
	}
}
