/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:31:33 by momrane           #+#    #+#             */
/*   Updated: 2024/06/27 09:30:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_load_textures(t_env *env)
{
	t_img	*img;
	int		i;

	i = 0;
	while (i < 4)
	{
		img = &(env->img[i]);
		img->mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, img->path,
				&img->imgw, &img->imgh);
		if (img->mlx_img == NULL)
			return (FAILURE);
		img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->llen,
				&img->endian);
		if (img->addr == NULL)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_load_images(t_env *env)
{
	if (ft_load_textures(env) == FAILURE)
		return (FAILURE);
	env->img[CANVAS].mlx_img = mlx_new_image(env->mlx_ptr, env->winw,
			env->winh);
	if (env->img[CANVAS].mlx_img == NULL)
		return (FAILURE);
	env->img[CANVAS].addr = mlx_get_data_addr(env->img[CANVAS].mlx_img,
			&env->img[CANVAS].bpp, &env->img[CANVAS].llen,
			&env->img[CANVAS].endian);
	if (env->img[CANVAS].addr == NULL)
		return (FAILURE);
	return (SUCCESS);
}
