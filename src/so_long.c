/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:36:29 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/13 04:20:01 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	isber(char *file)
{
	int				len;

	len = ft_strlen(file);
	if (file == 0)
		return (0);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".ber") != 0)
		return (0);
	return (1);
}

int	main(int ac, char *av[])
{
	t_root			*root;

	if (ac != 2)
		die("invalid number of arguments", 0);
	if (isber(av[1]) == 0)
		die("invalid argument (<name>.ber)", 0);
	root = root_init(av[1]);
	draw(root);
	mlx_hook(root->mlx_win, 2, 1L << 0, key_press, root);
	mlx_hook(root->mlx_win, 3, 1L << 1, key_release, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, destroy_hook, root);
	mlx_loop(root->mlx);
	return (0);
}
