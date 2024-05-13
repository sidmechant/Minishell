/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:35:46 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/28 20:48:25 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	duplicate_solo_cmd(t_pars *pars, t_cmd *current)
{
	if (current->infile != STDIN_FILENO)
	{
		if (dup2(current->infile, STDIN_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close_in_child(pars);
	}
	if (current->outfile != STDOUT_FILENO)
	{
		if (dup2(current->outfile, STDOUT_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close_out_child(pars);
	}
}

void	duplicate_first(t_pars *pars, t_cmd *current)
{
	close(pars->pipefd[0]);
	if (dup2(current->infile, STDIN_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close_in_child(pars);
	if (current->outfile != STDOUT_FILENO)
	{
		if (dup2(current->outfile, STDOUT_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close_out_child(pars);
		close(pars->pipefd[1]);
	}
	else
	{
		if (dup2(pars->pipefd[1], STDOUT_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close(pars->pipefd[1]);
	}
}

void	duplicate_last(t_pars *pars, t_cmd *current)
{
	close(pars->pipefd[1]);
	if (dup2(current->outfile, STDOUT_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close_out_child(pars);
	if (current->infile != STDIN_FILENO)
	{
		if (dup2(current->infile, STDIN_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close_in_child(pars);
		close(pars->pipefd[0]);
	}
	else
	{
		if (dup2(pars->pipefd[0], STDIN_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close(pars->pipefd[0]);
	}
}

void	duplicate_normal_1(t_pars *pars, t_cmd *current)
{
	close(pars->savefd[1]);
	close(pars->pipefd[0]);
	if (current->infile != STDIN_FILENO)
	{
		if (dup2(current->infile, STDIN_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close_in_child(pars);
		close(pars->savefd[0]);
	}
	else
	{
		if (dup2(pars->savefd[0], STDIN_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close(pars->savefd[0]);
	}
	duplicate_normal_2(pars, current);
}

void	duplicate_normal_2(t_pars *pars, t_cmd *current)
{
	if (current->outfile != STDOUT_FILENO)
	{
		if (dup2(current->outfile, STDOUT_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close_out_child(pars);
		close(pars->pipefd[1]);
	}
	else
	{
		if (dup2(pars->pipefd[1], STDOUT_FILENO) < 0)
			all_clear(pars, EXIT_FAILURE);
		close(pars->pipefd[1]);
	}
}
