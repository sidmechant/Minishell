/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coucou.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:37:20 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/29 05:43:28 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_in_child(t_pars *pars)
{
	t_cmd	*tmp;

	tmp = pars->command;
	while (tmp)
	{
		if (tmp->infile != STDIN_FILENO)
			close(tmp->infile);
		tmp = tmp->next;
	}
}

void	close_out_child(t_pars *pars)
{
	t_cmd	*tmp;

	tmp = pars->command;
	while (tmp)
	{
		if (tmp->outfile != STDOUT_FILENO && tmp->outfile != STDERR_FILENO)
			close(tmp->outfile);
		tmp = tmp->next;
	}
}

char	*ft_create(char *tmp, t_cmd *cmd)
{
	tmp = malloc(sizeof(char) * 3);
	if (!tmp)
		all_clear(cmd->pars, EXIT_FAILURE);
	tmp[0] = '\n';
	tmp[1] = 127;
	tmp[2] = '\0';
	return (tmp);
}

char	*malloc_void(t_cmd *cmd)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		all_clear(cmd->pars, EXIT_FAILURE);
	str[0] = '\0';
	return (str);
}

void	open_double_infile_2(char *limit, t_cmd *cmd, char *s)
{
	char	*file;
	char	*path_hide;
	int		stock;

	(void)s;
	(void)limit;
	stock = 0;
	file = ft_itoa(cmd->infile);
	if (!file)
		all_clear(cmd->pars, EXIT_FAILURE);
	path_hide = ft_strjoin("/proc/self/fd/", file);
	if (!path_hide)
		all_clear(cmd->pars, EXIT_FAILURE);
	stock = open(path_hide, O_RDONLY);
	free(file);
	free(path_hide);
	close(cmd->infile);
	cmd->infile = stock;
}
