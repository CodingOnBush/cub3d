/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:28:49 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 07:02:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_init_cst(t_cst *cst)
{
	cst->ms = 0.5;
	cst->rs = 0.1;
	cst->width = 1640;
	cst->height = 1640;
	cst->planeX = 0;
	cst->planeY = 0.66;
	cst->dirX = -1;
	cst->dirY = 0;
}

static void	ft_init_ray(t_ray *ray)
{
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
	ray->perpWallDist = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->side = 0;
	ray->hit = 0;
	ray->texCol = 0;
}

static void	ft_init_data(t_data *data)
{
	data->raw = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->f = NULL;
	data->c = NULL;
	data->i = 0;
	data->map = NULL;
	data->mapw = 0;
	data->maph = 0;
	data->px = 0;
	data->py = 0;
}

static int	ft_init_mlx(t_mlx *mlx, int width, int height)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->mlx_ptr = mlx_init();
	if (!(mlx->mlx_ptr))
		return (printf("Error : mlx_init() failed\n"), FAILURE);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, "?");
	if (!(mlx->win_ptr))
	{
		printf("Error : mlx_new_window() failed\n");
		free(mlx->mlx_ptr);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	ft_init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->line_len = 0;
	img->bpp = 0;
	img->endian = 0;
	img->w = 0;
	img->h = 0;
	img->type = -1;
}

static void	ft_init_buffers(t_cub3d *cub)
{
	for (int i = 0; i < 4; i++)
	{
		ft_init_img(&cub->buf[i]);
	}
}

int	ft_init_cub3d(t_cub3d *cub)
{
	ft_init_cst(&cub->cst);
	ft_init_img(&cub->img);
	ft_init_buffers(cub);
	ft_init_ray(&cub->ray);
	ft_init_data(&cub->data);
	if (ft_init_mlx(&cub->mlx, cub->cst.width, cub->cst.height) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
