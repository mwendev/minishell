/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:12:23 by mwen              #+#    #+#             */
/*   Updated: 2021/12/11 20:34:02 by aignacz          ###   ########.fr       */
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
	char	*cmd_with_path;
	char	**envp;
	char	*line;
	char	**cmd;
	char	**argv;
	char	*prev_dir;
	char	path[PATH_MAX];
}	t_data;

void	change_directory(t_data *data);
char	**split_with_comma(char *line);

#endif