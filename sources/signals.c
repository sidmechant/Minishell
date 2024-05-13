/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:20:14 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/20 04:01:36 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int status)
{
	(void)status;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exitcode = 130;
}

void	child_signal_return(int signum, t_cmd *current, int *flag)
{
	if (signum == SIGINT && *flag == 0)
	{
		*flag = 1;
		ft_putchar_fd('\n', 1);
		g_exitcode = (128 + SIGINT);
	}
	else if (signum == SIGQUIT && current->next == NULL)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		g_exitcode = (128 + SIGQUIT);
	}
}
