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
		if (game->map != 0)
		{
			i = 0;
			while (i < game->height)
				free(game->map[i++]);
			free(game->map);
		}
		if (game->obj_pos != 0)
			free(game->obj_pos);
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

void	map_parsing(t_root *root, char *file)
{
	(void)root;
	ft_putendl_fd(file, 1);	
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
	map_parsing(root, file);
	free(file);
}

void	game_init(t_root *root, char *filename)
{
	root->game = (t_game *)malloc(sizeof(t_game));
	if (root->game == 0)
		root_destroy(root, "game_init(): malloc()", errno);
	root->game->map = 0;
	root->game->obj_pos = 0;
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
