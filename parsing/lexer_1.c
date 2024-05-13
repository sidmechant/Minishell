/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:34:16 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/27 17:05:52 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	negative_expand(char *str, int i)
{
	if (!str[i] || str[i] != '<')
		return (i);
	i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\"'))
		i++;
	if (str[i] == '$')
		str[i] = -1 * str[i];
	return (i);
}

int	ft_check_expand(char *str, char c, int i)
{
	int	j;

	if (c == '"')
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			j = ++i;
			if (str[++j] == '$')
				j = ft_check_expand(str, c, j);
			return (j);
		}
		if (str[i] == '$' && str[i + 1] && !ft_isquote(str[i + 1]))
		{
			j = ++i;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			if (str[j] == '$')
				j = ft_check_expand(str, c, j);
			return (j);
		}
	}
	return (i);
}

int	ft_negative_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				i = ft_check_expand(str, c, i);
				if (str[i] && str[i] != c)
					str[i] = -1 * str[i];
				if (str[i] && str[i] != c)
					i++;
			}
		}
		if (str[i] == '<')
			i = negative_expand(str, i + 1) - 1;
		if (str[i])
			i++;
	}
	return (1);
}

int	lex_quote(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 1;
	while (str[i])
	{
		if (str[i] == '"' && double_quote == 1 && single_quote == 0)
			double_quote = 0;
		else if (str[i] == '"' && double_quote == 0 && single_quote == 0)
			double_quote = 1;
		else if (str[i] == '\'' && single_quote == 0 && double_quote == 1)
			single_quote = 1;
		else if (str[i] == '\'' && single_quote == 1 && double_quote == 1)
			single_quote = 0;
		i++;
	}
	if (single_quote == double_quote)
		return (0);
	return (1);
}

int	lexer_shell(char **str, t_pars *pars)
{
	if (!lex_quote(*str))
	{
		ft_putstr_fd("Erreur de Syntaxe : Quote\n", STDERR_FILENO);
		return (0);
	}
	ft_negative_quote(*str);
	if (!lex_pipe(*str))
	{
		ft_putstr_fd("Erreur de Syntaxe : Pipe\n", STDERR_FILENO);
		return (0);
	}
	if (!lexer_redi(*str))
	{
		ft_putstr_fd("Erreur de Syntaxe : Redirection\n", STDERR_FILENO);
		return (0);
	}
	if (check_space(*str))
		return (0);
	*str = ft_init_pars(*str, pars);
	*str = ft_init_pars2(*str, pars);
	return (1);
}
