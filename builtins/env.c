/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:46:42 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/19 21:28:49 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_pars *pars, t_cmd *current)
{
	t_env	*tmp;

	(void)pars;
	(void)current;
	tmp = pars->env;
	while (tmp)
	{
		ft_putstr_fd(tmp->str, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		tmp = tmp->next;
	}
	g_exitcode = 0;
}
