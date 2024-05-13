/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 23:07:51 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/28 16:47:56 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_norme_1(char *s1, char *s2, char *s3)
{
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	free(s3);
	s3 = NULL;
}

void	norme_random(char *str, t_pars *pars)
{
	unsigned long long	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0 || (unsigned char)str[i] > 128)
		{
			env_list_clear(&pars->env);
			free(str);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)ptr;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	argus(int ac, char **av)
{
	(void)av;
	if (ac != 1)
		exit(EXIT_SUCCESS);
}

void	norme_chelou(char *str, t_cmd *cmd)
{
	close(cmd->infile);
	free(str);
	all_clear(cmd->pars, NO_EXIT);
}
