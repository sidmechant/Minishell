/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 04:18:01 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/19 04:20:46 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer_sens(char *str)
{
	int	i;
	int	d;
	int	g;

	i = 0;
	d = 0;
	g = 1;
	while (str[i])
	{
		if (str[i] == '>')
		{
			d = 1;
			while (str[i] && str[i + 1] && (str[i + 1] == ' '
					|| str[i + 1] == '>'))
				i++;
			if (str[i + 1] != '<' && str[i + 1])
				d = 0;
		}
		else if (str[i] == '<' && d == 1)
			g = 0;
		i++;
	}
	if (d && !g)
		return (0);
	return (1);
}

int	lexer_tripleredi(char *str)
{
	int	i;
	int	n;

	if (!str)
		return (0);
	i = -1;
	n = 0;
	while (str[++i])
	{
		if (str[i + 1] && str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (str[i] == '<' || str[i] == '>')
			n++;
		else
			n = 0;
		if (n >= 3)
			return (0);
	}
	return (1);
}
