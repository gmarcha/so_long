/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:19:14 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:19:14 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char sep)
{
	int				count;
	int				i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static char	*allocate_string(char const *s, char c)
{
	char			*str;
	int				j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	str = (char *)malloc(j + 1);
	if (str == 0)
		return (0);
	return (str);
}

static char	**split_words(char const *s, char c, char **strs, int len)
{
	int				i;
	int				j;

	i = 0;
	while (i < len)
	{
		while (*s && *s == c)
			s++;
		strs[i] = allocate_string(s, c);
		if (strs[i] == 0)
			return (ft_free_strs(strs, i));
		j = 0;
		while (*s && *s != c)
			strs[i][j++] = *s++;
		strs[i++][j] = 0;
	}
	strs[i] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	int				len;

	if (s == 0)
		return (0);
	len = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (strs == 0)
		return (0);
	if (split_words(s, c, strs, len) == 0)
		return (0);
	return (strs);
}
