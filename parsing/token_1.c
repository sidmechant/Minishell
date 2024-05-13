/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:24:36 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/29 00:35:42 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	id_files(char *str, int *c, int i, t_cmd *cmd)
{
	int		j;
	char	s;

	s = 0;
	s = if_quote(str[i], &i);
	j = i;
	while (str[j] && str[j] != s && str[j] != '|'
		&& str[j] != '<' && str[j] != '>')
		j++;
	if ((s == '"' || s == '\'') && str[j] && str[j] != ' '
		&& str[j] != '>' && str[j] != '<' && str[j] != '|')
	{
		j = i;
		return (id_files(str, c, i, cmd));
	}
	cmd->redi = 0;
	cmd->files = 1;
	openfiles(str + i, *c, j - i, cmd);
	return (j - 1);
}

int	id_redir(char *str, int *c, int i, t_cmd *cmd)
{
	int	j;

	if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
	{
		*c = 3;
		i++;
	}
	else if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
	{
		*c = 4;
		i++;
	}
	else if (str[i] == '>')
		*c = 1;
	else if (str[i] == '<')
		*c = 2;
	j = i;
	while (str[j] && str[j] == ' ' && str[j + 1] != '|')
		j++;
	cmd->redi = 1;
	return (j);
}

int	ft_negative_char(char *str)
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
				if (str[i] > 0)
					str[i] *= -1;
				if (str[i])
					i++;
			}
		}
		if (str[i])
			i++;
	}
	return (1);
}

t_cmd	*command_attribution(t_pars *pars, t_cmd *cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		all_clear(pars, EXIT_FAILURE);
	cmd->redi = 0;
	cmd->files = 1;
	cmd->cmd = 0;
	cmd->arg = 1;
	cmd->agr = NULL;
	cmd->strarg = NULL;
	cmd->strcmd = NULL;
	cmd->outfile = 1;
	cmd->infile = 0;
	cmd->status = 0;
	cmd->pars = pars;
	cmd->next = NULL;
	return (cmd);
}

void	token(char *str, t_cmd **cmd, t_pars *pars)
{
	int	redi;
	int	i;

	i = 0;
	redi = 0;
	*cmd = command_attribution(pars, *cmd);
	ft_negative_char(str);
	while (str[i] && str[i] != '|')
	{
		if (!(*cmd)->redi && (*cmd)->files && (str[i] == '<' || str[i] == '>'))
			i = id_redir(str, &redi, i, (*cmd));
		else if ((*cmd)->redi && (*cmd)->files && (str[i] != ' '))
			i = id_files(str, &redi, i, (*cmd));
		else if (!(*cmd)->redi && (*cmd)->files
			&& !(*cmd)->cmd && (*cmd)->arg && str[i] != ' ')
			i = id_cmd(str, i, str[i], (*cmd));
		else if (!(*cmd)->redi && (*cmd)->files && (*cmd)->cmd && str[i] != ' ')
			i = id_arg(str, i, str[i], (*cmd));
		if (!str[i] || str[i] == '|')
			break ;
		i++;
	}
	fill_tab_exec(*cmd, pars);
	if (str[i++])
		token(str + i, &((*cmd)->next), pars);
}
