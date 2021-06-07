/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:21:00 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:21:00 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			n;

	n = ft_strlen(s) + 1;
	while (n--)
		if (s[n] == (unsigned char)c)
			return ((char *)s + n);
	return (0);
}
