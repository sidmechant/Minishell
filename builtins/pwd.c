/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:38:32 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/19 21:29:09 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_pars *pars, t_cmd *current)
{
	char	*str;

	(void)pars;
	(void)current;
	if (!chdir("."))
	{
		str = getcwd(0, 0);
		if (str)
		{
			ft_putstr_fd(str, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			free(str);
			g_exitcode = 0;
			return ;
		}
	}
}
