/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:28:49 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 13:13:23 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_init_ray(t_ray *ray)
{
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
	ray->perpWallDist = 0;
	ray->planeX = 0;
	ray->planeY = 0;
	ray->dirX = 0;
	ray->dirY = 0;
	ray->ms = 0;
	ray->rs = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->texCol = 0;
}

static void	ft_init_img(t_img *img)
{
	img->path = NULL;
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->llen = 0;
	img->endian = 0;
	img->imgw = 64;
	img->imgh = 64;
}

static int	ft_init_win(t_win *win)
{
	int	i;

	win->winw = 640;
	win->winh = 640;
	win->mlx_ptr = NULL;
	win->win_ptr = NULL;
	i = 0;
	while (i < 5)
		ft_init_img(&win->img[i++]);
	return (SUCCESS);
}

static void	ft_init_file(t_file *file)
{
	int i;

	file->content = NULL;
	file->width = 0;
	file->height = 0;
	i = 0;
	while (i < 4)
		file->texpath[i++] = NULL;
	i = 0;
	while (i < 3)
	{
		file->rgbfloor[i] = 0;
		file->rgbsky[i] = 0;
		i++;
	}
	file->count = 0;
}

void	ft_init_env(t_env *env)
{
	ft_init_file(&env->file);
	env->map = NULL;
	env->mapw = 0;
	env->maph = 0;
	env->px = 0;
	env->py = 0;
	ft_init_ray(&env->ray);
	ft_init_win(&env->win);
}
