/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:26:30 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/03 13:23:49 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_str(const char **strs, const char *sep)
{
	size_t			count;
	size_t			i;

	count = 0;
	i = 0;
	while (strs[i])
		count += ft_strlen(strs[i++]);
	return (count + ft_strlen(sep) * (i - 1));
}

char	*ft_strsjoin(const char **strs, const char *sep)
{
	char			*str;
	size_t			i;

	str = (char *)malloc(sizeof(char) * (count_str(strs, sep) + 1));
	if (str == 0)
		return (0);
	*str = 0;
	i = 0;
	while (strs[i])
	{
		if (i)
			ft_strcat(str, sep);
		ft_strcat(str, strs[i++]);
	}
	return (str);
}
