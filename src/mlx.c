/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:31:33 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 16:45:32 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_load_img(t_env *env, int i)
{
	// t_img	img;

	// img = env->img[i];
	env->img[i].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[i].path, &env->img[i].imgw, &env->img[i].imgh);
	env->img[i].addr = mlx_get_data_addr(env->img[i].mlx_img, &env->img[i].bpp, &env->img[i].llen, &env->img[i].endian);
}

void	ft_load_images(t_env *env)
{
	int	i;
	t_img	*img;

	i = 0;
	while (i < 4)
	{
		img = &(env->img[i]);
		img->mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, img->path, &img->imgw, &img->imgh);
		img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->llen, &img->endian);
		i++;
	}
	// env->img[SOUTH].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[SOUTH].path, &env->img[SOUTH].imgw, &env->img[SOUTH].imgh);
	// env->img[SOUTH].addr = mlx_get_data_addr(env->img[SOUTH].mlx_img, &env->img[SOUTH].bpp, &env->img[SOUTH].llen, &env->img[SOUTH].endian);
	// env->img[WEST].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[WEST].path, &env->img[WEST].imgw, &env->img[WEST].imgh);
	// env->img[WEST].addr = mlx_get_data_addr(env->img[WEST].mlx_img, &env->img[WEST].bpp, &env->img[WEST].llen, &env->img[WEST].endian);
	// env->img[EAST].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[EAST].path, &env->img[EAST].imgw, &env->img[EAST].imgh);
	// env->img[EAST].addr = mlx_get_data_addr(env->img[EAST].mlx_img, &env->img[EAST].bpp, &env->img[EAST].llen, &env->img[EAST].endian);
	
	env->img[CANVAS].mlx_img = mlx_new_image(env->mlx_ptr, env->winw, env->winh);
	env->img[CANVAS].addr = mlx_get_data_addr(env->img[CANVAS].mlx_img, &env->img[CANVAS].bpp, &env->img[CANVAS].llen, &env->img[CANVAS].endian);
}
