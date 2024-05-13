/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:59:43 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/24 14:48:54 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_list_clear(t_env **envp)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		tmp = (*envp)->next;
		free((*envp)->str);
		free(*envp);
		*envp = tmp;
	}
	*envp = NULL;
}

void	cmd_list_clear(t_cmd **cmds)
{
	t_cmd	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		tmp = (*cmds)->next;
		free((*cmds)->strarg);
		(*cmds)->strarg = NULL;
		free((*cmds)->strcmd);
		(*cmds)->strcmd = NULL;
		(*cmds)->agr = free_strs((*cmds)->agr);
		free(*cmds);
		*cmds = NULL;
		*cmds = tmp;
	}
	*cmds = NULL;
}

void	all_clear(t_pars *pars, int flag)
{
	env_list_clear(&pars->env);
	cmd_list_clear(&pars->command);
	if (flag == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	else if (flag == NO_EXIT)
		return ;
}

char	**free_strs(char **ptr)
{
	int	i;

	i = -1;
	if (ptr)
	{
		while (ptr[++i])
		{
			if (ptr[i])
			{
				free(ptr[i]);
				ptr[i] = NULL;
			}
		}
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

char	**ft_free(char **tab, int i)
{
	while (i)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}
