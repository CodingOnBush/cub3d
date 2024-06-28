/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 12:21:09 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_pixel_put(t_env *env, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= env->winw || r < 0 || r >= env->winh)
		return ;
	dst = env->img[CANVAS].addr + (r * env->img[CANVAS].llen + c * (env->img[CANVAS].bpp / 8));
	*(unsigned int *)dst = color;
}

static int ft_get_ns_wall(int px, int py, int x, int y){
	(void)py;
	(void)y;
	if (px <= x)
		return (WEST);
	else
		return (EAST);
}

static int ft_get_ew_wall(int px, int py, int x, int y){
	(void)px;
	(void)x;
	if (py <= y)
		return (SOUTH);
	else
		return (NORTH);
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
	double cameraX = 2 * (col) / (double)env->winw - 1; //x-coordinate in camera space
	double rayDirX = env->ray.dirX + (env->ray.planeX)*(cameraX);
	double rayDirY = env->ray.dirY + (env->ray.planeY)*(cameraX);
	int	y;
	int	color;
	int		mapX = (int)(env->px);
	int		mapY = (int)(env->py);
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	double	deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	double	perpWallDist;
	int stepX;
	int stepY;
	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

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
	while (hit == 0)
	{
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
		if (mapX < 0 || mapY < 0 || mapX >= env->mapw || mapY >= env->maph)
			break ;
		if(env->map[mapX][mapY] > '0') hit = 1;
	}
	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
	else          perpWallDist = (sideDistY - deltaDistY);
	int lineHeight = (int)(env->winh / perpWallDist);
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








