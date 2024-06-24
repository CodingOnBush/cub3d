/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 13:58:54 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_env *env, int c, int r, int color)
{
	char	*dst;

	// if (c < 0 || c >= env->cst.width || r < 0 || r >= env->win.winh)
	// 	return ;
	dst = env->win.img[0].addr + (r * env->win.img[0].llen + c * (env->win.img[0].bpp / 8));
	*(unsigned int *)dst = color;
}

static int ft_get_ns_wall(int px, int py, int x, int y){
  if (py <= y)
    return (SOUTH);
  else
    return (NORTH);
}

static int ft_get_ew_wall(int px, int py, int x, int y){
  if (px <= x)
    return (EAST);
  else
    return (WEST);
  
}

static int	ft_get_color_tex(t_env *c, int x, int y, int type)
{
	t_img	tex;
	int		color;

	tex = c->win.img[type];
	if (x < 0 || x >= tex.imgw || y < 0 || y >= tex.imgh)
		return (0);
	color = *(unsigned int *)(tex.addr + (y * tex.llen + x * (tex.bpp / 8)));
	return (color);
}

static int	ft_get_color(t_env *c, int texX, int texY, int wall)
{
	t_img	tex;
	int		color;
  
	color = ft_get_color_tex(c, texX, texY, wall);
	return (color);
}

t_ray	ft_init_ray(t_env *env, int col)
{
	t_ray	ray;

	ray.cameraX = 2 * col / (double)env->win.winw - 1; //x-coordinate in camera space
	ray.rayDirX = env->ray.dirX + (env->ray.planeX)*(ray.cameraX);
	ray.rayDirY = env->ray.dirY + (env->ray.planeY)*(ray.cameraX);
	ray.mapX = (int)(env->px);
	ray.mapY = (int)(env->py);
	return (ray);
}

void	ft_draw(t_env *env, int col)
{
	int	y;
	int	color;

	env->ray = ft_init_ray(env, col);
	// //calculate ray position and direction
	// double cameraX = 2 * col / (double)env->cst.width - 1; //x-coordinate in camera space
	// double rayDirX = env->cst.dirX + (env->cst.planeX)*cameraX;
	// double rayDirY = env->cst.dirY + (env->cst.planeY)*cameraX;

	//which box of the map we're in
	// int mapX = (int)(env->px);
	// int mapY = (int)(env->py);

	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;

	//length of ray from one x or y-side to next x or y-side
	double deltaDistX = (env->ray.rayDirX == 0) ? 1e30 : fabs(1 / env->ray.rayDirX);
	double deltaDistY = (env->ray.rayDirY == 0) ? 1e30 : fabs(1 / env->ray.rayDirY);
	double perpWallDist;

	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	//calculate step and initial sideDist
	if(env->ray.rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (env->px - env->ray.mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (env->ray.mapX + 1.0 - env->px) * deltaDistX;
	}
	if(env->ray.rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (env->py - env->ray.mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (env->ray.mapY + 1.0 - env->py) * deltaDistY;
	}
	//perform DDA
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			env->ray.mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			env->ray.mapY += stepY;
			side = 1;
		}
		// Check if ray has hit a wall
		if(env->map[env->ray.mapX][env->ray.mapY] > '0') hit = 1;
	}

	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
	else          perpWallDist = (sideDistY - deltaDistY);

	//Calculate height of line to draw on screen
	int lineHeight = (int)(env->win.winh / perpWallDist);


	int pitch = 100;

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + (env->win.winh) / 2 + pitch;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + (env->win.winh) / 2 + pitch;
	if(drawEnd >= (env->win.winh)) drawEnd = (env->win.winh) - 1;

	//texturing calculations
	int texNum = env->map[env->ray.mapX][env->ray.mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = env->py + perpWallDist * env->ray.rayDirY;
      else          wallX = env->px + perpWallDist * env->ray.rayDirX;
      wallX -= floor((wallX));
    //   printf("wallX = %f\n", wallX);
	//x coordinate on the texture
	int texX = (int)(wallX * (double)(env->win.img[0].imgw));
	if(side == 0 && env->ray.rayDirX > 0) texX = env->win.img[0].imgw - texX - 1;
	if(side == 1 && env->ray.rayDirY < 0) texX = env->win.img[0].imgw - texX - 1;

	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * env->win.img[0].imgh / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - pitch - (env->win.winh) / 2 + lineHeight / 2) * step;
	y = 0;
	printf("drawStart = %d\n", drawStart);
	printf("drawEnd = %d\n", drawEnd);
	if (drawStart > env->win.winh || drawEnd < 0)
		return ;
	while (y < drawStart)
	{
		color = (env->file.colors[FLOOR][R] << 16 | env->file.colors[FLOOR][G] << 8 | env->file.colors[FLOOR][B]);
		ft_pixel_put(env, col, y, color);
		y++;
	}
	while (y < drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (env->win.img[0].imgh - 1) in case of overflow
		int texY = (int)texPos & (env->win.img[0].imgh - 1);
		texPos += step;
		// Uint32 color = texture[texNum][env->win.img[0].imgh * texY + texX];
		// int color = ft_get_color(env, texX, texY);

		int wall;

		if (side == 1)
			wall = ft_get_ns_wall(env->px, env->py, env->ray.mapX, env->ray.mapY);
		else
			wall = ft_get_ew_wall(env->px, env->py, env->ray.mapX, env->ray.mapY);

		int color = ft_get_color(env, texX, texY, wall);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(side == 1) color = (color >> 1) & 8355711;
		ft_pixel_put(env, col, y, color);
		y++;
	}
	while (y < env->win.winh)
	{
		ft_pixel_put(env, col, y, color);
		color = (env->file.colors[CEIL][R] << 16 | env->file.colors[CEIL][G] << 8 | env->file.colors[CEIL][B]);
		y++;
	}
}