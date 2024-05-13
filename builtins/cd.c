/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:19:31 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/27 00:32:32 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_error_msgs(char *arg, int error)
{
	if (error == 20)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	}
	if (error == 2)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	if (error == 13)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	g_exitcode = 1;
}

void	free_buffers(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	is_pwd(char *str)
{
	if (str[0] != 'P')
		return (0);
	if (str[1] != 'W')
		return (0);
	if (str[2] != 'D')
		return (0);
	if (str[3] != '=')
		return (0);
	return (1);
}

void	update_pwd(t_pars *pars)
{
	t_env		*tmp;
	char		*pwd;
	char		*str;

	pwd = ft_strdup("PWD=");
	if (!pwd)
		all_clear(pars, EXIT_FAILURE);
	str = getcwd(0, 0);
	tmp = pars->env;
	while (tmp)
	{
		if (is_pwd(tmp->str))
		{
			free(tmp->str);
			tmp->str = NULL;
			tmp->str = ft_strjoin(pwd, str);
			if (!tmp->str)
			{
				free_buffers(pwd, str);
				all_clear(pars, EXIT_FAILURE);
			}
		}
		tmp = tmp->next;
	}
	free_buffers(pwd, str);
}

void	ft_cd(t_pars *pars, t_cmd *current)
{
	int	i;

	i = 1;
	while (current->agr[i])
		i++;
	if (i == 1)
		g_exitcode = 0;
	else if (i == 2)
	{
		if (chdir(current->agr[1]) < 0)
			cd_error_msgs(current->agr[1], errno);
		else
		{
			update_pwd(pars);
			g_exitcode = 0;
		}
	}
	else
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		g_exitcode = 1;
	}
}
