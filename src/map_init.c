/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 04:00:01 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/13 04:00:01 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
