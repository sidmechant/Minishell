/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:24:03 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/20 00:24:38 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**secure_split_paths(char **strs, int n)
{
	int	i;

	i = 0;
	while (strs[i] && i < n)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

int	ft_wordcount(char const *str, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			wc++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (wc);
}

char	*ft_strndup(char const *src, int j, int *index)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * j + 1);
	if (!dest)
		return (NULL);
	while (i < j)
	{
		dest[i] = src[*index];
		i++;
		*index += 1;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_fill_split(char const *s, char c, char **strs)
{
	int	index;
	int	j;
	int	k;

	index = 0;
	k = 0;
	while (s[index])
	{
		if (s[index] != c)
		{
			j = 0;
			while (s[index + j] != c && s[index + j])
				j++;
			strs[k] = ft_strndup(s, j, &index);
			if (!strs[k])
				return (secure_split_paths(strs, k));
			k++;
		}
		else
			index++;
	}
	strs[k] = NULL;
	return (strs);
}

char	**ft_split_paths(char const *s, char c)
{
	char	**strs;

	if (!s || !*s)
		return (NULL);
	strs = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!strs)
		return (NULL);
	return (ft_fill_split(s, c, strs));
}
