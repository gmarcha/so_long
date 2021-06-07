/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:14:47 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:14:47 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*s;
	size_t			n;

	n = nmemb * size;
	s = malloc(n);
	if (s == 0)
		return (0);
	return (ft_memset(s, 0, n));
}
