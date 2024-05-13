/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 05:28:37 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/29 05:44:44 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = (char)n + 48;
	if (n >= 0 && n <= 9)
		write(fd, &c, 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	write_util(int count)
{
	write(2, "warning: here-document at line ", 32);
	ft_putnbr_fd(count, 2);
	write(2, " delimited by end-of-file\n", 26);
}

void	norme_print(t_cmd *cmd, char *input)
{
	ft_putstr_fd(input, cmd->infile);
	ft_putchar_fd('\n', cmd->infile);
}
