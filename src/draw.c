/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/30 15:45:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_env *env, int col, int row, int color)
{
	t_img const	img = env->img[CANVAS];
	void		*box;

	if (col < 0 || col >= env->winw)
		return ;
	if (row < 0 || row >= env->winh)
		return ;
	box = img.addr + (row * img.llen + col * (img.bpp / 8));
	*(unsigned int *)box = color;
}

static int	ft_get_tex_pixel(t_env *env, t_point tex)
{
	void	*box;
	t_img	img;
	int		wall;

	if (env->ray.side == 1)
	{
		wall = NORTH;
		if (env->py <= env->ray.mapY)
			wall = SOUTH;
	}
	else
	{
		wall = EAST;
		if (env->px <= env->ray.mapX)
			wall = WEST;
	}
	img = env->img[wall];
	if (tex.x < 0 || tex.x >= img.imgw || tex.y < 0 || tex.y >= img.imgh)
		return (0);
	box = img.addr + (tex.y * img.llen + tex.x * (img.bpp / 8));
	return (*(int *)box);
}

static int	ft_wall_is_hit(t_env *env)
{
	if (env->ray.mapX < 0 || env->ray.mapY < 0)
		return (YES);
	if (env->ray.mapX >= env->mapw || env->ray.mapY >= env->maph)
		return (YES);
	if(env->map[env->ray.mapX][env->ray.mapY] > '0')
		return (YES);
	return (NO);
}

static void	ft_set_steps(t_env *env)
{
	env->ray.stepX = 1;
	env->ray.stepY = 1;
	if(env->ray.raydir.x < 0)
		env->ray.stepX = -1;
	if(env->ray.raydir.y < 0)
		env->ray.stepY = -1;
}

static double	ft_get_oppside(t_env *env, t_vic sidedist)
{
	ft_set_steps(env);
	while (ft_wall_is_hit(env) == NO)
	{
		if(sidedist.x < sidedist.y)
		{
			sidedist.x += env->ray.deltadist.x;
			env->ray.mapX += env->ray.stepX;
			env->ray.side = 0;
		}
		else
		{
			sidedist.y += env->ray.deltadist.y;
			env->ray.mapY += env->ray.stepY;
			env->ray.side = 1;
		}
	}
	if(env->ray.side == 0)
		return (sidedist.x - env->ray.deltadist.x);
	return (sidedist.y - env->ray.deltadist.y);
}

static void	ft_set_sidedist(t_env *env, t_vic raydir)
{
	env->ray.sidedist.x = 0;
	env->ray.sidedist.y = 0;
	if (raydir.x < 0)
		env->ray.sidedist.x = (env->px - env->ray.mapX) * env->ray.deltadist.x;
	else
		env->ray.sidedist.x = (env->ray.mapX + 1.0 - env->px) * env->ray.deltadist.x;
	if (raydir.y < 0)
		env->ray.sidedist.y = (env->py - env->ray.mapY) * env->ray.deltadist.y;
	else
		env->ray.sidedist.y = (env->ray.mapY + 1.0 - env->py) * env->ray.deltadist.y;
	if (env->ray.sidedist.x == 0)
		env->ray.sidedist.x = 0.1;
	if (env->ray.sidedist.y == 0)
		env->ray.sidedist.y = 0.1;
}

static void	ft_set_line_height(t_env *env)
{
	env->ray.deltadist.x = 1e30;
	env->ray.deltadist.y = 1e30;
	if (env->ray.raydir.x != 0)
		env->ray.deltadist.x = fabs(1 / env->ray.raydir.x);
	if (env->ray.raydir.y != 0)
		env->ray.deltadist.y = fabs(1 / env->ray.raydir.y);
	ft_set_sidedist(env, env->ray.raydir);
	env->ray.oppside = ft_get_oppside(env, env->ray.sidedist);
	env->ray.line_height = env->winh / env->ray.oppside;
}

static void	ft_set_raydir(t_env *env, int col)
{
	double const	cameraX = 2 * (col) / (double)env->winw - 1;

	env->ray.raydir.x = env->ray.dirX + env->ray.planeX * cameraX;
	env->ray.raydir.y = env->ray.dirY + env->ray.planeY * cameraX;
}

static int	ft_get_texx(t_env *env)
{
	double	wallX; //where exactly the wall was hit
	int		texx;

	if(env->ray.side == 0)
		wallX = env->py + env->ray.oppside * env->ray.raydir.y;
	else
	  	wallX = env->px + env->ray.oppside * env->ray.raydir.x;
	wallX -= floor((wallX));
	texx = (int)(wallX * (double)(env->img[NORTH].imgw));
	if(env->ray.side == 0 && env->ray.raydir.x > 0)
		texx = env->img[NORTH].imgh - texx - 1;
	if(env->ray.side == 1 && env->ray.raydir.y < 0)
		texx = env->img[NORTH].imgw - texx - 1;
	return (texx);
}

static void	ft_setup_drawing(t_env *env, int col)
{
	env->ray.mapX = (int)(env->px);
	env->ray.mapY = (int)(env->py);
	ft_set_raydir(env, col);
	ft_set_line_height(env);
	env->ray.draw_start = -(env->ray.line_height) / 2 + (env->winh) / 2;
	if(env->ray.draw_start < 0)
		env->ray.draw_start = 0;
	env->ray.draw_end = env->ray.line_height / 2 + (env->winh) / 2;
	if(env->ray.draw_end >= (env->winh))
		env->ray.draw_end = (env->winh) - 1;
}

static int	ft_draw_wall(t_env *env, int col, int row)
{
	double	texPos;
	int		color;
	int		step;
	t_point	tex;

	tex.x = ft_get_texx(env);
	step = (1.0 * env->img[NORTH].imgh / (env->ray.line_height));
	texPos = (double)((env->ray.draw_start - (env->winh) / 2 + (env->ray.line_height) / 2) * step);
	while (row < env->ray.draw_end)
	{
		tex.y = (int)texPos & (env->img[NORTH].imgh - 1);
		texPos += step;
		color = ft_get_tex_pixel(env, tex);
		// // pas obligatoire de laisser ca je pense, nan ?
		// if(env->ray.side == 1)
		// 	color = (color >> 1) & 8355711;
		ft_pixel_put(env, col, row, color);
		(row) = (row) + 1;
	}
	return (row);
}

void	ft_draw_stripe(t_env *env, int col)
{
	double	step;
	double	texPos;
	int		row;
	int		color;

	ft_setup_drawing(env, col);
	if (env->ray.draw_start > env->winh || env->ray.draw_end < 0)
		return ;
	row = 0;
	color = ft_rgb_to_int(env->file.colors[CEIL]);
	while (row < env->ray.draw_start)
	{
		ft_pixel_put(env, col, row, color);
		row++;
	}
	row = ft_draw_wall(env, col, row);
	color = ft_rgb_to_int(env->file.colors[FLOOR]);
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
	else if (env->up)
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
	else if (env->right)
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
	else if (env->rotright)
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
		ft_draw_stripe(env, col);
		col++;
	}
	if (env->mlx_ptr && env->win_ptr && env->img[CANVAS].mlx_img)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[CANVAS].mlx_img, 0, 0);
	return (0);
}








