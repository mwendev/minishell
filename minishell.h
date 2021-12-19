/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:12:23 by mwen              #+#    #+#             */
/*   Updated: 2021/12/19 22:09:31 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# ifdef __linux__
#  include <limits.h>
# else
#  include <sys/syslimits.h>
# endif

typedef struct s_data
{
	int		not_valid;
	int		pipe_nb;
	int		*pipe_fd;
	int		envp_len;
	char	*cmd_with_path;
	char	**argv;
	char	**envp;
	char	*line;
	char	**cmd;
	char	*prev_dir;
	char	path[PATH_MAX];
}	t_data;

void	change_directory(t_data *data);
int		check_path(char *cmd, t_data *data);
int		check_pipe_nb(char *cmd, t_data *data);
int		check_line(t_data *data);
int		create_command(char *cmd, t_data *data);
char	*create_string(int count, char c, int len, t_data *data);
char	**create_envp(char **environ, t_data *data);
char	**split_with_comma(char *line, char c, t_data *data);
void	execute_command(char *cmd, t_data *data, int cmd_nb, int end);
void	execute_pipe(t_data *data);
void	error(t_data *data, char *str, int end);
int		free_split(char **str);
void	free_pipe(char **pipe_cmd, t_data *data);
void	close_pipe(int piped, t_data *data);
void	signal_init(void);

#endif