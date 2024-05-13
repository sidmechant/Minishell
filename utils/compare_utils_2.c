/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 03:46:00 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/27 18:33:16 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/minishell.h"

int	ft_isquote(int c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

char	if_quote(char c, int *i)
{
	if (c != '\'' && c != '"')
		return (' ');
	*i = *i + 1;
	return (c);
}

int	check_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	}
	return (1);
}

int	find_slash(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmpenv(char *str, char *env, int len)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (i != len)
		return (0);
	j = 0;
	while (j < i)
	{
		if (str[j] == env[j])
			j++;
		else
			break ;
	}
	if (j != i)
		return (0);
	return (1);
}
