/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 03:47:37 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/13 03:47:37 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	had_move(t_root *root, int x, int y)
{
	if (root->game->player.x != x || root->game->player.y != y)
	{
		root->game->player_move++;
		ft_putnbr_fd(root->game->player_move, 1);
		ft_putendl_fd("", 1);
	}
}

static void	iscollectable(t_root *root)
{
	int				k;

	k = 0;
	while (k < root->game->count_coll)
	{
		if (root->game->coll[k].x == root->game->player.x
			&& root->game->coll[k].y == root->game->player.y)
		{
			root->game->coll[k].x = -1;
			root->game->coll[k].y = -1;
			root->game->player_coll++;
		}
		k++;
	}
}

void	update(t_root *root)
{
	int				x;
	int				y;

	x = root->game->player.x;
	y = root->game->player.y;
	if (root->game->player_up != 0)
		move_up(root, x, y);
	else if (root->game->player_down != 0)
		move_down(root, x, y);
	else if (root->game->player_left != 0)
		move_left(root, x, y);
	else if (root->game->player_right != 0)
		move_right(root, x, y);
	had_move(root, x, y);
	iscollectable(root);
	draw(root);
	if (root->game->exit.x == root->game->player.x
		&& root->game->exit.y == root->game->player.y)
		if (root->game->count_coll == root->game->player_coll)
			root_destroy(root, 0, 0);
}
