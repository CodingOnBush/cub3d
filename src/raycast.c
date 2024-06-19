/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:05:18 by momrane           #+#    #+#             */
/*   Updated: 2024/06/19 11:13:16 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_init_vars(t_cub3d *c, int col)
{
	c->ray.cameraX = ((2 * col) / (double)c->cst.width) - 1;
	c->ray.rayDirX = c->cst.dirX + c->cst.planeX * c->ray.cameraX;
	c->ray.rayDirY = c->cst.dirY + c->cst.planeY * c->ray.cameraX;
	c->ray.mapX = (int)c->sim.px;
	c->ray.mapY = (int)c->sim.py;
	c->ray.hit = 0;
	c->ray.deltaDistX = 1e30;
	c->ray.deltaDistY = 1e30;
	c->ray.stepX = 1;
	c->ray.stepY = 1;
	if (c->ray.rayDirX != 0)
		c->ray.deltaDistX = fabs(1 / c->ray.rayDirX);
	if (c->ray.rayDirY != 0)
		c->ray.deltaDistY = fabs(1 / c->ray.rayDirY);
	if(c->ray.rayDirX < 0)
		c->ray.stepX = -1;
	if(c->ray.rayDirY < 0)
		c->ray.stepY = -1;
	c->ray.sideDistX = (c->ray.mapX + 1.0 - c->sim.px) * c->ray.deltaDistX;
	if(c->ray.rayDirX < 0)
		c->ray.sideDistX = (c->sim.px - c->ray.mapX) * c->ray.deltaDistX;
	c->ray.sideDistY = (c->ray.mapY + 1.0 - c->sim.py) * c->ray.deltaDistY;
	if(c->ray.rayDirY < 0)
		c->ray.sideDistY = (c->sim.py - c->ray.mapY) * c->ray.deltaDistY;
}

static int	ft_get_color(t_cub3d *c, int x, int y)
{
	t_img	tex;
	int		color;

	tex = c->buf;
	if (x < 0 || x >= tex.w || y < 0 || y >= tex.h)
		return (0);
	color = *(unsigned int *)(tex.addr + (y * tex.line_len + x * (tex.bpp / 8)));
	return (color);
}

double	ft_get_perp_wall_dist(t_cub3d *c, int col)
{
	ft_init_vars(c, col);
	while(c->ray.hit == 0)
	{
		if(c->ray.sideDistX < c->ray.sideDistY)
		{
			c->ray.sideDistX += c->ray.deltaDistX;
			c->ray.mapX += c->ray.stepX;
			c->ray.side = 0;
		}
		else
		{
			c->ray.sideDistY += c->ray.deltaDistY;
			c->ray.mapY += c->ray.stepY;
			c->ray.side = 1;
		}
		if(worldMap[c->ray.mapX][c->ray.mapY] > 0)
			c->ray.hit = 1;
	}
	c->ray.perpWallDist = (c->ray.sideDistY - c->ray.deltaDistY);
	if(c->ray.side == 0)
		c->ray.perpWallDist = (c->ray.sideDistX - c->ray.deltaDistX);

	int lineHeight = (int)(c->cst.height / c->ray.perpWallDist);
	int pitch = 100;

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + c->cst.height / 2 + pitch;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + c->cst.height / 2 + pitch;
	if(drawEnd >= c->cst.height) drawEnd = c->cst.height - 1;

	int texNum = worldMap[c->ray.mapX][c->ray.mapY] - 1; //1 subtracted from it so that texture 0 can be used!
	
	
	double wallX;
	if(c->ray.side == 0)
		wallX = c->sim.py + c->ray.perpWallDist * c->ray.rayDirY;
	else
		wallX = c->sim.px + c->ray.perpWallDist * c->ray.rayDirX;
	wallX -= floor(wallX);
	
	int texX = (int)(wallX * (double)c->buf.w);
	if(c->ray.side == 0 && c->ray.rayDirX > 0) texX = c->buf.w - texX - 1;
	if(c->ray.side == 1 && c->ray.rayDirY < 0) texX = c->buf.w - texX - 1;

	double step = 1.0 * c->buf.h / lineHeight;

	double texPos = (drawStart - pitch - c->cst.height / 2 + lineHeight / 2) * step;
	for(int y = 0; y < drawStart; y++)
	{
		ft_pixel_put(c, col, y, 0x000000);
	}
	for(int y = drawStart; y < drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (c->buf.h - 1);
		texPos += step;
		// Uint32 color = texture[texNum][texHeight * texY + texX];
		int color = ft_get_color(c, texX, texY);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(c->ray.side == 1)
			color = (color >> 1) & 8355711;
		// buffer[y][x] = color;
		ft_pixel_put(c, col, y, color);
	}
	for(int y = drawEnd; y < c->cst.height; y++)
	{
		ft_pixel_put(c, col, y, 0xA27AB7);
	}
    
	return (c->ray.perpWallDist);
}
