/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 16:49:52 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_draw_wall(t_env *env, int col, int start, int line_height)
{
	double const	step = 1.0 * env->img[NORTH].imgh / line_height;
	t_point			tex;
	double			texpos;
	int				pix;

	tex.x = ft_get_texx(env);
	texpos = (env->ray.start - (env->winh) / 2 + line_height / 2) * step;
	while (start < env->ray.end)
	{
		tex.y = (int)texpos & (env->img[NORTH].imgh - 1);
		texpos += step;
		pix = ft_get_texpixel(env, tex.x, tex.y);
		if (env->ray.side == 1)
			pix = (pix >> 1) & 8355711;
		ft_pixel_put(env, col, start, pix);
		start++;
	}
	return (start);
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
	while (row < env->ray.start)
		ft_pixel_put(env, col, row++, color);
	row = ft_draw_wall(env, col, env->ray.start, line_height);
	color = ft_rgb_to_int(env->file.colors[FLOOR]);
	while (row < env->winh)
		ft_pixel_put(env, col, row++, color);
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
