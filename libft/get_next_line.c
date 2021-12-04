/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:51:21 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/15 23:49:08 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*concatanate_lines(char *line1, char *line2)
{
	char	*result;
	size_t	i;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen_gnl(line1);
	l2 = ft_strlen_gnl(line2);
	result = (char *) malloc((l1 + l2 + 1) * sizeof(char));
	i = 0;
	while (i < l1)
	{
		*(result + i) = *(line1 + i);
		i++;
	}
	i = 0;
	while (i < l2)
	{
		*(result + l1 + i) = *(line2 + i);
		i++;
	}
	*(result + l1 + l2) = '\0';
	free(line1);
	free(line2);
	return (result);
}

int	get_new_line(char *buffer, char **line)
{
	int			len;
	char		*line2;

	len = get_len_line(buffer);
	line2 = ft_strdup_gnl(buffer, len);
	if (*line == 0)
		*line = line2;
	else
		*line = concatanate_lines(*line, line2);
	return (len);
}

int	gnl_else(char *buffer, char **line, int len, ssize_t *ret)
{	
	int	exit;

	exit = 0;
	len = get_new_line(buffer, line);
	if (len != BUFFER_SIZE && *(buffer + len) != '\0')
	{
		ft_memmove_gnl(buffer, buffer + len + 1, BUFFER_SIZE - (len + 1));
		*ret = 1;
		exit = 1;
	}
	else
		*buffer = 0;
	return (exit);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE] = {0};
	ssize_t		ret;
	int			exit;
	int			len;

	exit = 0;
	ret = BUFFER_SIZE;
	*line = 0;
	while (!exit)
	{
		if (*buffer == 0)
		{
			ft_bzero_gnl(buffer, BUFFER_SIZE);
			ret = read(fd, buffer, BUFFER_SIZE);
			if (ret <= 0)
			{
				exit = 1;
				len = get_new_line(buffer, line);
			}
		}
		else
			exit = gnl_else(buffer, line, len, &ret);
	}
	return (ret);
}
