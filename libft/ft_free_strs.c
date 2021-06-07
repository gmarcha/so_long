/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:40:46 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/05 18:29:12 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_strs(char **strs, int size)
{
	int				i;

	i = 0;
	while (i < size)
		free(strs[i++]);
	free(strs);
	return (0);
}
