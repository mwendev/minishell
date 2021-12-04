/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:21:16 by mwen              #+#    #+#             */
/*   Updated: 2021/10/14 15:47:54 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	**init_cmd(int argc, char **argv, int *cmd_num)
{
	char	**cmd;
	int		num;
	int		i;

	i = 1;
	num = -1;
	cmd = ft_calloc(argc - 2, sizeof(char *));
	while (++i != argc - 1 && ++num >= 0)
		cmd[num] = ft_strdup(argv[i]);
	*cmd_num = num + 1;
	return (cmd);
}

char	**init_path(char **cmd, char **envp, int cmd_num)
{
	char	*paths;
	char	**path;
	char	**confirmed_path;
	int		i;

	i = -1;
	paths = check_path_in_env(envp);
	if (!paths)
		return (NULL);
	path = ft_split(paths, ':');
	confirmed_path = ft_calloc(cmd_num + 1, sizeof(char *));
	while (++i < cmd_num)
	{
		confirmed_path[i] = check_path(path, cmd[i]);
		if (!confirmed_path[i])
		{
			double_free(confirmed_path);
			double_free(path);
			error("Error: No path found for command");
			return (NULL);
		}
	}
	double_free(path);
	return (confirmed_path);
}

t_pd	init_pdata(int argc, char **argv, char **envp)
{
	t_pd	pdata;
	int		cmd_num;

	cmd_num = 0;
	pdata.argc = argc;
	if (ft_strnstr(argv[1], "here_doc", ft_strlen(argv[1])))
		pdata.infile = 0;
	else
		pdata.infile = open(argv[1], O_RDONLY);
	pdata.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pdata.infile < 0 || pdata.outfile < 0)
	{
		perror("Error");
		exit(1);
	}
	pdata.cmd = init_cmd(argc, argv, &cmd_num);
	pdata.path = init_path(pdata.cmd, envp, cmd_num);
	if (!pdata.path)
	{
		double_free(pdata.cmd);
		exit(1);
	}
	pdata.envp = envp;
	return (pdata);
}
