/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:20:32 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/29 03:45:55 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_pars *pars, t_cmd *current)
{
	if (!ft_strncmp("cd", current->agr[0], 3))
		ft_cd(pars, current);
	if (!ft_strncmp("echo", current->agr[0], 5))
		ft_echo(pars, current);
	if (!ft_strncmp("env", current->agr[0], 4))
		ft_env(pars, current);
	if (!ft_strncmp("exit", current->agr[0], 5))
		ft_exit(pars, current);
	if (!ft_strncmp("export", current->agr[0], 7))
		ft_export(pars, current);
	if (!ft_strncmp("pwd", current->agr[0], 4))
		ft_pwd(pars, current);
	if (!ft_strncmp("unset", current->agr[0], 6))
		ft_unset(pars, current);
}

void	exec_builtin_inout(t_pars *pars, t_cmd *current)
{
	int	copy[2];

	if (current->infile < 0 || current->outfile < 0)
		return ;
	copy[0] = dup(STDIN_FILENO);
	if (copy[0] < 0)
		all_clear(pars, EXIT_FAILURE);
	if (dup2(pars->command->infile, STDIN_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(pars->command->infile);
	copy[1] = dup(STDOUT_FILENO);
	if (copy[1] < 0)
		all_clear(pars, EXIT_FAILURE);
	if (dup2(pars->command->outfile, STDOUT_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(pars->command->outfile);
	exec_builtin(pars, current);
	if (dup2(copy[0], STDIN_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(copy[0]);
	if (dup2(copy[1], STDOUT_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(copy[1]);
}

void	exec_builtin_in(t_pars *pars, t_cmd *current)
{
	int	copy;

	if (current->infile < 0 || current->outfile < 0)
		return ;
	copy = dup(STDIN_FILENO);
	if (copy < 0)
		all_clear(pars, EXIT_FAILURE);
	if (dup2(pars->command->infile, STDIN_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(pars->command->infile);
	exec_builtin(pars, current);
	if (dup2(copy, STDIN_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(copy);
}

void	exec_builtin_out(t_pars *pars, t_cmd *current)
{
	int	copy;

	if (current->infile < 0 || current->outfile < 0)
		return ;
	copy = dup(STDOUT_FILENO);
	if (copy < 0)
		all_clear(pars, EXIT_FAILURE);
	if (dup2(pars->command->outfile, STDOUT_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(pars->command->outfile);
	exec_builtin(pars, current);
	if (dup2(copy, STDOUT_FILENO) < 0)
		all_clear(pars, EXIT_FAILURE);
	close(copy);
}

void	solo_builtin(t_pars *pars, t_cmd *current)
{
	if (pars->command->infile != STDIN_FILENO
		&& pars->command->outfile != STDOUT_FILENO)
		exec_builtin_inout(pars, current);
	else if (pars->command->infile != STDIN_FILENO)
		exec_builtin_in(pars, current);
	else if (pars->command->outfile != STDOUT_FILENO)
		exec_builtin_out(pars, current);
	else
		exec_builtin(pars, current);
}
