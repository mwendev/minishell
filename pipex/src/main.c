/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 11:06:32 by mwen              #+#    #+#             */
/*   Updated: 2021/10/13 21:22:24 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
	double_free(argv);
}

void	prepare_fd(t_pd pdata, int count)
{
	if (count == 0)
	{
		if (dup2(pdata.infile, STDIN_FILENO) < 0
			|| dup2(pdata.fd[1], STDOUT_FILENO) < 0)
		{
			perror("Error");
			free_data(pdata);
			exit(3);
		}
		close(pdata.fd[0]);
		close(pdata.infile);
	}
	else
	{
		if (dup2(pdata.fd[0], STDIN_FILENO) < 0
			|| dup2(pdata.outfile, STDOUT_FILENO) < 0)
		{
			perror("Error");
			free_data(pdata);
			exit(3);
		}
		close(pdata.fd[1]);
		close(pdata.outfile);
	}
	exe_cmd(pdata, count);
}

void	pipex(t_pd pdata)
{
	int		status;
	pid_t	cmd1;
	pid_t	cmd2;	

	status = 0;
	if (pipe(pdata.fd) == -1)
		error_exit("Error: Can't create pipe", 2);
	cmd1 = fork();
	if (cmd1 < 0)
		return (perror("Fork Error"));
	if (cmd1 == 0)
		prepare_fd(pdata, 0);
	waitpid(-1, &status, 0);
	cmd2 = fork();
	if (cmd2 < 0)
		return (perror("Fork Error"));
	if (cmd2 == 0)
		prepare_fd(pdata, 1);
	close(pdata.fd[0]);
	close(pdata.fd[1]);
	waitpid(-1, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pd	pdata;

	check_args(argc, argv);
	pdata = init_pdata(argc, argv, envp);
	pipex(pdata);
	free_data(pdata);
}
