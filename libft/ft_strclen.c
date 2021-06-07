/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:14:33 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/02 16:31:10 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(const char *s, const char *charset)
{
	size_t			i;

	i = 0;
	while (s[i])
	{
		if (ft_ischarset(s[i], charset))
			break ;
		i++;
	}
	return (i);
}
