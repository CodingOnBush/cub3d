/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/29 18:14:25 by momrane          ###   ########.fr       */
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
	double	cameraX = 2 * (col) / (double)env->winw - 1;

	env->ray.raydir.x = env->ray.dirX + (env->ray.planeX)*(cameraX);
	env->ray.raydir.y = env->ray.dirY + (env->ray.planeY)*(cameraX);
	env->ray.mapX = env->px;
	env->ray.mapY = env->py;
	// env->ray.deltadist.y = 1e30;
	// env->ray.deltadist.x = 1e30;
	// if (env->ray.raydir.x != 0)
	// 	env->ray.deltadist.x = fabs(1 / env->ray.raydir.x);
	// if (env->ray.raydir.y != 0)
	// 	env->ray.deltadist.y = fabs(1 / env->ray.raydir.y);
	// env->ray.deltadist.x = (env->ray.raydir.x == 0) ? 1e30 : fabs(1 / env->ray.raydir.x);
	// env->ray.deltadist.y = (env->ray.raydir.y == 0) ? 1e30 : fabs(1 / env->ray.raydir.y);
}

static t_vic	ft_get_delta(t_vic raydir)
{
	t_vic	deltadist;

	deltadist.x = 1e30;
	deltadist.y = 1e30;
	if (raydir.x != 0)
		deltadist.x = fabs(1 / raydir.x);
	if (raydir.y != 0)
		deltadist.y = fabs(1 / raydir.y);
	return (deltadist);
}

static void ft_handle_stepx(t_env *env, t_vic deltadist)
{
	if(env->ray.raydir.x < 0)
	{
		env->ray.stepX = -1;
		env->ray.sidedist.x = (env->px - env->ray.mapX) * deltadist.x;
		if (env->ray.sidedist.x == 0)
			env->ray.sidedist.x = 0.1;
	}
	else
	{
		env->ray.stepX = 1;
		env->ray.sidedist.x = (env->ray.mapX + 1.0 - env->px) * deltadist.x;
		if (env->ray.sidedist.x == 0)
			env->ray.sidedist.x = 0.1;
	}
}

static void	ft_handle_stepy(t_env *env, t_vic deltadist)
{
	if(env->ray.raydir.y < 0)
	{
		env->ray.stepY = -1;
		env->ray.sidedist.y = (env->py - env->ray.mapY) * deltadist.y;
		if (env->ray.sidedist.y == 0)
			env->ray.sidedist.y = 0.1;
	}
	else
	{
		env->ray.stepY = 1;
		env->ray.sidedist.y = (env->ray.mapY + 1.0 - env->py) * deltadist.y;
		if (env->ray.sidedist.y == 0)
			env->ray.sidedist.y = 0.1;
	}
}

static double	ft_get_oppside(t_env *env, t_vic sidedist, t_vic deltadist)
{
	while (1)
	{
		if(sidedist.x < sidedist.y)
		{
			sidedist.x += deltadist.x;
			env->ray.mapX += env->ray.stepX;
			env->ray.side = 0;
		}
		else
		{
			sidedist.y += deltadist.y;
			env->ray.mapY += env->ray.stepY;
			env->ray.side = 1;
		}
		if (env->ray.mapX < 0 || env->ray.mapY < 0 || env->ray.mapX >= env->mapw || env->ray.mapY >= env->maph)
			break ;
		if(env->map[env->ray.mapX][env->ray.mapY] > '0')
			break;
	}
	if(env->ray.side == 0)
		return (sidedist.x - deltadist.x);
	else
		return (sidedist.y - deltadist.y);
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

static int	ft_get_line_height(t_env *env)
{
	double		opposite_side;
	t_vic const	deltadist = ft_get_delta(env->ray.raydir);
	int			line_height;

	ft_handle_stepx(env, deltadist);
	ft_handle_stepy(env, deltadist);
	opposite_side = ft_get_oppside(env, env->ray.sidedist, env->ray.deltadist);
	line_height = (int)(env->winh / opposite_side);
	return (line_height);
}

static void	ft_draw2(t_env *env, int col)
{
	int	row;
	int	color;
	int	draw_start;
	int	draw_end;

	int	line_height;
	
	ft_init_draw_vars(env, col);
	line_height = ft_get_line_height(env);
	
	env->ray.pitch = 100;
	env->ray.drawStart = -(line_height) / 2 + (env->winh) / 2 + env->ray.pitch;
	if(env->ray.drawStart < 0)
		env->ray.drawStart = 0;
	env->ray.drawEnd = (line_height) / 2 + (env->winh) / 2 + env->ray.pitch;
	if(env->ray.drawEnd >= (env->winh))
		env->ray.drawEnd = (env->winh) - 1;
	
	if(env->ray.side == 0)
		env->ray.wallx = env->py + env->ray.perpWallDist * env->ray.raydir.y;
	else
	  	env->ray.wallx = env->px + env->ray.perpWallDist * env->ray.raydir.x;
	env->ray.wallx -= floor((env->ray.wallx));
	
	
	int texX = (int)(env->ray.wallx * (double)(env->img[NORTH].imgw));
	if(env->ray.side == 0 && env->ray.raydir.x > 0)
		texX = env->img[NORTH].imgh - texX - 1;
	if(env->ray.side == 1 && env->ray.raydir.y < 0)
		texX = env->img[NORTH].imgw - texX - 1;
	env->ray.step = 1.0 * env->img[NORTH].imgh / (line_height);
	env->ray.texPos = (env->ray.drawStart - env->ray.pitch - (env->winh) / 2 + (line_height) / 2) * (env->ray.step);
	row = 0;
	if (env->ray.drawStart > env->winh || env->ray.drawEnd < 0)
		return ;
	
	// ft_draw_ceiling(env, 0, draw_start, col);
	
	while (row < env->ray.drawStart)
	{
		color = (env->file.colors[0][R] << 16 | env->file.colors[0][G] << 8 | env->file.colors[0][B]);
		ft_pixel_put(env, col, row, color);
		row++;
	}

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








