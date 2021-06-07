/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:57:12 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/03 13:22:10 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_num(int c, const char *base)
{
	size_t			i;

	i = 0;
	while (base[i])
		if (c == base[i++])
			break ;
	return (i - 1);
}

int	ft_atoi_base(const char *str, const char *base, size_t len_base)
{
	int				result;
	int				sign;

	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	sign = 1;
	if (*str == 43 || *str == 45)
		sign *= (*str++ & 2) - 1;
	result = 0;
	while (*str && ft_ischarset(*str, base))
		result = result * len_base + get_num(*str++, base);
	return (result * sign);
}
