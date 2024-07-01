/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 11:51:30 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_get_texx(t_env *env)
{
	int		texx;
	double	wall_x;

	if (env->ray.side == 0)
		wall_x = env->py + env->ray.oppside * env->ray.raydir.y;
	else
		wall_x = env->px + env->ray.oppside * env->ray.raydir.x;
	wall_x -= floor((wall_x));
	texx = (int)(wall_x * (double)(env->img[NORTH].imgw));
	if (env->ray.side == 0 && env->ray.raydir.x > 0)
		texx = env->img[NORTH].imgh - texx - 1;
	if (env->ray.side == 1 && env->ray.raydir.y < 0)
		texx = env->img[NORTH].imgw - texx - 1;
	return (texx);
}

static void	ft_setup_drawing(t_env *env, int col)
{
	double const	camera_x = 2 * (col) / (double)env->winw - 1;

	env->ray.raydir.x = env->ray.dirX + env->ray.planeX * camera_x;
	env->ray.raydir.y = env->ray.dirY + env->ray.planeY * camera_x;
	env->ray.mapX = (int)(env->px);
	env->ray.mapY = (int)(env->py);
	ft_set_line_height(env);
	env->ray.draw_start = -(env->ray.line_height) / 2 + (env->winh) / 2;
	if (env->ray.draw_start < 0)
		env->ray.draw_start = 0;
	env->ray.draw_end = env->ray.line_height / 2 + (env->winh) / 2;
	if (env->ray.draw_end >= (env->winh))
		env->ray.draw_end = (env->winh) - 1;
}

// Pourquoi j'utilise l'imeage NORTH ici ? et pas une autre ?
// essager de remplacer les env->img[NORTH].imgh par texh
static int	ft_draw_wall(t_env *env, int col, int row, int texh)
{
	double	tex_pos;
	int		color;
	int		step;
	t_point	tex;

	tex.x = ft_get_texx(env);
	step = (1.0 * env->img[NORTH].imgh / (env->ray.line_height));
	tex_pos = (double)((env->ray.draw_start - (env->winh) / 2
				+ (env->ray.line_height) / 2) * step);
	while (row < env->ray.draw_end)
	{
		tex.y = (int)tex_pos & (env->img[NORTH].imgh - 1);
		tex_pos += step;
		color = ft_get_tex_pixel(env, tex);
		// // pas obligatoire de laisser ca je pense, nan ?
		if (env->ray.side == 1)
			color = (color >> 1) & 8355711;
		ft_pixel_put(env, col, row, color);
		(row) = (row) + 1;
	}
	return (row);
}

void	ft_draw_stripe(t_env *env, int col)
{
	double	step;
	double	tex_pos;
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
	row = ft_draw_wall(env, col, row, ft_get_texture(env).imgh);
	color = ft_rgb_to_int(env->file.colors[FLOOR]);
	while (row < env->winh)
	{
		ft_pixel_put(env, col, row, color);
		row++;
	}
}

int	ft_render(t_env *env)
{
	int			col;
	t_img const	canva = env->img[CANVAS];

	col = 0;
	if (env->down || env->right || env->left)
		ft_move(env);
	if (env->up || env->rotleft || env->rotright)
		ft_move(env);
	while (col < env->winw)
	{
		ft_draw_stripe(env, col);
		col++;
	}
	if (env->mlx_ptr && env->win_ptr && canva.mlx_img)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, canva.mlx_img, 0,
			0);
	return (0);
}
