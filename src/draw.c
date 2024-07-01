/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 14:54:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_draw_wall(t_env *env, int col, int start, int line_height)
{
	double const	step = 1.0 * TEXH / line_height;
	int const		texx = ft_get_texx(env);
	double			texpos;
	int				pix;
	int				texy;

	texpos = (env->ray.start - (env->winh) / 2 + line_height / 2) * step;
	while (start < env->ray.end)
	{
		texy = (int)texpos & (TEXH - 1);
		texpos += step;
		pix = ft_get_texpixel(env, texx, texy);
		if (env->ray.side == 1)
			pix = (pix >> 1) & 8355711;
		ft_pixel_put(env, col, start, pix);
		start++;
	}
}

static void	ft_set_start_and_end(t_env *env, int line_height)
{
	env->ray.start = -line_height / 2 + (env->winh) / 2;
	if (env->ray.start < 0)
		env->ray.start = 0;
	env->ray.end = line_height / 2 + (env->winh) / 2;
	if (env->ray.end >= (env->winh))
		env->ray.end = (env->winh) - 1;
}

static void	ft_draw_in_range(t_env *env, int start, int end, int col, int color)
{
	while (start < end)
	{
		ft_pixel_put(env, col, start, color);
		start++;
	}
}

static void	ft_draw_stripe(t_env *env, int col)
{
	int const	line_height = ft_get_line_height(env, col);
	int			row;
	int			color;

	env->ray.start = -line_height / 2 + (env->winh) / 2;
	if (env->ray.start < 0)
		env->ray.start = 0;
	env->ray.end = line_height / 2 + (env->winh) / 2;
	if (env->ray.end >= (env->winh))
		env->ray.end = (env->winh) - 1;
	if (env->ray.start >= env->ray.end)
		return ;
	row = 0;
	color = ft_rgb_to_int(env->file.colors[CEIL]);
	ft_draw_in_range(env, 0, env->ray.start, col, color);
	ft_draw_wall(env, col, env->ray.start, line_height);
	color = ft_rgb_to_int(env->file.colors[FLOOR]);
	ft_draw_in_range(env, env->ray.end, env->winh, col, color);
}

int	ft_render(t_env *env)
{
	int	col;

	col = 0;
	if (env->down || env->up || env->left || env->right || env->rotleft
		|| env->rotright)
		ft_move(env);
	while (col < env->winw)
	{
		ft_draw_stripe(env, col);
		col++;
	}
	if (env->mlx_ptr && env->win_ptr && env->img[CANVAS].mlx_img)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
			env->img[CANVAS].mlx_img, 0, 0);
	return (0);
}
