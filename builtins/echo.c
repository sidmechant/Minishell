/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:32:43 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/19 21:28:43 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_echo_n(char *str)
{
	int	trigger;
	int	i;

	trigger = 0;
	i = 1;
	if (str[0] != '-' || !str || !*str)
		return (0);
	while (str[i])
	{
		trigger = 1;
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (trigger == 1)
		return (1);
	return (0);
}

void	ft_echo(t_pars *pars, t_cmd *current)
{
	int	i;
	int	trigger;

	(void)pars;
	i = 1;
	trigger = 0;
	while (current->agr[i] && check_echo_n(current->agr[i]))
	{
		trigger = 1;
		i++;
	}
	while (current->agr[i])
	{
		ft_putstr_fd(current->agr[i++], STDOUT_FILENO);
		if (current->agr[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (trigger == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exitcode = 0;
}
