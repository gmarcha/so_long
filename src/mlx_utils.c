/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:38:53 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/07 18:39:12 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    mlx_draw_pixel(t_img *mlx_img, int x, int y, int color)
{
    char            *target;

    target = mlx_img->data + (x * mlx_img->bpp / 8 + y * mlx_img->size_line);
    *(unsigned int *)target = color;
}

unsigned int    mlx_rgb_to_int(int o, int r, int g, int b)
{
    return (o << 24 | r << 16 | g << 8 | b);
}
