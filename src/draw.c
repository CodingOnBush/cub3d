/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 23:31:54 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	ft_pixel_put(t_env *env, int c, int r, int color)
// {
// 	char	*dst;

// 	if (c < 0 || c >= file->cst.width || r < 0 || r >= file->cst.height)
// 		return ;
// 	dst = file->img.addr + (r * file->img.line_len + c * (file->img.bpp / 8));
// 	*(unsigned int *)dst = color;
// }

// static int ft_get_ns_wall(int px, int py, int x, int y){
//   if (py <= y)
//     return (SOUTH);
//   else
//     return (NORTH);
// }

// static int ft_get_ew_wall(int px, int py, int x, int y){
//   if (px <= x)
//     return (EAST);
//   else
//     return (WEST);
  
// }

// static int	ft_get_color_tex(t_env *c, int x, int y, int type)
// {
// 	t_img	tex;
// 	int		color;

// 	tex = c->buf[type];
// 	if (x < 0 || x >= tex.w || y < 0 || y >= tex.h)
// 		return (0);
// 	color = *(unsigned int *)(tex.addr + (y * tex.line_len + x * (tex.bpp / 8)));
// 	return (color);
// }

// static int	ft_get_color(t_env *c, int texX, int texY, int wall)
// {
// 	t_img	tex;
// 	int		color;
  
// 	color = ft_get_color_tex(c, texX, texY, wall);
// //   if (wall == NORTH)
// //   {
// //     // color = 0x00FF0000; //red
// //   }
  

  
// //   else if (wall == SOUTH)
// //   {
// //     color = 0x0000FF00; //green
// // 	// color = ft_get_color_tex(c, SOUTH);
// //   }
// //   else if (wall == EAST)
// //   {
// //     color = 0x000000FF; //blue
// // 	// color = ft_get_color_tex(c, EAST);
// //   }
// //   else if (wall == WEST)
// //   {
// //     color = 0x00FFFF00; //yellow
// // 	// color = ft_get_color_tex(c, WEST);
// //   }
// 	return (color);
// }

// void	ft_draw(t_env *env, int col)
// {
// 	//calculate ray position and direction
// 	double cameraX = 2 * col / (double)file->cst.width - 1; //x-coordinate in camera space
// 	double rayDirX = file->cst.dirX + (file->cst.planeX)*cameraX;
// 	double rayDirY = file->cst.dirY + (file->cst.planeY)*cameraX;

// 	//which box of the map we're in
// 	int mapX = (int)(file->data.px);
// 	int mapY = (int)(file->data.py);

// 	//length of ray from current position to next x or y-side
// 	double sideDistX;
// 	double sideDistY;

// 	//length of ray from one x or y-side to next x or y-side
// 	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
// 	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
// 	double perpWallDist;

// 	//what direction to step in x or y-direction (either +1 or -1)
// 	int stepX;
// 	int stepY;

// 	int hit = 0; //was there a wall hit?
// 	int side; //was a NS or a EW wall hit?

// 	//calculate step and initial sideDist
// 	if(rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (file->data.px - mapX) * deltaDistX;
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		sideDistX = (mapX + 1.0 - file->data.px) * deltaDistX;
// 	}
// 	if(rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (file->data.py - mapY) * deltaDistY;
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		sideDistY = (mapY + 1.0 - file->data.py) * deltaDistY;
// 	}
// 	//perform DDA
// 	while (hit == 0)
// 	{
// 		//jump to next map square, either in x-direction, or in y-direction
// 		if(sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			mapX += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			mapY += stepY;
// 			side = 1;
// 		}
// 		// Check if ray has hit a wall
// 		if(file->data.map[mapX][mapY] > '0') hit = 1;
// 	}

// 	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
// 	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
// 	else          perpWallDist = (sideDistY - deltaDistY);

// 	//Calculate height of line to draw on screen
// 	int lineHeight = (int)(file->cst.height / perpWallDist);


// 	int pitch = 100;

// 	//calculate lowest and highest pixel to fill in current stripe
// 	int drawStart = -lineHeight / 2 + (file->cst.height) / 2 + pitch;
// 	if(drawStart < 0) drawStart = 0;
// 	int drawEnd = lineHeight / 2 + (file->cst.height) / 2 + pitch;
// 	if(drawEnd >= (file->cst.height)) drawEnd = (file->cst.height) - 1;

// 	//texturing calculations
// 	int texNum = file->data.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

//       //calculate value of wallX
//       double wallX; //where exactly the wall was hit
//       if(side == 0) wallX = file->data.py + perpWallDist * rayDirY;
//       else          wallX = file->data.px + perpWallDist * rayDirX;
//       wallX -= floor((wallX));
//     //   printf("wallX = %f\n", wallX);
//       //x coordinate on the texture
//       int texX = (int)(wallX * (double)(file->buf[0].w));
//       if(side == 0 && rayDirX > 0) texX = file->buf[0].w - texX - 1;
//       if(side == 1 && rayDirY < 0) texX = file->buf[0].w - texX - 1;

//       // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
//       // How much to increase the texture coordinate per screen pixel
//       double step = 1.0 * file->buf[0].h / lineHeight;
//       // Starting texture coordinate
//       double texPos = (drawStart - pitch - (file->cst.height) / 2 + lineHeight / 2) * step;
//       for(int y = drawStart; y < drawEnd; y++)
//       {
//         // Cast the texture coordinate to integer, and mask with (file->buf[0].h - 1) in case of overflow
//         int texY = (int)texPos & (file->buf[0].h - 1);
//         texPos += step;
//         // Uint32 color = texture[texNum][file->buf[0].h * texY + texX];
//         // int color = ft_get_color(file, texX, texY);

// 		int wall;

// 		if (side == 1)
// 			wall = ft_get_ns_wall(file->data.px, file->data.py, mapX, mapY);
// 		else
// 			wall = ft_get_ew_wall(file->data.px, file->data.py, mapX, mapY);

//         int color = ft_get_color(file, texX, texY, wall);
// 		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 		if(side == 1) color = (color >> 1) & 8355711;
// 		// buffer[y][x] = color;
// 		ft_pixel_put(file, col, y, color);
// 	}
// }
