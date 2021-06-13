/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_isvalid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 04:06:30 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/13 04:06:30 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	isborder(t_root *root, int i)
{
	if (i < root->game->width
		|| i > (root->game->width + 1) * (root->game->height - 1)
		|| i % (root->game->width + 1) == 0
		|| i % (root->game->width + 1) == root->game->width - 1)
		return (1);
	return (0);
}

static void	isvalid(t_root *root, char *file, int i)
{
	if (file[i] == 'P')
		root->game->count_player++;
	else if (file[i] == 'E')
		root->game->count_exit++;
	else if (file[i] == 'C')
		root->game->count_coll++;
	else if (file[i] == '1' || file[i] == '0')
		return ;
	else
	{
		free(file);
		root_destroy(root, "map content is invalid", 0);
	}
}

void	map_isvalid(t_root *root, char *file)
{
	int				i;

	i = -1;
	while (file[++i] != 0)
	{
		if (file[i] == '\n')
			continue ;
		if (isborder(root, i))
		{
			if (file[i] != '1')
			{
				free(file);
				root_destroy(root, "map isn't surrounded by walls", 0);
			}
		}
		else
			isvalid(root, file, i);
	}
	if (root->game->count_player != 1
		|| root->game->count_exit != 1
		|| root->game->count_coll < 1)
	{
		free(file);
		root_destroy(root, "map configuration is invalid", 0);
	}
}
