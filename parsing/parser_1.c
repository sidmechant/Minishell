/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 04:36:36 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/27 18:37:45 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_replace_neg(char *str)
{
	int	i;
	int	single;

	single = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '>' || str[i] == '<'
			|| str[i] == '|')
		{
			if (str[i] == '\'')
				single = 1;
			str[i] *= -1;
		}
		if (single == 1 && str[i] == '$')
			str[i] *= -1;
		if (str[i] == '\t')
			str[i] = 32;
		i++;
	}
	return (1);
}

char	*ft_replace(char *str, char *node, int i, int j)
{
	char	*new;
	char	*tmp;

	new = ft_substr(str, 0, i - 1);
	if (!new)
		return (NULL);
	tmp = new;
	if (node)
	{
		ft_replace_neg(node);
		new = ft_strjoin(tmp, node);
		if (!new)
			return (free(tmp), NULL);
		free(tmp);
		tmp = new;
		new = ft_strjoin(tmp, str + j);
		if (!new)
			return (free(tmp), NULL);
		return (free(tmp), new);
	}
	new = ft_strjoin(tmp, str + j);
	if (!new)
		return (free(tmp), NULL);
	return (free(tmp), new);
}

char	*ft_replace_exitcode(char *str, int i, int j, t_pars *pars)
{
	char	*itoa;
	char	*ret;

	itoa = ft_itoa(g_exitcode);
	if (!itoa)
		all_clear(pars, EXIT_FAILURE);
	ret = ft_replace(str, itoa, i, j);
	if (!ret)
	{
		free(str);
		str = NULL;
		free(itoa);
		itoa = NULL;
		all_clear(pars, EXIT_FAILURE);
	}
	free(str);
	str = NULL;
	free(itoa);
	itoa = NULL;
	return (ret);
}

char	*ft_init_pars(char *str, t_pars *pars)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (str[++i])
	{	
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			str = ft_replace_exitcode(str, i + 1, i + 2, pars);
		else if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_'))
		{
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			tmp = str;
			str = ft_save_pos_expand(tmp, i + 1, j, pars);
			i--;
		}
	}
	return (str);
}

char	*ft_init_pars2(char *str, t_pars *pars)
{
	int		i;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
		{
			tmp = str;
			str = ft_save_pos_expand(tmp, i + 1, i + 2, pars);
			i--;
		}
		else if ((str[i] == '$' && str[i + 1] && ft_isquote(str[i + 1])))
		{
			tmp = str;
			str = ft_save_pos_expand(tmp, i + 1, i + 1, pars);
			i--;
		}
		if (i >= 0 && str[i] == '\t')
			str[i] = 32;
	}
	return (str);
}
