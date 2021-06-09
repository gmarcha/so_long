/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:36:29 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/09 22:27:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_matrix(int **m, int size)
{
	int				i;

	i = 0;
	while (i < size)
		free(m[i++]);
	free(m);
}

void	die(char *errmsg, int errnum)
{
	if (errmsg != 0 || errnum != 0)
		ft_putendl_fd("Error", 2);
	if (errmsg != 0)
		ft_putstr_fd(errmsg, 2);
	if (errmsg != 0 && errnum != 0)
		ft_putstr_fd(": ", 2);
	if (errnum != 0)
		ft_putstr_fd(strerror(errnum), 2);
	if (errmsg != 0 || errnum != 0)
	{
		ft_putendl_fd("", 2);
		exit(1);
	}
	exit(0);
}

void	game_destroy(t_game *game)
{
	int				i;

	if (game != 0)
	{
		if (game->obj_pos != 0)
			free(game->obj_pos);
		if (game->map != 0)
		{
			i = 0;
			while (i < game->height)
				free(game->map[i++]);
			free(game->map);
		}
		free(game);
	}
}

void	root_destroy(t_root *root, char *errmsg, int errnum)
{
	if (root != 0)
	{
		if (root->mlx_img != 0)	
			mlx_destroy_image(root->mlx, root->mlx_img);
		if (root->mlx_win != 0)
			mlx_destroy_window(root->mlx, root->mlx_win);
		if (root->mlx != 0)
			mlx_destroy_display(root->mlx);
		if (root->game != 0)
			game_destroy(root->game);
		free(root);
	}
	die(errmsg, errnum);
}

int		count_char(char *s, int c)
{
	int				count;
	int				i;

	count = 0;
	i = 0;
	while (s[i])
		if (s[i++] == c)
			count++;
	return (count);
}

void	map_width(t_root *root, char *file)
{
	root->game->width = 0;
	while (file[root->game->width] && file[root->game->width] != '\n')
		root->game->width++;
	if (root->game->width == 0 || file[root->game->width] == 0)
		root_destroy(root, "map file is invalid", 0);
}

void	map_height(t_root *root, char *file)
{
	int				i;
	int				j;
	
	root->game->height = 1;
	i = root->game->width + 1;
	while (file[i] != 0)
	{
		j = 0;
		while (file[i + j] != 0 && file[i + j] != '\n')
			j++;
		if (root->game->width != j)
			root_destroy(root, "map format is invalid", 0);
		i += root->game->width + 1;
		root->game->height++;
	}
}

void	map_isvalid(t_root *root, char *file)
{
	int				count_player;
	int				count_exit;
	int				i;

	count_player = 0;
	count_exit = 0;
	i = -1;
	while (file[++i] != 0)
	{
		if (file[i] == '\n')
			continue ;
		if (i < root->game->width ||
			i > (root->game->width + 1) * (root->game->height - 1) ||
			i % (root->game->width + 1) == 0 ||
			i % (root->game->width + 1) == root->game->width - 1)
		{
			if (file[i] != '1')
				root_destroy(root, "map isn't surrounded by walls", 0);
		}
		else
		{
			if (file[i] == 'P')
				count_player++;
			else if (file[i] == 'E')
				count_exit++;
			else if (file[i] == 'C')
				root->game->obj_count++;
			else if (file[i] == '1' || file[i] == '0')	
				continue ;
			else
				root_destroy(root, "map content is invalid", 0);
		}
	}
	if (count_player != 1 || count_exit != 1 || root->game->obj_count < 1)
		root_destroy(root, "map configuration is invalid", 0);
}

void	map_parsing(t_root *root, char *file)
{
	int				i;
	int				j;
	int				k;
	int				obj;

	root->game->obj_pos = (t_coord *)malloc(sizeof(t_coord) * root->game->obj_count);
	if (root->game->obj_pos == 0)
		root_destroy(root, "map_parsing(): malloc()", errno);
	root->game->map = (int **)malloc(sizeof(int *) * root->game->height);
	if (root->game->map == 0)
		root_destroy(root, "map_parsing(): malloc()", errno);
	obj = 0;
	k = 0;
	j = 0;
	while (j < root->game->height)
	{
		root->game->map[j] = (int *)malloc(sizeof(int) * root->game->width);
		if (root->game->map[j] == 0)
		{
			free_matrix(root->game->map, j);
			root->game->map = 0;
			root_destroy(root, "map_parsing(): malloc()", errno);
		}
		i = 0;
		while (i < root->game->width)
		{
			if (file[k] == 'P')
			{
				root->game->player_pos.x = k % (root->game->width + 1);
				root->game->player_pos.y = k / (root->game->width + 1);
				file[k] = '0';
			}
			if (file[k] == 'E')
			{
				root->game->exit_pos.x = k % (root->game->width + 1);
				root->game->exit_pos.y = k / (root->game->width + 1);
				file[k] = '0';
			}
			if (file[k] == 'C')
			{
				root->game->obj_pos[obj].x = k % (root->game->width + 1);
				root->game->obj_pos[obj].y = k / (root->game->width + 1);
				obj++;
				file[k] = '0';
			}
			root->game->map[j][i++] = file[k++] - 48;
		}
		k++;
		j++;
	}
}

void	map_read(t_root *root, char *file)
{
	map_width(root, file);
	map_height(root, file);
	map_isvalid(root, file);
	map_parsing(root, file);
}

void	map_init(t_root *root, char *filename)
{
	int				fd;
	char			*file;
	char			buf[1024 + 1];
	int				ret;
	char			*tmp;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		root_destroy(root, filename, errno);
	file = ft_calloc(1, 1);
	if (file == 0)
	{
		close(fd);
		root_destroy(root, "map_init(): ft_calloc()", errno);
	}
	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buf, 1024);
		if (ret == -1)
		{
			free(file);
			close(fd);
			root_destroy(root, "map_init(): read()", errno);
		}
		else
		{
			buf[ret] = 0;
			tmp = ft_strjoin(file, buf);
			free(file);
			file = tmp;
			if (file == 0)
			{
				close(fd);
				root_destroy(root, "map_init(): ft_strjoin()", errno);
			}
		}
	}
	close(fd);
	map_read(root, file);
	free(file);
}

void	game_init(t_root *root, char *filename)
{
	root->game = (t_game *)malloc(sizeof(t_game));
	if (root->game == 0)
		root_destroy(root, "game_init(): malloc()", errno);
	root->game->map = 0;
	root->game->obj_pos = 0;
	root->game->obj_count = 0;
	map_init(root, filename);
}

t_root	*root_init(char *filename)
{
	t_root			*root;

	root = (t_root *)malloc(sizeof(t_root));
	if (root == 0)
		root_destroy(0, "root_init(): malloc()", errno);
	root->game = 0;
	root->mlx = 0;
	root->mlx_win = 0;
	root->mlx_img = 0;
	game_init(root, filename);
	root->mlx = mlx_init();
	if (root->mlx == 0)
		root_destroy(root, "mlx_init(): can't load mlx", 0);
	root->mlx_win = mlx_new_window(root->mlx, 1920, 1080, "Hello world!");
	if (root->mlx_win == 0)
		root_destroy(root, "mlx_new_window(): can't create a window", 0);
	root->mlx_img = mlx_new_image(root->mlx, 1920, 1080);
	if (root->mlx_img == 0)
		root_destroy(root, "mlx_new_image(): can't create an image", 0);
	return (root);
}



int    key_hook(int keycode, t_root *root)
{
	if (keycode == 65307)
	{
		ft_putstr_fd("Thanks for playing!\nhttps://github.com/gmarcha\n", 1);
		root_destroy(root, 0, 0);
	}
	return (0);
}

int    main(int ac, char *av[])
{
	t_root          *root;

	if (ac != 2)
		die("invalid number arguments", 0);
	root = root_init(av[1]);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->mlx_img, 0, 0);
	mlx_hook(root->mlx_win, 2, (1L << 0), &key_hook, root);
	mlx_loop(root->mlx);
	return (0);
}
