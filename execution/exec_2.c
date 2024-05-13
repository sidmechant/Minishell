/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:16:03 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/21 13:18:53 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *check)
{
	if (!ft_strncmp("cd", check, 3))
		return (1);
	if (!ft_strncmp("echo", check, 5))
		return (1);
	if (!ft_strncmp("env", check, 4))
		return (1);
	if (!ft_strncmp("exit", check, 5))
		return (1);
	if (!ft_strncmp("export", check, 7))
		return (1);
	if (!ft_strncmp("pwd", check, 4))
		return (1);
	if (!ft_strncmp("unset", check, 6))
		return (1);
	return (0);
}

int	count_command(t_pars *pars)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = pars->command;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_cmd	*last_command(t_pars *pars)
{
	t_cmd	*last;

	if (!pars->command)
		return (NULL);
	last = pars->command;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	create_pipe(t_pars *pars, t_cmd *current, int cmd_nbr)
{
	if (cmd_nbr > 1 && current->next != NULL)
	{
		if (pipe(pars->pipefd) < 0)
			all_clear(pars, EXIT_FAILURE);
	}
}
