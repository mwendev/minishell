/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:42:44 by mwen              #+#    #+#             */
/*   Updated: 2021/10/14 15:48:22 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdarg.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

//outfile -> append
//infile -> stdin when "here_doc"

//first run a command that would convert stdin until LIMITER to another file
//dup2 it to STDIN
typedef struct s_pd
{
	int		argc;
	int		infile;
	int		outfile;
	int		fd[2];
	char	**cmd;
	char	**path;
	char	**envp;
}			t_pd;

void	check_args(int argc, char **argv);
char	*check_path_in_env(char **envp);
char	*check_path(char **path, char *cmd);
void	error_exit(char *msg, int i);
void	error(char *msg);
void	double_free(char **double_pointer);
void	free_data(t_pd pdata);
t_pd	init_pdata(int argc, char **argv, char **envp);

void	*ft_calloc(size_t nitems, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char	*big, const char *little, size_t len);

#endif