/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 10:02:01 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_cub3d *cub, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= cub->cst.width || r < 0 || r >= cub->cst.height)
	{
		// printf("nop");
		return ;
	}
	dst = cub->img.addr + (r * cub->img.line_len + c * (cub->img.bpp / 8));
	*(unsigned int *)dst = color;
}

// static int	ft_get_pixel(t_cub3d *c, int row, int lineHeight)
// {
// 	t_img	tex;
// 	int		color;

// 	tex = c->buf;
// 	color = *(unsigned int *)(tex.addr + (row * tex.line_len + c->ray.texCol * (tex.bpp / 8)));
// 	c->ray.texCol = (c->ray.texCol + 1) % tex.w;
// 	return (color);
// }

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

void	ft_draw_column(t_cub3d *c, int col, double perpWallDist)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		row;
	double	ratio;
	int		color;

	lineHeight = (int)(c->cst.height / perpWallDist);
	drawStart = (-lineHeight / 2) + (c->cst.height / 2);
	drawEnd = lineHeight / 2 + c->cst.height / 2;
	if(drawStart < 0)
		drawStart = 0;
	if(drawEnd >= c->cst.height)
		drawEnd = c->cst.height - 1;


	
	
	
	row = 0;
	while (row < drawStart)
	{
		ft_pixel_put(c, col, row, 0xFFFFFF);
		row++;
	}
	ratio = (drawEnd - drawStart) / c->buf.h;
	if (ratio <= 0)
		ratio = 1;
	while (row < drawEnd)
	{
		color = ft_get_color(c, c->ray.texCol, (int)(row / ratio) % c->buf.h);
		ft_pixel_put(c, col, row, color);
		row++;
	}
	c->ray.texCol = (c->ray.texCol + 1) % c->buf.w;
	while (row < c->cst.height)
	{
		ft_pixel_put(c, col, row, 0xFFFFFF);
		row++;
	}
}

void	ft_draw_texture(t_cub3d *c, t_img tex, int zoom)
{
	char	*tmp;
	int tex_col;
	int tex_row;

	tex_col = 0;
	while (tex_col < tex.w)
	{
		tex_row = 0;
		while (tex_row < tex.h)
		{
			tmp = tex.addr + (tex_row * tex.line_len + tex_col * (tex.bpp / 8));
			for (int win_col = 0; win_col < zoom; win_col++)
			{
				for (int win_row = 0; win_row < zoom; win_row++)
				{
					ft_pixel_put(c, (tex_col * zoom) + win_col, (tex_row * zoom) + win_row, *(unsigned int *)tmp);
				}	
			}
			tex_row++;
		}
		tex_col++;
	}
}


void	ft_draw(t_cub3d *cub, int col)
{
	//calculate ray position and direction
      double cameraX = 2 * col / (double)cub->cst.width - 1; //x-coordinate in camera space
      double rayDirX = cub->cst.dirX + (cub->cst.planeX)*cameraX;
      double rayDirY = cub->cst.dirY + (cub->cst.planeY)*cameraX;

      //which box of the map we're in
      int mapX = (int)(cub->sim.px);
      int mapY = (int)(cub->sim.py);

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
        sideDistX = (cub->sim.px - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - cub->sim.px) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (cub->sim.py - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - cub->sim.py) * deltaDistY;
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
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
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
      int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = cub->sim.py + perpWallDist * rayDirY;
      else          wallX = cub->sim.px + perpWallDist * rayDirX;
      wallX -= floor((wallX));

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
        int color = ft_get_color(cub, texX, texY);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        // buffer[y][x] = color;
		ft_pixel_put(cub, col, y, color);
      }
}
