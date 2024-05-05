/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:24:05 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 10:14:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_put_pixel(t_env *env, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= env->width || y < 0 || y >= env->height)
		return ;
	dst = env->img.img_data + (y * env->img.size_line + x * (env->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw(t_env *env)
{
	ft_parse_matrix(env, ft_convert_points);
	ft_clear_img(env);
	ft_parse_matrix(env, ft_draw_dda);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.img_ptr, 0, 0);
}
