/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 15:43:16 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_cub3d *cub, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= cub->cst.width || r < 0 || r >= cub->cst.height)
		return ;
	dst = cub->img.addr + (r * cub->img.line_len + c * (cub->img.bpp / 8));
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

static int	ft_get_color(t_cub3d *c, int x, int y, int side)
{
	t_img	tex;
	int		color;
  int   wall;
  
  if (side == 1)
    wall = ft_get_ns_wall(c->data.px, c->data.py, x, y);
  else
    wall = ft_get_ew_wall(c->data.px, c->data.py, x, y);
  if (wall == NORTH)
    color = 0x00FF0000; //red
  else if (wall == SOUTH)
    color = 0x0000FF00; //green
  else if (wall == EAST)
    color = 0x000000FF; //blue
  else if (wall == WEST)
    color = 0x00FFFF00; //yellow
	return (color);
}

// static int	ft_get_color(t_cub3d *c, int x, int y)
// {
// 	t_img	tex;
// 	int		color;
//   int   wall;
  
// 	tex = c->buf;
// 	if (x < 0 || x >= tex.w || y < 0 || y >= tex.h)
// 		return (0);
// 	color = *(unsigned int *)(tex.addr + (y * tex.line_len + x * (tex.bpp / 8)));
//   return (color);
// }

void	ft_draw(t_cub3d *cub, int col)
{
	//calculate ray position and direction
	double cameraX = 2 * col / (double)cub->cst.width - 1; //x-coordinate in camera space
	double rayDirX = cub->cst.dirX + (cub->cst.planeX)*cameraX;
	double rayDirY = cub->cst.dirY + (cub->cst.planeY)*cameraX;

	//which box of the map we're in
	int mapX = (int)(cub->data.px);
	int mapY = (int)(cub->data.py);

	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;

	//length of ray from one x or y-side to next x or y-side
	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	double perpWallDist;

	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	//calculate step and initial sideDist
	if(rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (cub->data.px - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - cub->data.px) * deltaDistX;
	}
	if(rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (cub->data.py - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - cub->data.py) * deltaDistY;
	}
	//perform DDA
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		// Check if ray has hit a wall
		if(cub->data.map[mapX][mapY] > '0') hit = 1;
	}

	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
	else          perpWallDist = (sideDistY - deltaDistY);

	//Calculate height of line to draw on screen
	int lineHeight = (int)(cub->cst.height / perpWallDist);


	int pitch = 100;

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + (cub->cst.height) / 2 + pitch;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + (cub->cst.height) / 2 + pitch;
	if(drawEnd >= (cub->cst.height)) drawEnd = (cub->cst.height) - 1;

	//texturing calculations
	int texNum = cub->data.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = cub->data.py + perpWallDist * rayDirY;
      else          wallX = cub->data.px + perpWallDist * rayDirX;
      wallX -= floor((wallX));
      printf("wallX = %f\n", wallX);
      //x coordinate on the texture
      int texX = (int)(wallX * (double)(cub->buf.w));
      if(side == 0 && rayDirX > 0) texX = cub->buf.w - texX - 1;
      if(side == 1 && rayDirY < 0) texX = cub->buf.w - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * cub->buf.h / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - pitch - (cub->cst.height) / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (cub->buf.h - 1) in case of overflow
        int texY = (int)texPos & (cub->buf.h - 1);
        texPos += step;
        // Uint32 color = texture[texNum][cub->buf.h * texY + texX];
        // int color = ft_get_color(cub, texX, texY);
        int color = ft_get_color(cub, mapX, mapY, side);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(side == 1) color = (color >> 1) & 8355711;
		// buffer[y][x] = color;
		ft_pixel_put(cub, col, y, color);
	}
}
