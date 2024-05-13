/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:47:36 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/28 19:29:04 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	norme_init(t_norme *tab, int l)
{
	tab->strs = malloc((l + 1) * sizeof(char *));
	if (!tab->strs)
		return (0);
	tab->strs[l] = 0;
	tab->tmp = tab->strs;
	return (1);
}

int	pospos(char *str, char *c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > 0 && (str[i] == '\'' || str[i] == '"'))
		{
			*c = str[i];
			break ;
		}
		if (str[i] < 0)
			str[i] *= -1;
	}
	return (i);
}

void	open_single_outfile(char *str, t_cmd *cmd, char *tmp)
{
	(void)tmp;
	if (cmd->outfile == -1 || cmd->infile == -1)
		return ;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	cmd->outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (cmd->outfile == -1)
		perror(str);
}

void	open_single_infile(char *str, t_cmd *cmd, char *tmp)
{
	(void)tmp;
	if (cmd->outfile == -1 || cmd->infile == -1)
		return ;
	if (cmd->infile != 0)
		close(cmd->infile);
	cmd->infile = open(str, O_RDONLY, 0666);
	if (cmd->infile == -1)
		perror(str);
}

void	open_double_outfile(char *str, t_cmd *cmd, char *tmp)
{
	(void)tmp;
	if (cmd->outfile == -1 || cmd->infile == -1)
		return ;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	cmd->outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (cmd->outfile == -1)
		perror(str);
}
