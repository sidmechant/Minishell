/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 05:23:56 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/28 19:57:12 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_save_pos_expand(char *str, int i, int j, t_pars *pars)
{
	char	*tmp;
	t_env	*temp;
	int		ok;

	ok = 0;
	if (pars->env)
		temp = pars->env;
	while (temp)
	{
		if (ft_strcmpenv(str + i, temp->str, j - i) == 1)
		{
			tmp = str;
			str = ft_replace(tmp, ft_strchr(temp->str, '=') + 1, i, j);
			if (!str)
				return (free(tmp), all_clear(pars, EXIT_FAILURE), NULL);
			return (free(tmp), str);
		}
		ok++;
		temp = temp->next;
	}
	tmp = str;
	str = ft_replace(tmp, NULL, i, j);
	if (!str)
		return (free(tmp), all_clear(pars, EXIT_FAILURE), NULL);
	return (free(tmp), str);
}

int	ft_positive_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
	return (1);
}
