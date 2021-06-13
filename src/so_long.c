/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:36:29 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/13 02:21:50 by gamarcha         ###   ########.fr       */
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
		if (game->coll != 0)
			free(game->coll);
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
		if (root->ground != 0)
			mlx_destroy_image(root->mlx, root->ground);
		if (root->wall != 0)
			mlx_destroy_image(root->mlx, root->wall);
		if (root->coll != 0)
			mlx_destroy_image(root->mlx, root->coll);
		if (root->exit != 0)
			mlx_destroy_image(root->mlx, root->exit);
		if (root->player != 0)
			mlx_destroy_image(root->mlx, root->player);
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

void	map_width(t_root *root, char *file)
{
	root->game->width = 0;
	while (file[root->game->width] && file[root->game->width] != '\n')
		root->game->width++;
	if (root->game->width == 0 || file[root->game->width] == 0)
	{
		free(file);
		root_destroy(root, "map file is invalid", 0);
	}
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
		{
			free(file);
			root_destroy(root, "map format is invalid", 0);
		}
		i += root->game->width + 1;
		root->game->height++;
	}
}

static int	isborder(t_root *root, int i)
{
	if (i < root->game->width ||
		i > (root->game->width + 1) * (root->game->height - 1) ||
		i % (root->game->width + 1) == 0 ||
		i % (root->game->width + 1) == root->game->width - 1)
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
	if (root->game->count_player != 1 ||
		root->game->count_exit != 1 ||
		root->game->count_coll < 1)
	{
		free(file);
		root_destroy(root, "map configuration is invalid", 0);
	}
}

static void	get_coord(t_root *root, char *file, int k, int *obj)
{
	if (file[k] == 'P')
	{
		root->game->player.x = k % (root->game->width + 1);
		root->game->player.y = k / (root->game->width + 1);
		file[k] = '0';
	}
	else if (file[k] == 'E')
	{
		root->game->exit.x = k % (root->game->width + 1);
		root->game->exit.y = k / (root->game->width + 1);
		file[k] = '0';
	}
	else if (file[k] == 'C')
	{
		root->game->coll[*obj].x = k % (root->game->width + 1);
		root->game->coll[*obj].y = k / (root->game->width + 1);
		file[k] = '0';
		(*obj)++;
	}
}

void	map_parsing(t_root *root, char *file)
{
	int				i;
	int				j;
	int				k;
	int				obj;

	obj = 0;
	k = 0;
	j = -1;
	while (++j < root->game->height)
	{
		root->game->map[j] = (int *)malloc(sizeof(int) * root->game->width);
		if (root->game->map[j] == 0)
		{
			free_matrix(root->game->map, j);
			root->game->map = 0;
			free(file);
			root_destroy(root, "map_parsing(): malloc()", errno);
		}
		i = 0;
		while (i < root->game->width)
		{
			get_coord(root, file, k, &obj);
			root->game->map[j][i++] = file[k++] - 48;
		}
		k++;
	}
}

void	map_read(t_root *root, char *file)
{
	map_width(root, file);
	map_height(root, file);
	map_isvalid(root, file);
	root->game->coll =
		(t_coord *)malloc(sizeof(t_coord) * root->game->count_coll);
	if (root->game->coll == 0)
	{
		free(file);
		root_destroy(root, "map_parsing(): malloc()", errno);
	}
	root->game->map = (int **)malloc(sizeof(int *) * root->game->height);
	if (root->game->map == 0)
	{
		free(file);
		root_destroy(root, "map_parsing(): malloc()", errno);
	}
	ft_putendl_fd(file, 1);
	map_parsing(root, file);
}

static void	file_parse(t_root *root, char **file, char buf[], int fd)
{
	char			*tmp;

	tmp = ft_strjoin(*file, buf);
	free(*file);
	*file = tmp;
	if (*file == 0)
	{
		close(fd);
		root_destroy(root, "map_init(): ft_strjoin()", errno);
	}
}

static void	file_read(t_root *root, char **file, char buf[], int fd)
{
	int				ret;

	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buf, 1024);
		if (ret == -1)
		{
			free(*file);
			close(fd);
			root_destroy(root, "map_init(): read()", errno);
		}
		else
		{
			buf[ret] = 0;
			file_parse(root, file, buf, fd);
		}
	}
}

static char	*file_init(t_root *root, int fd)
{
	char			*file;

	file = ft_calloc(1, 1);
	if (file == 0)
	{
		close(fd);
		root_destroy(root, "map_init(): ft_calloc()", errno);
	}
	return (file);
}

void	map_init(t_root *root, char *filename)
{
	int				fd;
	char			*file;
	char			buf[1024 + 1];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		root_destroy(root, filename, errno);
	file = file_init(root, fd);
	file_read(root, &file, buf, fd);
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
	root->game->coll = 0;
	root->game->count_coll = 0;
	root->game->count_exit = 0;
	root->game->count_player = 0;
	root->game->player_move = 0;
	root->game->player_coll = 0;
	root->game->player_up = 0;
	root->game->player_down = 0;
	root->game->player_left = 0;
	root->game->player_right = 0;
	map_init(root, filename);
}

void	texture_load(t_root *root, t_img **img, char *path)
{
	int				width;
	int				height;

	*img = mlx_xpm_file_to_image(root->mlx, path, &width, &height);
	if (*img == 0)
		root_destroy(0, "texture_init(): can't load texture", 0);
	(*img)->width = width;
	(*img)->height = height;
}

void	texture_init(t_root *root)
{
	texture_load(root, &root->player, "./img/player.xpm");
	texture_load(root, &root->exit, "./img/moto.xpm");
	texture_load(root, &root->coll, "./img/gas.xpm");
	texture_load(root, &root->wall, "./img/wall.xpm");
	texture_load(root, &root->ground, "./img/sand.xpm");
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
	root->player = 0;
	root->exit = 0;
	root->coll = 0;
	root->wall = 0;
	root->ground = 0;
	game_init(root, filename);
	root->mlx = mlx_init();
	if (root->mlx == 0)
		root_destroy(root, "mlx_init(): can't load mlx", 0);
	root->mlx_win = mlx_new_window(root->mlx, root->game->width * 40, root->game->height * 40, "so_long");
	if (root->mlx_win == 0)
		root_destroy(root, "mlx_new_window(): can't create a window", 0);
	root->mlx_img = mlx_new_image(root->mlx, root->game->width * 40, root->game->height * 40);
	if (root->mlx_img == 0)
		root_destroy(root, "mlx_new_image(): can't create an image", 0);
	texture_init(root);
	return (root);
}

void	draw_square(t_root *root, t_img *img, int x, int y)
{
	unsigned int	color;
	int				i;
	int				j;

	j = 0;
	while (j < 40)
	{
		i = 0;
		while (i < 40)
		{
			color = mlx_get_pixel(img, i, j);
			if (color != mlx_rgb_to_int(0, 255, 255, 255))
				mlx_draw_pixel(root->mlx_img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_env(t_root *root, int i, int j)
{
	int				k;

	if (root->game->exit.x == i && root->game->exit.y == j)
		draw_square(root, root->exit, i * 40, j * 40);
	k = -1;
	while (++k < root->game->count_coll)
		if (root->game->coll[k].x == i && root->game->coll[k].y == j)
			draw_square(root, root->coll, i * 40, j * 40);
	if (root->game->player.x == i && root->game->player.y == j)
		draw_square(root, root->player, i * 40, j * 40);
}

void	draw_map(t_root *root)
{
	int				i;
	int				j;

	j = 0;
	while (j < root->game->height)
	{
		i = 0;
		while (i < root->game->width)
		{
			if (root->game->map[j][i] == 1)
				draw_square(root, root->wall, i * 40, j * 40);
			else
				draw_square(root, root->ground, i * 40, j * 40);
			draw_env(root, i, j);
			i++;
		}
		j++;
	}
}

void	draw(t_root *root)
{
	draw_map(root);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->mlx_img, 0, 0);
}

void	update(t_root *root)
{
	int				x;
	int				y;

	x = root->game->player.x;
	y = root->game->player.y;
	if (root->game->player_up != 0)
	{
		if (root->game->map[y - 1][x] == 0)
			root->game->player.y -= 1;
	}
	else if (root->game->player_down != 0)
	{
		if (root->game->map[y + 1][x] == 0)
			root->game->player.y += 1;
	}
	else if (root->game->player_left != 0)
	{
		if (root->game->map[y][x - 1] == 0)
			root->game->player.x -= 1;
	}
	else if (root->game->player_right != 0)
		if (root->game->map[y][x + 1] == 0)
			root->game->player.x += 1;
	draw(root);
}

int	key_press(int keycode, t_root *root)
{
	if (keycode == 65307)
	{
		ft_putstr_fd("Thanks for playing!\nhttps://github.com/gmarcha\n", 1);
		root_destroy(root, 0, 0);
	}
	if (keycode == 119)
		root->game->player_up = 1;
	if (keycode == 115)
		root->game->player_down = 1;
	if (keycode == 97)
		root->game->player_left = 1;
	if (keycode == 100)
		root->game->player_right = 1;
	update(root);
	return (0);
}

int	key_release(int keycode, t_root *root)
{
	if (keycode == 119)
		root->game->player_up = 0;
	if (keycode == 115)
		root->game->player_down = 0;
	if (keycode == 97)
		root->game->player_left = 0;
	if (keycode == 100)
		root->game->player_right = 0;
	update(root);
	return (0);
}

int	destroy_hook(int keycode, t_root *root)
{
	(void)keycode;
	(void)root;
	ft_putstr_fd("Thanks for playing!\nhttps://github.com/gmarcha\n", 1);
	root_destroy(0, 0, 0);
	return (0);
}

int    main(int ac, char *av[])
{
	t_root          *root;

	if (ac != 2)
		die("invalid number of arguments", 0);
	root = root_init(av[1]);
	draw(root);
	mlx_hook(root->mlx_win, 2, 1L << 0, key_press, root);
	mlx_hook(root->mlx_win, 3, 1L << 1, key_release, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, destroy_hook, root);
	mlx_loop(root->mlx);
	return (0);
}
