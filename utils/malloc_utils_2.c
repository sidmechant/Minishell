/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 05:35:09 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/27 20:37:37 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			i++;
		if (str[i] && !(str[i] == '\'' || str[i] == '"'))
		{
			count++;
			while (str[i] && !(str[i] == '\'' || str[i] == '"'))
				i++;
		}
	}
	return (count);
}

char	*ft_catchwords(char *str)
{
	int		i;
	char	*dest;
	int		j;

	i = 0;
	while (str[i] && !(str[i] == '\'' || str[i] == '"'))
	{
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			break ;
		i++;
	}
	dest = malloc(sizeof(*dest) * i + 1);
	if (!dest)
		return (NULL);
	j = 0;
	while (str[j] && j < i)
	{
		dest[j] = str[j];
		j++;
	}
	while (j < i)
		dest[j++] = '\0';
	dest[j] = '\0';
	return (dest);
}

int	ft_cntword(char const *s, char c, int n)
{
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			n++;
		while (*s && *s != c)
			s++;
	}
	return (n);
}

char	**ft_split(char *s)
{
	t_iter		iter;
	char const	**tab;

	if (!s)
		return (NULL);
	iter.i = 0;
	iter.j = 0;
	tab = malloc(sizeof(char *) * (ft_words(s) + 1));
	if (!tab)
		return (NULL);
	while (s[iter.i] && iter.j < ft_words(s))
	{
		while (s[iter.i] && (s[iter.i] == '\'' || s[iter.i] == '"'))
			iter.i++;
		if (s[iter.i] && !(s[iter.i] == '\'' || s[iter.i] == '"'))
		{
			tab[iter.j] = ft_catchwords(s + iter.i);
			if (tab[iter.j++] == NULL)
				return (ft_free((char **)tab, iter.i));
		}
		while (s[iter.i] && !(s[iter.i] == '\'' || s[iter.i] == '"'))
			iter.i++;
	}
	tab[iter.j] = 0;
	return ((char **)tab);
}

char	**ft_split2(char *s, char c)
{
	int		l;
	int		i;
	t_norme	tab;

	if (!s)
		return (NULL);
	l = ft_cntword(s, c, 0);
	if (!norme_init(&tab, l))
		return (NULL);
	while (l--)
	{
		while (*s && *s == c)
			s++;
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		*tab.strs = ft_substr(s, 0, i);
		if (!*tab.strs++)
			return (free_strs(tab.tmp));
		while (*s && *s != c)
			s++;
	}
	return (tab.tmp);
}
