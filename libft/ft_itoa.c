/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:16:47 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:16:47 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*nbr;
	unsigned int	nb;
	int				len_nbr;

	len_nbr = ft_nbrlen(n);
	nbr = (char *)malloc(len_nbr + 1);
	if (nbr == 0)
		return (0);
	nbr[len_nbr] = 0;
	nb = n;
	if (n < 0)
		nb = -n;
	while (len_nbr--)
	{
		nbr[len_nbr] = "0123456789"[nb % 10];
		nb /= 10;
	}
	if (n < 0)
		nbr[0] = '-';
	return (nbr);
}
