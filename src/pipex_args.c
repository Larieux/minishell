/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 10:58:18 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errors(int argc, t_minist *s_minis, char **envp)
{
	if (argc < 4)
		return (write(2, "too few arguments\n", 19), -1);
	if (ft_strlen(s_minis->args[1]) == 8
		&& ft_strncmp(s_minis->args[1], "here_doc", 8) == 0)
	{
		if (argc < 5)
			return (write(2, "too few arguments\n", 19), -1);
		s_minis->here_doc = 1;
		s_minis->first_cmd = 3;
		s_minis->eof_len = ft_strlen(s_minis->args[2]);
		init_heredoc(s_minis);
	}
	else
	{
		s_minis->here_doc = 0;
		s_minis->first_cmd = 2;
		s_minis->infile = ft_strdup(s_minis->args[1]);
	}
	s_minis->outfile = ft_strdup(s_minis->args[s_minis->arg_c_or - 1]);
	if (envp == NULL)
		s_minis->env = NULL;
	else
		s_minis->env = envp;
	return (0);
}

char	**find_paths(t_minist *s_minis)
{
	char	*path;
	char	**paths;
	size_t	i;

	i = 0;
	path = NULL;
	while (s_minis->env[i])
	{
		if (ft_strncmp(s_minis->env[i], "PATH=", 5) == 0)
			path = s_minis->env[i];
		i++;
	}
	if (path == NULL)
		return (NULL);
	path = ft_substr(path, 5, strlen(path) - 5);
	if (path == NULL)
		return (write(2, "malloc error\n", 14), NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (free (path), write(2, "malloc error\n", 14), NULL);
	return (free (path), paths);
}

void	exec_vanilla_cmd(t_minist *s_minis, char **cmd)
{
	char	**van_cmd;
	char	*van_cmd_args[2];
	int		i;

	van_cmd = ft_split(cmd[0], '/');
	i = 0;
	while (van_cmd[i + 1] != NULL)
		i++;
	van_cmd_args[0] = ft_strjoin(van_cmd[i], " ");
	free_dtab (van_cmd);
	i = 1;
	while (cmd[i] != NULL)
	{
		van_cmd_args[1] = ft_strjoin(van_cmd_args[0], cmd[i]);
		free (van_cmd_args[0]);
		van_cmd_args[0] = ft_strjoin(van_cmd_args[1], " ");
		free (van_cmd_args[1]);
		i++;
	}
	van_cmd = ft_split(van_cmd_args[0], ' ');
	free (van_cmd_args[0]);
	execve(cmd[0], van_cmd, s_minis->env);
	free_dtab (van_cmd);
}

void	find_cmd(t_minist *s_minis, char **cmd)
{
	int		i;
	int		test_exec;
	char	**paths;
	char	*slash_cmd;
	char	*path_cmd;

	paths = find_paths(s_minis);
	slash_cmd = ft_strjoin("/", cmd[0]);
	if (slash_cmd == NULL || !slash_cmd)
		exit_dfree_malloc(paths);
	test_exec = -1;
	i = 0;
	while (test_exec == -1 && paths != NULL && paths[i] != NULL)
	{
		path_cmd = ft_strjoin(paths[i], slash_cmd);
		free(paths[i]);
		test_exec = execve(path_cmd, cmd, s_minis->env);
		free(path_cmd);
		i++;
	}
	exec_vanilla_cmd(s_minis, cmd);
	execve_error(s_minis, cmd, paths, slash_cmd);
}
