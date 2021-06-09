/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:35:43 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/07 18:38:08 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <mlx.h>
# include <mlx_int.h>
# include "libft.h"

typedef struct s_coord
{
	int				x;
	int				y;
}				t_coord;

typedef struct s_game
{
	int			**map;
	int			height;
	int			size;
	t_coord		player_pos;
	int			player_move;
	int			player_coll;
	t_coord		exit_pos;
	t_coord		*obj_pos;
}				t_game;

typedef struct s_root
{
    void            *mlx;
    void            *mlx_win;
    t_img            *mlx_img;
	t_game			*game;
}                t_root;

void			mlx_draw_pixel(t_img *mlx_img, int x, int y, int color);
unsigned int	mlx_rgb_to_int(int o, int r, int g, int b);

#endif
