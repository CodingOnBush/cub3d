/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 16:53:09 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_pixel_put2(t_env *env, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= env->winw || r < 0 || r >= env->winh)
		return ;
	dst = env->img[CANVAS].addr + (r * env->img[CANVAS].llen + c * (env->img[CANVAS].bpp / 8));
	*(unsigned int *)dst = color;
}

static int ft_get_ns_wall(int px, int py, int x, int y){
  if (px <= x)
    return (SOUTH);
  else
    return (NORTH);
}

static int ft_get_ew_wall(int px, int py, int x, int y){
  if (py <= y)
    return (EAST);
  else
    return (WEST);
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

static void	ft_draw(t_env *env, int col)
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

	// printf("rayDirX = %f\n", rayDirX);
	// printf("dirX = %f\n", env->ray.dirX);
	// printf("planeX = %f\n", env->ray.planeX);

	// printf("rayDirY = %f\n", rayDirY);
	// printf("dirY = %f\n", env->ray.dirY);
	// printf("planeY = %f\n\n", env->ray.planeY);
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
		if (mapX < 0 || mapY < 0 || mapX >= env->mapw || mapY >= env->maph)
			break ;
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
			wall = ft_get_ew_wall(env->px, env->py, mapX, mapY);
		else
			wall = ft_get_ns_wall(env->px, env->py, mapX, mapY);

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
}

static void	ft_move(t_env *env)
{
	double	stepHorizontalX;
	double	stepHorizontalY;
	double	stepVerticalX;
	double	stepVerticalY;

	stepHorizontalX = env->ray.planeX * env->ray.ms;
	stepHorizontalY = env->ray.planeY * env->ray.ms;
	stepVerticalX = env->ray.dirX * env->ray.ms;
	stepVerticalY = env->ray.dirY * env->ray.ms;
	if (env->down)
	{
		// printf("down\n");
		if(env->map[(int)(env->px - stepVerticalX)][(int)(env->py)] == '0')
			env->px -= stepVerticalX;
		if(env->map[(int)(env->px)][(int)(env->py - stepVerticalY)] == '0')
			env->py -= stepVerticalY;
	}
	if (env->up)
	{
		// printf("up\n");
		if(env->map[(int)(env->px + stepVerticalX)][(int)(env->py)] == '0')
			env->px += stepVerticalX;
		if(env->map[(int)(env->px)][(int)(env->py + stepVerticalY)] == '0')
			env->py += stepVerticalY;
	}
	if (env->left)
	{
		// printf("left\n");
		if (env->map[(int)(env->px - stepHorizontalX)][(int)(env->py)] == '0')
			env->px -= stepHorizontalX;
		if (env->map[(int)(env->px)][(int)(env->py - stepHorizontalY)] == '0')
			env->py -= stepHorizontalY;
	}
	if (env->right)
	{
		// printf("right\n");
		if (env->map[(int)(env->px + stepHorizontalX)][(int)(env->py)] == '0')
			env->px += stepHorizontalX;
		if (env->map[(int)(env->px)][(int)(env->py + stepHorizontalY)] == '0')
			env->py += stepHorizontalY;
	}
}

static void	ft_rotate(t_env *env)
{
	if (env->rotleft)
	{
		// printf("rot left\n");
		double oldDirX = env->ray.dirX;
		env->ray.dirX = env->ray.dirX * cos(env->ray.rs) - env->ray.dirY * sin(env->ray.rs);
		env->ray.dirY = oldDirX * sin(env->ray.rs) + env->ray.dirY * cos(env->ray.rs);
		double oldPlaneX = env->ray.planeX;
		env->ray.planeX = env->ray.planeX * cos(env->ray.rs) - env->ray.planeY * sin(env->ray.rs);
		env->ray.planeY = oldPlaneX * sin(env->ray.rs) + env->ray.planeY * cos(env->ray.rs);
	}
	if (env->rotright)
	{
		// printf("rot right\n");
		double oldDirX = env->ray.dirX;
		env->ray.dirX = env->ray.dirX * cos(-env->ray.rs) - env->ray.dirY * sin(-env->ray.rs);
		env->ray.dirY = oldDirX * sin(-env->ray.rs) + env->ray.dirY * cos(-env->ray.rs);
		double oldPlaneX = env->ray.planeX;
		env->ray.planeX = env->ray.planeX * cos(-env->ray.rs) - env->ray.planeY * sin(-env->ray.rs);
		env->ray.planeY = oldPlaneX * sin(-env->ray.rs) + env->ray.planeY * cos(-env->ray.rs);
	}
}

int	ft_render(t_env *env)
{
	int	col;

	col = 0;
	if (env->down || env->up || env->left || env->right)
		ft_move(env);
	if (env->rotleft || env->rotright)
		ft_rotate(env);
	while (col < env->winw)
	{
		ft_draw(env, col);
		col++;
	}
	if (env->mlx_ptr && env->win_ptr && env->img[CANVAS].mlx_img)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[CANVAS].mlx_img, 0, 0);
	return (0);
}








