/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:39:20 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/22 13:41:47 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**transform_empty_env(void)
{
	char	**rtrn;

	rtrn = malloc(sizeof(char *) * 2);
	if (!rtrn)
		return (NULL);
	rtrn[0] = ft_strdup("");
	if (!rtrn[0])
	{
		free(rtrn);
		return (NULL);
	}
	rtrn[1] = NULL;
	return (rtrn);
}

char	**transform_duplicate(t_env *tmp, char **strs, int size)
{
	int	i;

	i = 0;
	while (i < size && tmp)
	{
		strs[i] = ft_strdup(tmp->str);
		if (!strs)
			return (ft_free(strs, i));
		tmp = tmp->next;
		i++;
	}
	strs[size] = NULL;
	return (strs);
}

char	**transform_env(t_env *env)
{
	char	**transform;
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = env;
	if (!env)
	{
		transform = transform_empty_env();
		return (transform);
	}
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	transform = malloc(sizeof(char *) * (size + 1));
	if (!transform)
		return (NULL);
	tmp = env;
	transform = transform_duplicate(tmp, transform, size);
	return (transform);
}

void	exec_slash_command(t_pars *pars, t_cmd *current)
{
	char	**copy_env;

	copy_env = NULL;
	if (access(current->agr[0], X_OK) == 0)
	{
		copy_env = transform_env(pars->env);
		if (!copy_env)
		{
			write(STDERR_FILENO, "Error : Malloc failed !\n", 22);
			all_clear(pars, EXIT_FAILURE);
		}
		g_exitcode = 0;
		execve(current->agr[0], current->agr, copy_env);
	}
	exec_failed_2(pars, current, copy_env, errno);
	exit(g_exitcode);
}
