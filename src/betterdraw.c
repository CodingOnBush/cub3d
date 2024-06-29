/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   betterdraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:19:23 by momrane           #+#    #+#             */
/*   Updated: 2024/06/29 10:42:14 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_vec	ft_get_deltadist(t_env *env)
{
	t_vec	deltadist;

	deltadist.x = 1e30;
	deltadist.y = 1e30;
	if (env->ray.rayDirX != 0)
		deltadist.x = fabs(1 / env->ray.rayDirX);
	if (env->ray.rayDirY != 0)
		deltadist.y = fabs(1 / env->ray.rayDirY);
	return (deltadist);
}

static t_vec	ft_get_sidedist(t_env *env, t_vec deltadist)
{
	t_vec	sidedist;

	if(env->ray.rayDirX < 0)
		sidedist.x = (env->px - env->ray.mapY) * deltadist.y;
	else
		sidedist.x = (env->ray.mapY + 1.0 - env->py) * deltadist.y;
	if(env->ray.rayDirY < 0)
		sidedist.y = (env->py - env->ray.mapY) * deltadist.y;
	else
		sidedist.y = (env->ray.mapY + 1.0 - env->py) * deltadist.y;
	if (sidedist.y == 0)
		sidedist.y = 0.1;
	if (sidedist.x == 0)
		sidedist.x = 0.1;
	return (sidedist);
}

static void	ft_find_hit_point(t_env *env, t_vec sidedist, t_vec deltadist, int stepX, int stepY)
{
	while (1)
	{
		if(sidedist.x < sidedist.y)
		{
			sidedist.x += env->ray.deltadist.x;
			env->ray.mapX += stepX;
			env->ray.side = 0;
		}
		else
		{
			sidedist.y += env->ray.deltadist.y;
			env->ray.mapY += stepY;
			env->ray.side = 1;
		}
		if (env->ray.mapX < 0 || env->ray.mapY < 0)
			return;
		if (env->ray.mapX >= env->mapw || env->ray.mapY >= env->maph)
			return;
		if(env->map[env->ray.mapX][env->ray.mapY] > '0')
			return;
	}
}

static int	ft_get_line_height(t_env *env)
{
	t_vec const	deltadist = ft_get_deltadist(env);
	t_vec const	sidedist = ft_get_sidedist(env, deltadist);
	int			stepX;
	int			stepY;
	int			perpWallDist;

	stepX = 1;
	stepY = 1;
	if (env->ray.rayDirX < 0)
		stepX = -1;
	if (env->ray.rayDirY < 0)
		stepY = -1;
	ft_find_hit_point(env, sidedist, env->ray.deltadist, stepX, stepY);
	if(env->ray.side == 0)
		perpWallDist = (sidedist.x - env->ray.deltadist.x);
	else
		perpWallDist = (sidedist.y - env->ray.deltadist.y);
	return ((int)(env->winh / env->ray.perpWallDist));
}

static void	ft_set_raydir(t_env *env, int col)
{
	double cameraX = 2 * (col) / (double)env->winw - 1;//x-coordinate in camera space

	env->ray.raydir.x = env->ray.dir.x + env->ray.plane.x * cameraX;
	env->ray.raydir.y = env->ray.dir.y + env->ray.plane.y * cameraX;
}

void	ft_draw_stripe(t_env *env, int col)
{
	int		lineHeight;


	int	y;
	int	color;

	env->ray.mapX = (int)env->px;
	env->ray.mapY = (int)env->py;
	ft_set_raydir(env, col);
	
	//length of ray from current position to next x or y-side
	// double	sideDistX;
	// double	sideDistY;
	
	//length of ray from one x or y-side to next x or y-side
	// double	env->ray.deltadist.x = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	// double	env->ray.deltadist.y = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);



	lineHeight = ft_get_line_height(env);
	
	int pitch = 100;
	int drawStart = -lineHeight / 2 + (env->winh) / 2 + pitch;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + (env->winh) / 2 + pitch;
	if(drawEnd >= (env->winh)) drawEnd = (env->winh) - 1;
	double wallX; //where exactly the wall was hit
	if(side == 0)
		wallX = env->py + perpWallDist * rayDirY;
	else
	  	wallX = env->px + perpWallDist * rayDirX;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(env->img[NORTH].imgw));
	if(side == 0 && rayDirX > 0)
		texX = env->img[NORTH].imgh - texX - 1;
	if(side == 1 && rayDirY < 0)
		texX = env->img[NORTH].imgw - texX - 1;
	double step = 1.0 * env->img[NORTH].imgh / lineHeight;
	double texPos = (drawStart - pitch - (env->winh) / 2 + lineHeight / 2) * step;
	y = 0;
	if (drawStart > env->winh || drawEnd < 0)
		return ;
	while (y < drawStart)
	{
		color = (env->file.colors[0][R] << 16 | env->file.colors[0][G] << 8 | env->file.colors[0][B]);
		ft_pixel_put(env, col, y, color);
		y++;
	}
	while (y < drawEnd)
	{
		int texY = (int)texPos & (env->img[NORTH].imgh - 1);
		texPos += step;
		int wall;
		if (side == 1)
			wall = ft_get_ew_wall(env->px, env->py, mapX, mapY);
		else
			wall = ft_get_ns_wall(env->px, env->py, mapX, mapY);

		int color = ft_get_color2(env, texX, texY, wall);
		if(side == 1) color = (color >> 1) & 8355711;
		ft_pixel_put(env, col, y, color);
		y++;
	}
	while (y < env->winh)
	{
		color = (env->file.colors[1][R] << 16 | env->file.colors[1][G] << 8 | env->file.colors[1][B]);
		ft_pixel_put(env, col, y, color);
		y++;
	}
}
