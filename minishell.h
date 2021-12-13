/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:12:23 by mwen              #+#    #+#             */
/*   Updated: 2021/12/13 22:42:52 by mwen             ###   ########.fr       */
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
# include <sys/syslimits.h>

typedef struct s_data
{
	int		end;
	int		not_valid;
	int		pipe_nb;
	int		*pipe_fd;
	char	*cmd_with_path;
	char	**envp;
	char	*line;
	char	**cmd;
	char	**argv;
	char	*prev_dir;
	char	path[PATH_MAX];
}	t_data;

void	change_directory(t_data *data);
int	check_command(char *cmd, t_data *data);
int	check_pipe_nb(char *cmd, t_data *data);
char	**split_with_comma(char *line);
void	execute_command(char *cmd, t_data *data);
void	error(t_data *data, char *str, int end);
int	free_split(char **str);
void	free_pipe(char **pipe_cmd, t_data *data);
void	close_pipe(int piped, t_data *data);


#endif