/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:08 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 14:48:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_env *env, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= env->winw || r < 0 || r >= env->winh)
		return ;
	dst = env->img[CANVAS].addr + (r * env->img[CANVAS].llen + c * (env->img[CANVAS].bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_get_texpixel(t_env *env, int texX, int texY)
{
	t_img	tex;
	int		color;
	int		wall;

	if (env->ray.side == 1)
	{
		wall = NORTH;
		if (env->py <= env->ray.mapY)
			wall = SOUTH;
	}
	else
	{
		wall = EAST;
		if (env->px <= env->ray.mapX)
			wall = WEST;
	}
	tex = env->img[wall];
	if (texX < 0 || texX >= tex.imgw || texY < 0 || texY >= tex.imgh)
		return (0);
	color = *(unsigned int *)(tex.addr + (texY * tex.llen + texX * (tex.bpp / 8)));
	return (color);
}

int	ft_get_texx(t_env *env)
{
	double wallX;

	if(env->ray.side == 0)
		wallX = env->py + env->ray.perpWallDist * env->ray.raydir.y;
	else
	  	wallX = env->px + env->ray.perpWallDist * env->ray.raydir.x;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(env->img[NORTH].imgw));
	if(env->ray.side == 0 && env->ray.raydir.x > 0)
		texX = TEXH - texX - 1;
	if(env->ray.side == 1 && env->ray.raydir.y < 0)
		texX = env->img[NORTH].imgw - texX - 1;
	return (texX);	
}
