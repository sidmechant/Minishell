/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:15:29 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/20 11:16:51 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_exitcode(char *str)
{
	int		i;
	int		neg;
	long	check;

	check = 0;
	i = 0;
	neg = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = check * 10 + (str[i++] - 48);
		if (check < -2147483648 || check > 2147483647)
			return (255);
	}
	return (check);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_program(t_pars *pars, t_cmd *current, int optno)
{
	if (optno == 1)
	{
		g_exitcode = 0;
		all_clear(pars, NO_EXIT);
		exit(g_exitcode);
	}
	if (optno == 2)
	{
		g_exitcode = 2;
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(current->agr[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		all_clear(pars, NO_EXIT);
		exit(g_exitcode);
	}
}

void	ft_exit(t_pars *pars, t_cmd *current)
{
	int	i;
	int	code;

	i = 0;
	while (current->agr[i])
		i++;
	if ((i - 1) == 0)
		exit_program(pars, current, 1);
	if ((i - 1) == 1)
	{
		if (!check_digit(current->agr[1]))
			exit_program(pars, current, 2);
		code = get_exitcode(current->agr[1]);
		g_exitcode = (int)code;
		all_clear(pars, NO_EXIT);
		exit(g_exitcode);
	}
	if ((i - 1) > 1)
	{
		if (!check_digit(current->agr[1]))
			exit_program(pars, current, 2);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		g_exitcode = 1;
	}
}
