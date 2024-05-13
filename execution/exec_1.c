/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:14:08 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/28 19:57:05 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_command_line(t_pars *pars, char *s)
{
	int		cmd_nbr;
	t_cmd	*current;

	current = pars->command;
	cmd_nbr = count_command(pars);
	if (cmd_nbr == 1 && is_builtin(current->agr[0]))
		solo_builtin(pars, current);
	else if (cmd_nbr >= 1)
	{
		while (current)
		{
			create_pipe(pars, current, cmd_nbr);
			current->cmd_pid = fork();
			if (current->cmd_pid < 0)
				all_clear(pars, EXIT_FAILURE);
			if (current->cmd_pid == 0)
				exec_child(pars, current, cmd_nbr, s);
			pipe_manipulation(pars, current, cmd_nbr);
			current = current->next;
		}
		wait_processes(pars);
	}
}

void	wait_processes(t_pars *pars)
{
	static int	flag = 0;
	t_cmd		*current;

	current = pars->command;
	while (current)
	{
		waitpid(current->cmd_pid, &current->status, 0);
		if (WIFEXITED(current->status))
			g_exitcode = WEXITSTATUS(current->status);
		if (WIFSIGNALED(current->status))
			child_signal_return(WTERMSIG(current->status), current, &flag);
		current = current->next;
	}
	flag = 0;
}

void	pipe_manipulation(t_pars *pars, t_cmd *current, int cmd_nbr)
{
	t_cmd	*last;

	last = last_command(pars);
	if (current == pars->command && cmd_nbr > 1)
	{
		pars->savefd[0] = pars->pipefd[0];
		pars->savefd[1] = pars->pipefd[1];
	}
	else if (current == last && cmd_nbr > 1)
	{
		close(pars->pipefd[0]);
		close(pars->pipefd[1]);
	}
	else if (cmd_nbr > 1)
	{
		close(pars->savefd[0]);
		close(pars->savefd[1]);
		pars->savefd[0] = pars->pipefd[0];
		pars->savefd[1] = pars->pipefd[1];
	}
	if (current->infile > 2)
		close(current->infile);
	if (current->outfile > 2)
		close(current->outfile);
}

void	exec_child(t_pars *pars, t_cmd *current, int cmd_nbr, char *s)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	free(s);
	if (current->infile < 0 || current->outfile < 0)
		file_error(pars, current, cmd_nbr);
	if (cmd_nbr == 1)
		duplicate_solo_cmd(pars, current);
	else if (current == pars->command)
		duplicate_first(pars, current);
	else if (current->next == NULL)
		duplicate_last(pars, current);
	else
		duplicate_normal_1(pars, current);
	if (is_builtin(current->agr[0]))
	{
		signal(SIGPIPE, SIG_IGN);
		exec_builtin(pars, current);
		all_clear(pars, NO_EXIT);
		exit(g_exitcode);
	}
	exec_command(pars, current);
}

void	exec_command(t_pars *pars, t_cmd *current)
{
	char	*path;
	char	**copy_env;

	if (find_slash(current->agr[0]))
		exec_slash_command(pars, current);
	path = command_with_path(pars, current);
	if (!path)
		all_clear(pars, EXIT_FAILURE);
	copy_env = transform_env(pars->env);
	if (!copy_env)
		all_clear(pars, EXIT_FAILURE);
	g_exitcode = 0;
	execve(path, current->agr, copy_env);
	exec_failed_1(pars, current, copy_env, errno);
	free(path);
	exit(g_exitcode);
}
