/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 10:24:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_print_ray(t_ray ray)
{
	printf("\ncameraX = %f\n", ray.cameraX);
	printf("rayDirX = %f\n", ray.rayDirX);
	printf("rayDirY = %f\n", ray.rayDirY);
	printf("mapX = %d\n", ray.mapX);
	printf("mapY = %d\n", ray.mapY);
	printf("sideDistX = %f\n", ray.sideDistX);
	printf("sideDistY = %f\n", ray.sideDistY);
	printf("deltaDistX = %f\n", ray.deltaDistX);
	printf("deltaDistY = %f\n", ray.deltaDistY);
	printf("perpWallDist = %f\n", ray.perpWallDist);
	printf("stepX = %d\n", ray.stepX);
	printf("stepY = %d\n", ray.stepY);
	printf("side = %d\n", ray.side);
	printf("hit = %d\n", ray.hit);
	printf("texCol = %d\n\n", ray.texCol);
}

void	ft_pixel_put(t_cub3d *cub, int c, int r, int color)
{
	char	*dst;

	// if (c < 0 || c >= cub->cst.width || r < 0 || r >= cub->cst.height)
	// 	return ;
	dst = cub->img.addr + (r * cub->img.llen + c * (cub->img.bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ft_pixel_put2(t_env *env, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= env->winw || r < 0 || r >= env->winh)
		return ;
	dst = env->img[CANVAS].addr + (r * env->img[CANVAS].llen + c * (env->img[CANVAS].bpp / 8));
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

static int	ft_get_color_tex(t_cub3d *c, int x, int y, int type)
{
	t_img	tex;
	int		color;

	tex = c->buf[type];
	if (x < 0 || x >= tex.imgw || y < 0 || y >= tex.imgh)
		return (0);
	color = *(unsigned int *)(tex.addr + (y * tex.llen + x * (tex.bpp / 8)));
	return (color);
}

static int	ft_get_color(t_cub3d *c, int texX, int texY, int wall)
{
	t_img	tex;
	int		color;
  
	color = ft_get_color_tex(c, texX, texY, wall);
	return (color);
}

static int	ft_get_color2(t_env *e, int texX, int texY, int wall)
{
	t_img	tex;
	int		color;

	tex = e->img[wall];
	if (texX < 0 || texX >= tex.imgw || texY < 0 || texY >= tex.imgh)
		return (0);
	color = *(unsigned int *)(tex.addr + (texY * tex.llen + texX * (tex.bpp / 8)));
	return (color);
}

t_ray	ft_init_ray(t_cub3d *cub, int col)
{
	t_ray	ray;

	ray.cameraX = 2 * col / (double)cub->cst.width - 1; //x-coordinate in camera space
	ray.rayDirX = cub->cst.dirX + (cub->cst.planeX)*(ray.cameraX);
	ray.rayDirY = cub->cst.dirY + (cub->cst.planeY)*(ray.cameraX);
	ray.mapX = (int)(cub->data.px);
	ray.mapY = (int)(cub->data.py);

	return (ray);
}

// void	ft_draw(t_cub3d *cub, int col)
// {
// 	int	y;
// 	int	color;

// 	cub->ray = ft_init_ray(cub, col);
// 	// //calculate ray position and direction
// 	// double cameraX = 2 * col / (double)cub->cst.width - 1; //x-coordinate in camera space
// 	// double rayDirX = cub->cst.dirX + (cub->cst.planeX)*cameraX;
// 	// double rayDirY = cub->cst.dirY + (cub->cst.planeY)*cameraX;

// 	//which box of the map we're in
// 	// int mapX = (int)(cub->data.px);
// 	// int mapY = (int)(cub->data.py);

// 	//length of ray from current position to next x or y-side
// 	double sideDistX;
// 	double sideDistY;

// 	//length of ray from one x or y-side to next x or y-side
// 	double deltaDistX = (cub->ray.rayDirX == 0) ? 1e30 : fabs(1 / cub->ray.rayDirX);
// 	double deltaDistY = (cub->ray.rayDirY == 0) ? 1e30 : fabs(1 / cub->ray.rayDirY);
// 	double perpWallDist;

// 	//what direction to step in x or y-direction (either +1 or -1)
// 	int stepX;
// 	int stepY;

// 	int hit = 0; //was there a wall hit?
// 	int side; //was a NS or a EW wall hit?

// 	//calculate step and initial sideDist
// 	if(cub->ray.rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (cub->data.px - cub->ray.mapX) * deltaDistX;
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		sideDistX = (cub->ray.mapX + 1.0 - cub->data.px) * deltaDistX;
// 	}
// 	if(cub->ray.rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (cub->data.py - cub->ray.mapY) * deltaDistY;
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		sideDistY = (cub->ray.mapY + 1.0 - cub->data.py) * deltaDistY;
// 	}
// 	//perform DDA
// 	while (hit == 0)
// 	{
// 		//jump to next map square, either in x-direction, or in y-direction
// 		if(sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			cub->ray.mapX += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			cub->ray.mapY += stepY;
// 			side = 1;
// 		}
// 		// Check if ray has hit a wall
// 		if(cub->data.map[cub->ray.mapX][cub->ray.mapY] > '0') hit = 1;
// 	}

// 	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
// 	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
// 	else          perpWallDist = (sideDistY - deltaDistY);

// 	//Calculate height of line to draw on screen
// 	int lineHeight = (int)(cub->cst.height / perpWallDist);


// 	int pitch = 100;

// 	//calculate lowest and highest pixel to fill in current stripe
// 	int drawStart = -lineHeight / 2 + (cub->cst.height) / 2 + pitch;
// 	if(drawStart < 0) drawStart = 0;
// 	int drawEnd = lineHeight / 2 + (cub->cst.height) / 2 + pitch;
// 	if(drawEnd >= (cub->cst.height)) drawEnd = (cub->cst.height) - 1;

// 	//texturing calculations
// 	int texNum = cub->data.map[cub->ray.mapX][cub->ray.mapY] - 1; //1 subtracted from it so that texture 0 can be used!

//       //calculate value of wallX
//       double wallX; //where exactly the wall was hit
//       if(side == 0) wallX = cub->data.py + perpWallDist * cub->ray.rayDirY;
//       else          wallX = cub->data.px + perpWallDist * cub->ray.rayDirX;
//       wallX -= floor((wallX));
//     //   printf("wallX = %f\n", wallX);
// 	//x coordinate on the texture
// 	int texX = (int)(wallX * (double)(cub->buf[0].imgw));
// 	if(side == 0 && cub->ray.rayDirX > 0) texX = cub->buf[0].imgh - texX - 1;
// 	if(side == 1 && cub->ray.rayDirY < 0) texX = cub->buf[0].imgw - texX - 1;

// 	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
// 	// How much to increase the texture coordinate per screen pixel
// 	double step = 1.0 * cub->buf[0].imgh / lineHeight;
// 	// Starting texture coordinate
// 	double texPos = (drawStart - pitch - (cub->cst.height) / 2 + lineHeight / 2) * step;
// 	y = 0;
// 	// printf("drawStart = %d\n", drawStart);
// 	// printf("drawEnd = %d\n", drawEnd);
// 	if (drawStart > cub->cst.height || drawEnd < 0)
// 		return ;
// 	while (y < drawStart)
// 	{
// 		color = (cub->data.f->r << 16 | cub->data.f->g << 8 | cub->data.f->b);
// 		ft_pixel_put(cub, col, y, color);
// 		y++;
// 	}
// 	while (y < drawEnd)
// 	{
// 		// Cast the texture coordinate to integer, and mask with (cub->buf[0].h - 1) in case of overflow
// 		int texY = (int)texPos & (cub->buf[0].imgh - 1);
// 		texPos += step;
// 		// Uint32 color = texture[texNum][cub->buf[0].h * texY + texX];
// 		// int color = ft_get_color(cub, texX, texY);

// 		int wall;

// 		if (side == 1)
// 			wall = ft_get_ns_wall(cub->data.px, cub->data.py, cub->ray.mapX, cub->ray.mapY);
// 		else
// 			wall = ft_get_ew_wall(cub->data.px, cub->data.py, cub->ray.mapX, cub->ray.mapY);

// 		int color = ft_get_color(cub, texX, texY, wall);
// 		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 		if(side == 1) color = (color >> 1) & 8355711;
// 		ft_pixel_put(cub, col, y, color);
// 		y++;
// 	}
// 	while (y < cub->cst.height)
// 	{
// 		ft_pixel_put(cub, col, y, color);
// 		color = (cub->data.c->r << 16 | cub->data.c->g << 8 | cub->data.c->b);
// 		y++;
// 	}
// 	// ft_print_ray(cub->ray);
// 	if (col == 2)
// 	{
// 		printf("cameraX = %f\n", cub->ray.cameraX);
// 		printf("rayDirX = %f\n", cub->ray.rayDirX);
// 		printf("rayDirY = %f\n", cub->ray.rayDirY);
// 		printf("mapX = %d\n", cub->ray.mapX);
// 		printf("mapY = %d\n", cub->ray.mapY);
// 		printf("sideDistX = %f\n", sideDistX);
// 		printf("sideDistY = %f\n", sideDistY);
// 		printf("deltaDistX = %f\n", deltaDistX);
// 		printf("deltaDistY = %f\n", deltaDistY);
// 		printf("perpWallDist = %f\n", perpWallDist);
// 		printf("stepX = %d\n", stepX);
// 		printf("stepY = %d\n", stepY);
// 		printf("side = %d\n", side);
// 		printf("hit = %d\n", hit);
// 		printf("texCol = %d\n\n\n", cub->ray.texCol);
// 		printf("[%f, %f]\n", cub->data.px, cub->data.py);
// 	}
// }

void	ft_draw2(t_env *env, int col)
{
	int	y;
	int	color;

	// printf("rendering column %d\n", col);
	// cub->ray = ft_init_ray(cub, col);
	double	cameraX = 2 * col / (double)env->winw - 1; //x-coordinate in camera space
	double	rayDirX = env->ray.dirX + (env->ray.planeX)*(cameraX);
	double	rayDirY = env->ray.dirY + (env->ray.planeY)*(cameraX);
	int		mapX = (int)(env->px);
	int		mapY = (int)(env->py);
	// //calculate ray position and direction
	// double cameraX = 2 * col / (double)cub->cst.width - 1; //x-coordinate in camera space
	// double rayDirX = cub->cst.dirX + (cub->cst.planeX)*cameraX;
	// double rayDirY = cub->cst.dirY + (cub->cst.planeY)*cameraX;

	//which box of the map we're in
	// int mapX = (int)(cub->data.px);
	// int mapY = (int)(cub->data.py);

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
		sideDistX = (env->px - mapX) * deltaDistX;
		if (sideDistX == 0)
			sideDistX = 0.1;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - env->px) * deltaDistX;
		if (sideDistX == 0)
			sideDistX = 0.1;
	}
	if(rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (env->py - mapY) * deltaDistY;
		if (sideDistY == 0)
			sideDistY = 0.1;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - env->py) * deltaDistY;
		if (sideDistY == 0)
			sideDistY = 0.1;
	}
	// printf("rayDirX = %f\n", rayDirX);
	// printf("rayDirY = %f\n", rayDirY);

	// printf("sideDistX = %f\n", sideDistX);
	// printf("sideDistY = %f\n", sideDistY);
	
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
		if(env->map[mapX][mapY] > '0') hit = 1;
	}
	// printf("mapX = %d\n", mapX);
	// printf("mapY = %d\n", mapY);
	// printf("map[mapX][mapY] = %c\n", env->map[mapX][mapY]);

	// printf("sideDistX = %f\n", sideDistX);
	// printf("sideDistY = %f\n", sideDistY);
	
	// printf("deltaDistX = %f\n", deltaDistX);
	// printf("deltaDistY = %f\n\n", deltaDistY);

	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
	else          perpWallDist = (sideDistY - deltaDistY);

	// printf("perpWallDist = %f\n", perpWallDist);

	//Calculate height of line to draw on screen
	int lineHeight = (int)(env->winh / perpWallDist);

	// printf("lineHeight = %d\n", lineHeight);

	int pitch = 100;

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + (env->winh) / 2 + pitch;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + (env->winh) / 2 + pitch;
	if(drawEnd >= (env->winh)) drawEnd = (env->winh) - 1;

	// printf("drawStart = %d\n", drawStart);
	// printf("drawEnd = %d\n", drawEnd);

	//texturing calculations
	// int texNum = env->map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = env->py + perpWallDist * rayDirY;
      else          wallX = env->px + perpWallDist * rayDirX;
      wallX -= floor((wallX));
    //   printf("wallX = %f\n", wallX);
	//x coordinate on the texture
	int texX = (int)(wallX * (double)(env->img[NORTH].imgw));
	if(side == 0 && rayDirX > 0) texX = env->img[NORTH].imgh - texX - 1;
	if(side == 1 && rayDirY < 0) texX = env->img[NORTH].imgw - texX - 1;

	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * env->img[NORTH].imgh / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - pitch - (env->winh) / 2 + lineHeight / 2) * step;
	y = 0;
	// printf("drawStart = %d\n", drawStart);
	// printf("drawEnd = %d\n", drawEnd);
	if (drawStart > env->winh || drawEnd < 0)
		return ;
	while (y < drawStart)
	{
		// color = (cub->data.f->r << 16 | cub->data.f->g << 8 | cub->data.f->b);
		color = (env->file.colors[0][R] << 16 | env->file.colors[0][G] << 8 | env->file.colors[0][B]);
		ft_pixel_put2(env, col, y, color);
		y++;
	}
	while (y < drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (cub->buf[0].h - 1) in case of overflow
		int texY = (int)texPos & (env->img[NORTH].imgh - 1);
		texPos += step;
		// Uint32 color = texture[texNum][cub->buf[0].h * texY + texX];
		// int color = ft_get_color(cub, texX, texY);

		int wall;

		if (side == 1)
			wall = ft_get_ns_wall(env->px, env->py, mapX, mapY);
		else
			wall = ft_get_ew_wall(env->px, env->py, mapX, mapY);

		int color = ft_get_color2(env, texX, texY, wall);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(side == 1) color = (color >> 1) & 8355711;
		ft_pixel_put2(env, col, y, color);
		y++;
	}
	while (y < env->winh)
	{
		// color = (cub->data.c->r << 16 | cub->data.c->g << 8 | cub->data.c->b);
		color = (env->file.colors[1][R] << 16 | env->file.colors[1][G] << 8 | env->file.colors[1][B]);
		ft_pixel_put2(env, col, y, color);
		y++;
	}
	// if (col >= 0)
	// {
	// 	printf("cameraX = %f\n", cameraX);
	// 	printf("rayDirX = %f\n", rayDirX);
	// 	printf("rayDirY = %f\n", rayDirY);
	// 	printf("mapX = %d\n", mapX);
	// 	printf("mapY = %d\n", mapY);
	// 	printf("sideDistX = %f\n", sideDistX);
	// 	printf("sideDistY = %f\n", sideDistY);
	// 	printf("deltaDistX = %f\n", deltaDistX);
	// 	printf("deltaDistY = %f\n", deltaDistY);
	// 	printf("perpWallDist = %f\n", perpWallDist);
	// 	printf("stepX = %d\n", stepX);
	// 	printf("stepY = %d\n", stepY);
	// 	printf("side = %d\n", side);
	// 	printf("hit = %d\n", hit);
	// 	printf("texCol = %d\n\n\n", env->ray.texCol);
	// 	printf("[%f, %f]\n", env->px, env->py);
	// }
}
