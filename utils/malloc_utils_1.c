/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:56:58 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/22 12:18:11 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_charsize(long n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count++;
		return (count);
	}
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_fill(char *str, int len, long nb)
{
	str[len] = '\0';
	len--;
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[len--] = nb % 10 + 48;
		nb /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	nb = (long)n;
	len = ft_charsize(nb);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str = ft_fill(str, len, nb);
	return (str);
}
