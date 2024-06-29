/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/29 19:44:15 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_env *env, int c, int r, int color)
{
	t_img const	img = env->img[CANVAS];
	void		*box;

	if (c < 0 || c >= env->winw || r < 0 || r >= env->winh)
		return ;
	box = img.addr + (r * img.llen + c * (img.bpp / 8));
	*(unsigned int *)box = color;
}

int	ft_get_tex_pixel(t_env *e, int texX, int texY, int wall)
{
	t_img const		tex = e->img[wall];
	void			*pixel_addr;

	if (texX < 0 || texX >= tex.imgw || texY < 0 || texY >= tex.imgh)
		return (0);
	pixel_addr = tex.addr + (texY * tex.llen + texX * (tex.bpp / 8));
	return (*(int *)pixel_addr);
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

static int	ft_get_line_height(t_env *env)
{
	int		line_height;
	// t_vic	sidedist;

	env->ray.deltadist.x = 1e30;
	env->ray.deltadist.y = 1e30;
	if (env->ray.raydir.x != 0)
		env->ray.deltadist.x = fabs(1 / env->ray.raydir.x);
	if (env->ray.raydir.y != 0)
		env->ray.deltadist.y = fabs(1 / env->ray.raydir.y);
	ft_set_sidedist(env, env->ray.raydir);
	env->ray.oppside = ft_get_oppside(env, env->ray.sidedist);
	line_height = env->winh / env->ray.oppside;
	return (line_height);
}

static void	ft_set_raydir(t_env *env, int col)
{
	double const	cameraX = 2 * (col) / (double)env->winw - 1;

	env->ray.raydir.x = env->ray.dirX + env->ray.planeX * cameraX;
	env->ray.raydir.y = env->ray.dirY + env->ray.planeY * cameraX;
}

void	ft_draw(t_env *env, int col)
{
	// t_vic	raydir;
	int		line_height;

	env->ray.mapX = (int)(env->px);
	env->ray.mapY = (int)(env->py);
	ft_set_raydir(env, col);
	int	y;
	int	color;
	line_height = ft_get_line_height(env);
	int pitch = 100;
	int drawStart = -line_height / 2 + (env->winh) / 2 + pitch;
	if(drawStart < 0)
		drawStart = 0;
	int drawEnd = line_height / 2 + (env->winh) / 2 + pitch;
	if(drawEnd >= (env->winh))
		drawEnd = (env->winh) - 1;
	
	double wallX; //where exactly the wall was hit
	if(env->ray.side == 0)
		wallX = env->py + env->ray.oppside * env->ray.raydir.y;
	else
	  	wallX = env->px + env->ray.oppside * env->ray.raydir.x;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(env->img[NORTH].imgw));
	if(env->ray.side == 0 && env->ray.raydir.x > 0)
		texX = env->img[NORTH].imgh - texX - 1;
	if(env->ray.side == 1 && env->ray.raydir.y < 0)
		texX = env->img[NORTH].imgw - texX - 1;
	double step = 1.0 * env->img[NORTH].imgh / line_height;
	double texPos = (drawStart - pitch - (env->winh) / 2 + line_height / 2) * step;
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
		if (env->ray.side == 1)
		{
			// wall = ft_get_ew_wall(env->px, env->py, env->ray.mapX, env->ray.mapY);
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

		int color = ft_get_tex_pixel(env, texX, texY, wall);
		if(env->ray.side == 1) color = (color >> 1) & 8355711;
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
		ft_draw(env, col);
		col++;
	}
	if (env->mlx_ptr && env->win_ptr && env->img[CANVAS].mlx_img)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[CANVAS].mlx_img, 0, 0);
	return (0);
}








