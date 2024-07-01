/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 14:11:04 by momrane          ###   ########.fr       */
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

static int	ft_get_line_height(t_env *env, int col)
{
	double	cameraX;
	t_vic	sidedist;
	t_vic	deltadist;
	int		stepX;
	int		stepY;

		
	env->ray.mapX = (int)env->px;
	env->ray.mapY = (int)env->py;
	cameraX = 2 * (col) / (double)env->winw - 1;
	env->ray.raydir.x = env->ray.dirX + (env->ray.planeX)*(cameraX);
	env->ray.raydir.y = env->ray.dirY + (env->ray.planeY)*(cameraX);

	deltadist.x = 1e30;
	if (env->ray.raydir.x != 0)
		deltadist.x = fabs(1 / env->ray.raydir.x);

	deltadist.y = 1e30;
	if (env->ray.raydir.y != 0)
		deltadist.y = fabs(1 / env->ray.raydir.y);
		
	if(env->ray.raydir.x < 0)
	{
		stepX = -1;
		sidedist.x = (env->px - env->ray.mapX) * deltadist.x;
		if (sidedist.x == 0)
			sidedist.x = 0.1;
	}
	else
	{
		stepX = 1;
		sidedist.x = (env->ray.mapX + 1.0 - env->px) * deltadist.x;
		if (sidedist.x == 0)
			sidedist.x = 0.1;
	}
	if(env->ray.raydir.y < 0)
	{
		stepY = -1;
		sidedist.y = (env->py - env->ray.mapY) * deltadist.y;
		if (sidedist.y == 0)
			sidedist.y = 0.1;
	}
	else
	{
		stepY = 1;
		sidedist.y = (env->ray.mapY + 1.0 - env->py) * deltadist.y;
		if (sidedist.y == 0)
			sidedist.y = 0.1;
	}
	while (1)
	{
		if(sidedist.x < sidedist.y)
		{
			sidedist.x += deltadist.x;
			env->ray.mapX += stepX;
			env->ray.side = 0;
		}
		else
		{
			sidedist.y += deltadist.y;
			env->ray.mapY += stepY;
			env->ray.side = 1;
		}
		if (env->ray.mapX < 0 || env->ray.mapY < 0 || env->ray.mapX >= env->mapw || env->ray.mapY >= env->maph)
			break ;
		if(env->map[env->ray.mapX][env->ray.mapY] > '0')
			break;
	}
	if(env->ray.side == 0)
		env->ray.perpWallDist = (sidedist.x - deltadist.x);
	else
		env->ray.perpWallDist = (sidedist.y - deltadist.y);
	return ((int)(env->winh / env->ray.perpWallDist));
}

static int	ft_get_texx(t_env *env)
{
	double wallX; //where exactly the wall was hit
	if(env->ray.side == 0)
		wallX = env->py + env->ray.perpWallDist * env->ray.raydir.y;
	else
	  	wallX = env->px + env->ray.perpWallDist * env->ray.raydir.x;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(env->img[NORTH].imgw));
	if(env->ray.side == 0 && env->ray.raydir.x > 0)
		texX = env->img[NORTH].imgh - texX - 1;
	if(env->ray.side == 1 && env->ray.raydir.y < 0)
		texX = env->img[NORTH].imgw - texX - 1;
	return (texX);	
}

static int	ft_draw_wall(t_env *env, int col, int row, int lineHeight)
{
	// double wallX; //where exactly the wall was hit
	// if(env->ray.side == 0)
	// 	wallX = env->py + env->ray.perpWallDist * env->ray.raydir.y;
	// else
	//   	wallX = env->px + env->ray.perpWallDist * env->ray.raydir.x;
	// wallX -= floor((wallX));
	// int texX = (int)(wallX * (double)(env->img[NORTH].imgw));
	// if(env->ray.side == 0 && env->ray.raydir.x > 0)
	// 	texX = env->img[NORTH].imgh - texX - 1;
	// if(env->ray.side == 1 && env->ray.raydir.y < 0)
	// 	texX = env->img[NORTH].imgw - texX - 1;
	int		texX = ft_get_texx(env);
	double step = 1.0 * env->img[NORTH].imgh / lineHeight;
	double texPos = (env->ray.start - (env->winh) / 2 + lineHeight / 2) * step;
	while (row < env->ray.end)
	{
		int texY = (int)texPos & (env->img[NORTH].imgh - 1);
		texPos += step;
		int wall;
		if (env->ray.side == 1)
		{
			if (env->py <= env->ray.mapY)
				wall = SOUTH;
			else
				wall = NORTH;
		}
		else
		{
			if (env->px <= env->ray.mapX)
				wall = WEST;
			else
				wall = EAST;
		}
		int color = ft_get_color2(env, texX, texY, wall);
		if(env->ray.side == 1) color = (color >> 1) & 8355711;
		ft_pixel_put(env, col, row, color);
		row++;
	}
	return (row);
}

static void	ft_set_start_and_end(t_env *env, int line_height)
{
	env->ray.start = -line_height / 2 + (env->winh) / 2;
	if(env->ray.start < 0)
		env->ray.start = 0;
	env->ray.end = line_height / 2 + (env->winh) / 2;
	if(env->ray.end >= (env->winh))
		env->ray.end = (env->winh) - 1;
}

static void	ft_draw2(t_env *env, int col)
{
	int const	lineHeight = ft_get_line_height(env, col);
	int			row;
	int			color;

	ft_set_start_and_end(env, lineHeight);	
	if (env->ray.start > env->winh || env->ray.end < 0)
		return ;
	row = 0;
	color = (env->file.colors[0][R] << 16 | env->file.colors[0][G] << 8 | env->file.colors[0][B]);
	while (row < env->ray.start)
	{
		ft_pixel_put(env, col, row, color);
		row++;
	}
	row = ft_draw_wall(env, col, row, lineHeight);
	color = (env->file.colors[1][R] << 16 | env->file.colors[1][G] << 8 | env->file.colors[1][B]);
	while (row < env->winh)
	{
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
		ft_draw2(env, col);
		col++;
	}
	if (env->mlx_ptr && env->win_ptr && env->img[CANVAS].mlx_img)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[CANVAS].mlx_img, 0, 0);
	return (0);
}








