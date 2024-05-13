/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:40:08 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/28 20:10:20 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_failed_1(t_pars *pars, t_cmd *cmd, char **strs, int error)
{
	(void)error;
	ft_putstr_fd(cmd->agr[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_exitcode = 127;
	strs = free_strs(strs);
	all_clear(pars, NO_EXIT);
}

void	exec_failed_2(t_pars *pars, t_cmd *cmd, char **strs, int error)
{
	struct stat	path_stat;

	ft_bzero(&path_stat, sizeof(struct stat));
	stat(cmd->agr[0], &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(cmd->agr[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_exitcode = 126;
	}
	else if (error == 2)
	{
		ft_putstr_fd(cmd->agr[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exitcode = 127;
	}
	else if (error == 13)
	{
		ft_putstr_fd(cmd->agr[0], STDERR_FILENO);
		ft_putstr_fd(": Permission Denied\n", STDERR_FILENO);
		g_exitcode = 126;
	}
	strs = free_strs(strs);
	all_clear(pars, NO_EXIT);
}

char	*find_path(char **paths, t_cmd *current)
{
	int		i;
	char	*tmp;
	char	*rtrn;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		rtrn = ft_strjoin(tmp, current->agr[0]);
		if (!rtrn)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		if (access(rtrn, X_OK) == 0)
			return (rtrn);
		free(rtrn);
		i++;
	}
	return (ft_strdup(current->agr[0]));
}

char	*command_with_path(t_pars *pars, t_cmd *current)
{
	char	**paths;
	char	*rtrn;
	t_env	*tmp;

	if (!pars->env)
		return (ft_strdup(current->agr[0]));
	if (current == NULL)
		return (ft_strdup(""));
	tmp = pars->env;
	while (tmp && ft_strncmp("PATH=", tmp->str, 5))
		tmp = tmp->next;
	if (!tmp)
		return (ft_strdup(current->agr[0]));
	paths = ft_split_paths(tmp->str + 5, ':');
	if (!paths)
		return (NULL);
	rtrn = find_path(paths, current);
	if (!rtrn)
	{
		paths = free_strs(paths);
		return (NULL);
	}
	paths = free_strs(paths);
	return (rtrn);
}
