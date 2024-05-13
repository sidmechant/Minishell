/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:14:56 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/23 21:01:34 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_forbidden_env_variable(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	remove_variable(t_pars *pars, t_env *ptr)
{
	t_env	*tmp;
	t_env	*copy;

	tmp = pars->env;
	copy = NULL;
	if (tmp == ptr)
	{
		pars->env = pars->env->next;
		free(tmp->str);
		free(tmp);
		tmp = NULL;
	}
	else
	{
		while (tmp->next && tmp->next != ptr)
			tmp = tmp->next;
		copy = tmp->next;
		tmp->next = tmp->next->next;
		free(copy->str);
		copy->str = NULL;
		free(copy);
		copy = NULL;
	}
}

int	search_env_variable(t_pars *pars, char *arg)
{
	t_env	*tmp;

	tmp = pars->env;
	if (check_forbidden_env_variable(arg))
	{
		ft_putstr_fd("unset: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_exitcode = 1;
		return (1);
	}
	while (tmp)
	{
		if (find_env_variable(arg, tmp->str))
		{
			remove_variable(pars, tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_unset(t_pars *pars, t_cmd *current)
{
	int	i;
	int	trigger;

	i = 1;
	trigger = 0;
	while (current->agr[i])
	{
		if (search_env_variable(pars, current->agr[i]))
		{
			trigger = 1;
			g_exitcode = 1;
		}
		else
		{
			if (trigger == 0)
				g_exitcode = 0;
		}
		i++;
	}
}
