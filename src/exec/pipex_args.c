/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:38 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 09:35:37 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_paths(char **env)
{
	char	*path;
	char	**paths;
	int		i;
	int		len;

	i = 0;
	len = env_var_len(env[i]);
	while (env && env[i]
		&& (len != 4 || ft_strncmp(env[i], "PATH", len) != 0))
	{
		i++;
		len = env_var_len(env[i]);
	}
	len = ft_strlen(env[i]);
	path = ft_substr(env[i], 5, len - 5);
	if (path == NULL)
		return (set_error(get_minist()->err, ERR_ALLOC, "exec_van_cmd_1")
			, NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (free (path)
			, set_error(get_minist()->err, ERR_ALLOC, "exec_van_cmd_2"), NULL);
	return (free (path), paths);
}

char	*exec_cmd(t_minist *minis, char **paths, char **cmd)
{
	char	*path_cmd;
	char	*slash_cmd;
	int		test_exec;
	int		i;

	test_exec = -1;
	i = 0;
	slash_cmd = ft_strjoin("/", cmd[0]);
	if (!(slash_cmd))
		return (set_error(minis->err, ERR_ALLOC, "find_cmd_1"), NULL);
	while (test_exec == -1 && paths && paths[i] && cmd)
	{
		path_cmd = ft_strjoin(paths[i], slash_cmd);
		if (!(path_cmd))
			return (free(slash_cmd)
				, set_error(minis->err, ERR_ALLOC, "find_cmd_2"), NULL);
		free(paths[i++]);
		test_exec = execve(path_cmd, cmd, minis->env);
		free(path_cmd);
	}
	return (slash_cmd);
}

void	find_cmd(t_minist *minis, char **cmd)
{
	char	**paths;
	char	*slash_cmd;
	int		i;

	i = 0;
	minis->state = EXECUTION;
	signal(SIGINT, SIG_DFL);
	while (cmd && cmd[0] && cmd[0][i])
	{
		if (cmd[0][i++] == '/')
			execve(cmd[0], cmd, minis->env);
	}
	paths = find_paths(minis->env);
	if (!paths)
		return ;
	slash_cmd = exec_cmd(minis, paths, cmd);
	if (!slash_cmd)
		return (free_dtab(paths), (void)0);
	exec_vanilla_cmd(minis, minis->env, cmd);
	mini_execve_error(cmd, paths, slash_cmd);
}
