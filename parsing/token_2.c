/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:35:22 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/29 05:45:13 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_double_infile(t_cmd *cmd, char *limit, char *s)
{
	char	*input;
	int		count;

	free(s);
	count = 0;
	while (213)
	{
		count++;
		input = readline(">");
		if (ft_strcmpenv(input, limit, ft_strlen(input)))
		{
			close(cmd->infile);
			norme_chelou(limit, cmd);
			exit (0);
		}
		if (!input)
		{
			norme_chelou(limit, cmd);
			free(input);
			write_util(count);
			exit (0);
		}
		norme_print(cmd, input);
		free(input);
	}
}

void	open_double_infile(char *limit, t_cmd *cmd, int exp, char *s)
{
	int			pid;
	int			status;

	(void)exp;
	cmd->infile = open("/tmp/", __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if (cmd->infile < 0)
		return ;
	pid = fork();
	if (pid < 0)
	{
		free(s);
		free(limit);
		all_clear(cmd->pars, EXIT_FAILURE);
	}
	if (pid == 0)
		handle_double_infile(cmd, limit, s);
	waitpid(pid, &status, 0);
	open_double_infile_2(limit, cmd, s);
}

char	*ft_positive_token(char *str, t_cmd *cmd)
{
	int		i;
	char	*ptr;
	char	*tmp;
	char	*save;
	char	c;

	c = 0;
	i = pospos(str, &c);
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		all_clear(cmd->pars, EXIT_FAILURE);
	if (c == '"' || c == '\'')
	{
		save = recup_token(str + i);
		ptr = save;
		save = ft_strjoin(tmp, save);
		free(ptr);
	}
	else
		save = ft_strjoin(tmp, "");
	free(tmp);
	ft_positive_char(save);
	return (save);
}

void	openfiles(char *str, int c, int j, t_cmd *cmd)
{
	char	*tmp;
	char	*savefile;

	tmp = NULL;
	savefile = NULL;
	tmp = ft_substr(str, 0, j);
	if (!tmp)
		all_clear(cmd->pars, EXIT_FAILURE);
	savefile = ft_positive_token(tmp, cmd);
	if (c == 1)
		open_single_outfile(savefile, cmd, tmp);
	else if (c == 2)
		open_single_infile(savefile, cmd, tmp);
	else if (c == 3)
		open_double_outfile(savefile, cmd, tmp);
	else if (c == 4 || c == 5)
		open_double_infile(savefile, cmd, c, tmp);
	if (tmp)
		free(tmp);
	if (savefile)
		free(savefile);
}

char	*recup_token(char *str)
{
	char	*ptr;
	char	**tab;
	char	*save;
	int		i;

	i = 0;
	tab = NULL;
	save = NULL;
	ptr = NULL;
	tab = ft_split(str);
	while (tab[i])
	{
		save = ft_strjoin(save, tab[i]);
		free(ptr);
		ptr = save;
		i++;
	}
	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	return (save);
}
