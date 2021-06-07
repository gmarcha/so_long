/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:12:59 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/03 13:18:35 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_convert_base(
	const char *str, const char *base_from, const char *base_to)
{
	int				nb;

	nb = ft_atoi_base(str, base_from, ft_strlen(base_from));
	return (ft_itoa_base(nb, base_to, ft_strlen(base_to)));
}
