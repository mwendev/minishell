/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:12:23 by mwen              #+#    #+#             */
/*   Updated: 2022/01/05 23:40:12 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

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
	int		echo_quote;
	int		exit_status;
	int		redir_from_fd;
	int		redir_stdin_fd;
	int		redir_to_fd;
	int		redir_append_fd;
	char	**redir_from;
	char	**redir_stdin;
	char	**redir_to;
	char	**redir_append;
	char	*cmd_with_path;
	char	**argv;
	char	**envp;
	char	*line;
	char	**cmd;
	char	path[PATH_MAX];
	char	prev_dir[PATH_MAX];

	char	**temp;
}	t_data;

/* main.c */
char	**split_input(char *line, char c, t_data *data);
void	destroy(t_data *data);

/* create.c */
char	**create_envp(char **envp, t_data *data, char *target);
char	*create_expand(int	flag, char *src, t_data *data);

/* signal.c */
void	signal_init(void);

/* check.c */
int		check_path(t_data *data);
int		check_line(t_data *data);
int		check_envplen(char **envp);
char	*check_in_env(char **envp, char *to_check, t_data *data);

/* execute.c */
void	execute_command(char *cmd, t_data *data, int cmd_nb, int end);
void	execute_pipe(t_data *data);

/* builtin.c */
void	change_env(t_data *data, int cmd);
void	change_directory(t_data *data);
void	print_echo(t_data *data);
void	print_env(t_data *data);

/* builtin_utils.c */
char	*has_target(char **envp, char *target);
char	*trim_target(char *target);
char	*get_dir_name(t_data *data);

/* redirect.c */
void	redirect(t_data *data);
void	redir_fd(t_data *data, int fd, int redir_type);

/* error.c */
void	error(t_data *data, char *str, int end, char type);
int		free_split(char **str);
void	free_pipe(char **pipe_cmd, t_data *data);
void	close_pipe(int piped, t_data *data);
void	destroy_redir(t_data *data);

#endif