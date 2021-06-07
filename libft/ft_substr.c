/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:20:46 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:20:46 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sub(unsigned int start, size_t len, size_t len_s)
{
	char	*str;

	if (len_s < start)
		str = (char *)malloc(1);
	else if (len_s - start < len)
		str = (char *)malloc(len_s - start + 1);
	else
		str = (char *)malloc(len + 1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			len_s;
	size_t			i;

	if (s == 0)
		return (0);
	len_s = ft_strlen(s);
	str = sub(start, len, len_s);
	if (str == 0)
		return (0);
	i = 0;
	if (start < len_s)
	{
		while (s[i + start] && i < len)
		{
			str[i] = s[i + start];
			i++;
		}
	}
	str[i] = 0;
	return (str);
}
