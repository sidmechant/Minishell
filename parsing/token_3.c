/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:14:50 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/29 02:36:08 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_tab_exec(t_cmd *cmd, t_pars *pars)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(cmd->strcmd, cmd->strarg);
	if (!tmp)
		all_clear(pars, EXIT_FAILURE);
	cmd->agr = ft_split2(tmp, 127);
	if (!cmd->agr)
	{
		free(tmp);
		all_clear(pars, EXIT_FAILURE);
	}
	while (cmd->agr[i])
	{
		if (cmd->agr[i][0] == '\n')
				cmd->agr[i][0] = '\0';
		i++;
	}
	free(tmp);
}

void	saves_arg(char *str, int i, int j, t_cmd *cmd)
{
	char	*ptr;
	char	*tmp;
	char	*save;
	char	*first;
	char	charset[2];

	charset[0] = 127;
	charset[1] = '\0';
	if (!cmd->strarg)
		cmd->strarg = malloc_void(cmd);
	first = cmd->strarg;
	tmp = ft_substr(str + i, 0, j - i);
	if (tmp[0] == '\0')
		save = ft_create(tmp, cmd);
	else
		save = ft_strjoin(tmp, charset);
	free(tmp);
	cmd->strarg = ft_strjoin(first, save);
	ptr = cmd->strarg;
	cmd->strarg = ft_positive_token(cmd->strarg, cmd);
	free_norme_1(ptr, save, first);
}

int	id_arg(char *str, int i, char c, t_cmd *cmd)
{
	int	j;

	c = if_quote(c, &i);
	j = i;
	while (str[j] && str[j] != c && str[j] != '|'
		&& str[j] != '<' && str[j] != '>')
		j++;
	if ((c == '"' || c == '\'') && str[j] && (str[j] != ' '
			&& str[j] != '>' && str[j] != '<' && str[j] != '|'))
	{
		j = i;
		return (id_arg(str, i, str[j], cmd));
	}
	cmd->arg = 0;
	saves_arg(str, i, j, cmd);
	return (j - 1);
}

void	saves_cmd(char *str, int i, int j, t_cmd *cmd)
{
	char	*tmp;
	char	*new;
	char	charset[2];

	if (i == -1)
	{
		cmd->strcmd = malloc(sizeof(char));
		if (!cmd->strcmd)
			all_clear(cmd->pars, EXIT_FAILURE);
		cmd->strcmd[0] = '\0';
		return ;
	}
	charset[0] = 127;
	charset[1] = '\0';
	tmp = ft_substr(str + i, 0, j - i);
	if (!tmp)
		all_clear(cmd->pars, EXIT_FAILURE);
	cmd->strcmd = ft_positive_token(tmp, cmd);
	free(tmp);
	new = ft_strjoin(cmd->strcmd, charset);
	if (cmd->strcmd)
		free(cmd->strcmd);
	cmd->strcmd = new;
}

int	id_cmd(char *str, int i, char c, t_cmd *cmd)
{
	int	j;

	c = if_quote(c, &i);
	j = i;
	while (str[j] && str[j] != c && str[j] != '|'
		&& str[j] != '<' && str[j] != '>')
		j++;
	if ((c == '"' || c == '\'') && str[j] && str[j] != ' '
		&& str[j] != '>' && str[j] != '<' && str[j] != '|')
	{
		j = i;
		return (id_cmd(str, i, str[j], cmd));
	}
	if (str[i] == ' ' || str[i] == '\'' || str[i] == '"')
		i = -1;
	saves_cmd(str, i, j, cmd);
	cmd->cmd = 1;
	cmd->arg = 0;
	return (j - 1);
}
