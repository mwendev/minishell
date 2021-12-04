/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 11:06:32 by mwen              #+#    #+#             */
/*   Updated: 2021/10/14 15:47:19 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exe_cmd(t_pd pdata, int count)
{
	char	**argv;
	char	*path;

	path = pdata.path[count];
	if (ft_strchr(pdata.cmd[count], ' '))
		argv = ft_split(pdata.cmd[count], ' ');
	else
	{
		argv = ft_calloc(2, sizeof(char *));
		argv[0] = ft_strdup(pdata.cmd[count]);
	}
	if (execve(path, argv, pdata.envp) < 0)
	{
		perror("Error");
		free_data(pdata);
		exit(2);
	}
}

void	pipex(t_pd pdata, int count)
{
	int		status;
	pid_t	cmd;

	status = 0;
	if (pipe(pdata.fd) == -1)
		error_exit("Error: Can't create pipe", 2);
	cmd = fork();
	if (cmd < 0)
		return (perror("Fork Error"));
	if (cmd == 0)
	{
		close(pdata.fd[0]);
		dup2(pdata.fd[1], STDOUT_FILENO);
		exe_cmd(pdata, count);
	}
	close(pdata.fd[1]);
	dup2(pdata.fd[0], STDIN_FILENO);
	waitpid(-1, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pd	pdata;
	int		count;
	int		fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	count = -1;
	check_args(argc, argv);
	pdata = init_pdata(argc, argv, envp);
	dup2(pdata.infile, STDIN_FILENO);
	dup2(pdata.outfile, STDOUT_FILENO);
	while (++count >= 0 && pdata.cmd[count + 1])
		pipex(pdata, count);
	exe_cmd(pdata, count);
	free_data(pdata);
}
