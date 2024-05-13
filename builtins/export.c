/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:15:11 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/24 14:47:53 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_variable(t_pars *pars, char *arg, t_env *ptr)
{
	t_env	*tmp;

	tmp = pars->env;
	while (tmp)
	{
		if (tmp == ptr)
		{
			free(ptr->str);
			ptr->str = NULL;
			ptr->str = ft_strdup(arg);
			if (!ptr->str)
				all_clear(pars, EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
}

void	add_variable(t_pars *pars, char *arg)
{
	t_env	*new;

	new = ft_lstnew(arg);
	if (!new)
		all_clear(pars, EXIT_FAILURE);
	ft_lstadd_back(&pars->env, new);
}

int	check_forbidden_export_variable(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+')
		{
			if (arg[i + 1] == '=')
				return (2);
			else
				return (1);
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	search_export_variable(t_pars *pars, char *arg)
{
	t_env	*tmp;

	tmp = pars->env;
	if (check_forbidden_export_variable(arg) == 2)
		return (0);
	if (check_forbidden_export_variable(arg) == 1)
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_exitcode = 1;
		return (1);
	}
	while (tmp)
	{
		if (find_export_variable(arg, tmp->str))
			return (replace_variable(pars, arg, tmp), 0);
		tmp = tmp->next;
	}
	if (!is_equal(arg))
		return (0);
	add_variable(pars, arg);
	return (0);
}

void	ft_export(t_pars *pars, t_cmd *current)
{
	int	i;
	int	trigger;

	i = 1;
	trigger = 0;
	while (current->agr[i])
	{
		if (search_export_variable(pars, current->agr[i]) == 1)
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
