/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:48:55 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/02 12:10:59 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen_base(int n, size_t len_base)
{
	size_t			len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= (int)len_base;
		len++;
	}
	return (len);
}
