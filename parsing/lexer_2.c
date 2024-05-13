/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 03:49:49 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/19 04:08:43 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lex_pipe(char *str)
{
	int	i;
	int	bool_char;
	int	bool_pipe;

	i = 0;
	bool_char = 1;
	bool_pipe = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			bool_char = 0;
		if (str[i] == '|')
		{
			if (bool_char == 1)
				return (0);
			bool_pipe = 1;
			bool_char = 1;
		}
		i++;
	}
	if (bool_pipe == 1 && bool_char == 1)
		return (0);
	return (1);
}

int	lexer_redi(char *str)
{
	if (!lexer_last_redi(str))
		return (0);
	else if (!lexer_redi_pipe(str))
		return (0);
	else if (!lexer_redirection_char(str))
		return (0);
	else if (!lexer_sens(str))
		return (0);
	else if (!lexer_tripleredi(str))
		return (0);
	return (1);
}

int	lexer_last_redi(char *str)
{
	int	i;
	int	bool_char;

	bool_char = 0;
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] != ' ' && str[i] != '<' && str[i] != '>')
			bool_char = 1;
		if ((str[i] == '<' || str[i] == '>') && bool_char == 0)
		{
			return (0);
		}
		i--;
	}
	return (1);
}

int	lexer_redi_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[++i] == ' ' || str[i] == '<' || str[i] == '>')
			{
			}
			if (str[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	lexer_redirection_char(char *str)
{
	int	i;
	int	chevron;
	int	espace;

	i = 0;
	espace = 0;
	chevron = 0;
	while (str[i])
	{
		if (chevron && espace && (str[i] == '>' || str[i] == '<'))
			return (0);
		if (str[i] == '>' || str[i] == '<')
			chevron = 1;
		else if (str[i] == ' ' && chevron)
			espace = 1;
		else if (chevron && str[i] != 32)
		{
			chevron = 0;
			espace = 0;
		}
		i++;
	}
	return (1);
}
