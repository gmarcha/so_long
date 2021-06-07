/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:36:29 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/07 18:39:21 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int    key_hook(int keycode, t_root *root)
{
    if (keycode == 65307)
    {
        mlx_destroy_image(root->mlx, root->mlx_img);
        mlx_destroy_window(root->mlx, root->mlx_win);
        mlx_destroy_display(root->mlx);
        free(root);
        exit(0);
    }
    return (0);
}

int    main(void)
{
    t_root            *root;

    root = (t_root *)malloc(sizeof(t_root));
    if (root == 0)
        return (0);
    root->mlx = mlx_init();
    if (root->mlx == 0)
    {
        free(root);
        return (0);
    }
    root->mlx_win = mlx_new_window(root->mlx, 1920, 1080, "Hello world!");
    if (root->mlx_win == 0)
    {
        mlx_destroy_display(root->mlx);
        free(root);
        return (0);
    }
    root->mlx_img = mlx_new_image(root->mlx, 1920, 1080);
    {
        mlx_destroy_window(root->mlx, root->mlx_win);
        mlx_destroy_display(root->mlx);
        free(root);
        return (0);
    }
    mlx_put_image_to_window(root->mlx, root->mlx_win, root->mlx_img, 0, 0);
    mlx_hook(root->mlx_win, 2, (1L << 0), &key_hook, root);
    mlx_loop(root->mlx);
}
