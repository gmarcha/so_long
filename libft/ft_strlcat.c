/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:19:42 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:19:42 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dst_len;
	size_t			i;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i] && i + dst_len + 1 < size)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	if (size != 0)
		dst[i + dst_len] = 0;
	if (size <= dst_len)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + dst_len);
}
