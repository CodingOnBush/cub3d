/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 18:21:21 by momrane          ###   ########.fr       */
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

int ft_get_ns_wall(int px, int py, int x, int y){
	(void)py;
	(void)y;
	if (px <= x)
		return (WEST);
	else
		return (EAST);
}

int ft_get_ew_wall(int px, int py, int x, int y){
	(void)px;
	(void)x;
	if (py <= y)
		return (SOUTH);
	else
		return (NORTH);
}

int	ft_get_color2(t_env *e, int texX, int texY, int wall)
{
	t_img	tex;
	int		color;

	tex = e->img[wall];
	if (texX < 0 || texX >= tex.imgw || texY < 0 || texY >= tex.imgh)
		return (0);
	color = *(unsigned int *)(tex.addr + (texY * tex.llen + texX * (tex.bpp / 8)));
	return (color);
}

static void	ft_init_draw_vars(t_env *env, int col)
{
	env->ray.cameraX = 2 * (col) / (double)env->winw - 1;
	env->ray.rayDirX = env->ray.dirX + (env->ray.planeX)*(env->ray.cameraX);
	env->ray.rayDirY = env->ray.dirY + (env->ray.planeY)*(env->ray.cameraX);
	env->ray.mapX = env->px;
	env->ray.mapY = env->py;
	env->ray.deltaDistY = 1e30;
	env->ray.deltaDistX = 1e30;
	if (env->ray.rayDirX != 0)
		env->ray.deltaDistX = fabs(1 / env->ray.rayDirX);
	if (env->ray.rayDirY != 0)
		env->ray.deltaDistY = fabs(1 / env->ray.rayDirY);
	// env->ray.deltaDistX = (env->ray.rayDirX == 0) ? 1e30 : fabs(1 / env->ray.rayDirX);
	// env->ray.deltaDistY = (env->ray.rayDirY == 0) ? 1e30 : fabs(1 / env->ray.rayDirY);
}

static void ft_handle_stepx(t_env *env)
{
	if(env->ray.rayDirX < 0)
	{
		env->ray.stepX = -1;
		env->ray.sideDistX = (env->px - env->ray.mapX) * env->ray.deltaDistX;
		if (env->ray.sideDistX == 0)
			env->ray.sideDistX = 0.1;
	}
	else
	{
		env->ray.stepX = 1;
		env->ray.sideDistX = (env->ray.mapX + 1.0 - env->px) * env->ray.deltaDistX;
		if (env->ray.sideDistX == 0)
			env->ray.sideDistX = 0.1;
	}
}

static void	ft_handle_stepy(t_env *env)
{
	if(env->ray.rayDirY < 0)
	{
		env->ray.stepY = -1;
		env->ray.sideDistY = (env->py - env->ray.mapY) * env->ray.deltaDistY;
		if (env->ray.sideDistY == 0)
			env->ray.sideDistY = 0.1;
	}
	else
	{
		env->ray.stepY = 1;
		env->ray.sideDistY = (env->ray.mapY + 1.0 - env->py) * env->ray.deltaDistY;
		if (env->ray.sideDistY == 0)
			env->ray.sideDistY = 0.1;
	}
}

static void ft_hit_wall(t_env *env)
{
	while (1)
	{
		if(env->ray.sideDistX < env->ray.sideDistY)
		{
			env->ray.sideDistX += env->ray.deltaDistX;
			env->ray.mapX += env->ray.stepX;
			env->ray.side = 0;
		}
		else
		{
			env->ray.sideDistY += env->ray.deltaDistY;
			env->ray.mapY += env->ray.stepY;
			env->ray.side = 1;
		}
		if (env->ray.mapX < 0 || env->ray.mapY < 0 || env->ray.mapX >= env->mapw || env->ray.mapY >= env->maph)
			break ;
		if(env->map[env->ray.mapX][env->ray.mapY] > '0')
			break;
	}
}

static void	ft_draw_ceiling(t_env *env, int start, int end, int col)
{
	t_file const	f = env->file;
	int				color;
	int				row;

	row = start;
	if (row >= end)
		return ;
	while (row < end)
	{
		color = (f.colors[0][R] << 16 | f.colors[0][G] << 8 | f.colors[0][B]);
		ft_pixel_put(env, col, row, color);
		row++;
	}
}

static void	ft_draw2(t_env *env, int col)
{
	int	row;
	int	color;
	int	draw_start;
	int	draw_end;
	
	ft_init_draw_vars(env, col);

	ft_handle_stepx(env);
	ft_handle_stepy(env);
	ft_hit_wall(env);
	
	
	if(env->ray.side == 0)
		env->ray.perpWallDist = (env->ray.sideDistX - env->ray.deltaDistX);
	else
		env->ray.perpWallDist = (env->ray.sideDistY - env->ray.deltaDistY);

	env->ray.lineHeight = (int)(env->winh / env->ray.perpWallDist);
	env->ray.pitch = 100;
	env->ray.drawStart = -(env->ray.lineHeight) / 2 + (env->winh) / 2 + env->ray.pitch;
	if(env->ray.drawStart < 0)
		env->ray.drawStart = 0;
	env->ray.drawEnd = (env->ray.lineHeight) / 2 + (env->winh) / 2 + env->ray.pitch;
	if(env->ray.drawEnd >= (env->winh))
		env->ray.drawEnd = (env->winh) - 1;
	
	if(env->ray.side == 0)
		env->ray.wallx = env->py + env->ray.perpWallDist * env->ray.rayDirY;
	else
	  	env->ray.wallx = env->px + env->ray.perpWallDist * env->ray.rayDirX;
	env->ray.wallx -= floor((env->ray.wallx));
	
	
	int texX = (int)(env->ray.wallx * (double)(env->img[NORTH].imgw));
	if(env->ray.side == 0 && env->ray.rayDirX > 0)
		texX = env->img[NORTH].imgh - texX - 1;
	if(env->ray.side == 1 && env->ray.rayDirY < 0)
		texX = env->img[NORTH].imgw - texX - 1;
	env->ray.step = 1.0 * env->img[NORTH].imgh / (env->ray.lineHeight);
	env->ray.texPos = (env->ray.drawStart - env->ray.pitch - (env->winh) / 2 + (env->ray.lineHeight) / 2) * (env->ray.step);
	row = 0;
	if (env->ray.drawStart > env->winh || env->ray.drawEnd < 0)
		return ;
	
	ft_draw_ceiling(env, 0, draw_start, col);
	
	// while (row < env->ray.drawStart)
	// {
	// 	color = (env->file.colors[0][R] << 16 | env->file.colors[0][G] << 8 | env->file.colors[0][B]);
	// 	ft_pixel_put(env, col, row, color);
	// 	row++;
	// }

	// ft_draw_wall(draw_start, draw_end);

	while (row < env->ray.drawEnd)
	{
		env->ray.texY = (int)env->ray.texPos & (env->img[NORTH].imgh - 1);
		env->ray.texPos += (env->ray.step);
		if (env->ray.side == 1)
			env->ray.wall = ft_get_ew_wall(env->px, env->py, env->ray.mapX, env->ray.mapY);
		else
			env->ray.wall = ft_get_ns_wall(env->px, env->py, env->ray.mapX, env->ray.mapY);

		color = ft_get_color2(env, texX, env->ray.texY, env->ray.wall);
		if(env->ray.side == 1)
			color = (color >> 1) & 8355711;
		ft_pixel_put(env, col, row, color);
		row++;
	}



	// ft_draw_floor(draw_end, env->winh)
	while (row < env->winh)
	{
		color = (env->file.colors[1][R] << 16 | env->file.colors[1][G] << 8 | env->file.colors[1][B]);
		ft_pixel_put(env, col, row, color);
		row++;
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








