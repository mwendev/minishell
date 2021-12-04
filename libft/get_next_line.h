/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:51:11 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/15 23:47:46 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 30

# include <stddef.h>

int		get_next_line(int fd, char **line);
int		get_len_line(const char *s);
char	*ft_strdup_gnl(const char *s, int len);
void	*ft_memmove_gnl(void *dest, const void *src, size_t n);
size_t	ft_strlen_gnl(char *s);
void	ft_bzero_gnl(void *s, size_t n);

#endif
