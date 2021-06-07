/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:26:51 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/03 13:24:39 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(const char *str, size_t len, const char *charset)
{
	size_t			count;
	size_t			i;

	count = 0;
	if (*str && !ft_ischarset(*str, charset))
		count++;
	i = 0;
	while (++i < len)
		if (ft_ischarset(str[i - 1], charset) && !ft_ischarset(str[i], charset))
			count++;
	return (count);
}

static char	*get_word(const char **str, const char *charset)
{
	char		*word;
	size_t		len;

	while (**str && ft_ischarset(**str, charset))
		(*str)++;
	len = ft_strclen(*str, charset);
	word = (char *)malloc(len + 1);
	if (word == 0)
		return (0);
	ft_strlcpy(word, *str, len + 1);
	*str += len;
	return (word);
}

char	**ft_csplit(const char *str, const char *charset)
{
	char			**strs;
	size_t			size;
	size_t			i;

	size = count_word(str, ft_strlen(str), charset);
	strs = (char **)malloc(sizeof(char *) * (size + 1));
	if (strs == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		strs[i] = get_word(&str, charset);
		if (strs[i] == 0)
			return (ft_free_strs(strs, i));
		i++;
	}
	strs[i] = 0;
	return (strs);
}
