/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:13:22 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/24 14:49:53 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	find_export_variable(char *arg, char *variable)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=' && variable[i])
	{
		if (arg[i] != variable[i])
			return (0);
		i++;
	}
	if (variable[i] == arg[i])
		return (1);
	return (0);
}

int	find_env_variable(char *arg, char *variable)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (arg[i] || (variable[i] && i < len))
	{
		if (arg[i] != variable[i])
			return (0);
		i++;
	}
	if (variable[i] == '=')
		return (1);
	return (0);
}
