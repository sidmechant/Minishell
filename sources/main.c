/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:48:43 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/28 16:35:00 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exitcode = 0;

t_env	*get_environment(char **envp)
{
	int		i;
	t_env	*first;
	t_env	*copy;
	t_env	*new;

	i = 0;
	if (!envp || !*envp)
		return (NULL);
	copy = ft_lstnew(envp[i]);
	if (!copy)
		exit(EXIT_FAILURE);
	first = copy;
	while (envp[++i])
	{
		new = ft_lstnew(envp[i]);
		if (!new)
		{
			env_list_clear(&first);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&copy, new);
		copy = new;
	}
	return (first);
}

void	initialize_struct(t_pars *pars)
{
	pars->command = NULL;
	pars->env = NULL;
}

int	check_eof_or_void(char *str, t_env **envp)
{
	if (!str)
	{
		env_list_clear(envp);
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	if (!*str)
		return (1);
	else
		return (0);
}

void	file_error(t_pars *pars, t_cmd *current, int cmd_nbr)
{
	if (cmd_nbr > 1)
	{
		if (current == pars->command)
		{
			close(pars->pipefd[0]);
			close(pars->pipefd[1]);
		}
		else if (current == last_command(pars))
		{
			close(pars->pipefd[0]);
			close(pars->pipefd[1]);
		}
		else
		{
			close(pars->savefd[0]);
			close(pars->pipefd[1]);
			close(pars->savefd[0]);
			close(pars->pipefd[1]);
		}
	}
	all_clear(pars, EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_pars	pars;

	argus(ac, av);
	initialize_struct(&pars);
	signal(SIGQUIT, SIG_IGN);
	pars.env = get_environment(envp);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		str = readline(MINISHELL);
		signal(SIGINT, SIG_IGN);
		if (check_eof_or_void(str, &pars.env))
			continue ;
		norme_random(str, &pars);
		add_history(str);
		if (lexer_shell(&str, &pars) == 1)
		{
			token(str, &pars.command, &pars);
			exec_command_line(&pars, str);
			cmd_list_clear(&pars.command);
		}
		free(str);
	}
	return (0);
}
