/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:28:38 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 10:01:59 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	ft_init_map_sizes(t_env *env)
{
	char	*line;
	int		fd;

	if (env->filename == NULL)
		return (-1);
	fd = open(env->filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = ft_gnl(fd);
	if (!line)
		return (-1);
	env->cols = ft_count_cols(line);
	while (line)
	{
		env->rows++;
		free(line);
		line = ft_gnl(fd);
	}
	close(fd);
	return (1);
}

static void	ft_init_img_values(t_env *env)
{
	env->img.img_ptr = NULL;
	env->img.img_data = NULL;
	env->img.bpp = 0;
	env->img.endian = 0;
	env->img.size_line = 0;
}

void	ft_init_env_values(t_env *env, char *filename)
{
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	env->filename = filename;
	env->width = 1600;
	env->height = 900;
	env->angle = 41.4;
	env->altitude = 1.2;
	env->zoom = 2;
	env->rows = 0;
	env->cols = 0;
	env->r = 0;
	env->c = 0;
	env->origin.x = env->width / 2;
	env->origin.y = env->height / 2;
	env->origin.z = 0;
	ft_init_img_values(env);
	env->mat = NULL;
	env->map = NULL;
}

int	ft_init_env(t_env *env, char *f)
{
	ft_init_env_values(env, f);
	if (ft_init_map_sizes(env) < 0)
		return (-1);
	env->mlx_ptr = mlx_init();
	if (!env->mlx_ptr)
		return (-1);
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->width, env->height, f);
	if (!env->win_ptr)
		return (-1);
	env->mat = ft_new_matrix(env->rows, env->cols);
	if (!env->mat)
		return (-1);
	env->map = ft_new_matrix(env->rows, env->cols);
	if (!env->map)
		return (-1);
	ft_init_img(env);
	return (1);
}
