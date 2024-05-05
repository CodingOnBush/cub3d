/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:24:03 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 09:41:48 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_init_img(t_env *env)
{
	if (env->mlx_ptr)
	{
		env->img.img_ptr = mlx_new_image(env->mlx_ptr, env->width, env->height);
		if (!env->img.img_ptr)
			ft_exit_error("mlx_new_image failed");
		env->img.img_data = mlx_get_data_addr(env->img.img_ptr, &env->img.bpp,
				&env->img.size_line, &env->img.endian);
		if (!(env->img.img_data))
			ft_exit_error("mlx_get_data_addr failed");
	}
}

void	ft_clear_img(t_env *env)
{
	if (env->img.img_data)
		ft_bzero(env->img.img_data, env->img.size_line * env->height);
}
