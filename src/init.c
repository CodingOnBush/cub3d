/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:28:49 by momrane           #+#    #+#             */
/*   Updated: 2024/06/18 17:24:22 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_cst(t_cst *cst)
{
	cst->ms = 0.5;
	cst->rs = 0.5;
	cst->width = 640;
	cst->height = 640;
	cst->planeX = 0;
	cst->planeY = 0.66;
	cst->dirX = -1;
	cst->dirY = 0;
}

void	ft_init_ray(t_ray *ray)
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

void	ft_init_sim(t_sim *sim)
{
	sim->map = NULL;
	sim->mapw = 0;
	sim->maph = 0;
	sim->px = 0;
	sim->py = 0;
}
