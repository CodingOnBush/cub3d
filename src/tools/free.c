/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:48:17 by momrane           #+#    #+#             */
/*   Updated: 2024/07/08 16:01:53 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free_array(char **array, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(array[i++]);
	free(array);
}

static void	ft_free_map(t_env *env)
{
	int	col;

	if (env->map != NULL)
	{
		col = 0;
		while (col < env->mapw)
		{
			free(env->map[col]);
			col++;
		}
		free(env->map);
	}
}

void	ft_free_env(t_env *env)
{
	int	i;

	i = 0;
	ft_free_map(env);
	while (i < 5)
	{
		if (env->img[i].path)
			free(env->img[i].path);
		if (env->mlx_ptr && env->img[i].mlx_img)
			mlx_destroy_image(env->mlx_ptr, env->img[i].mlx_img);
		i++;
	}
	if (env->mlx_ptr && env->win_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->mlx_ptr)
	{
		mlx_destroy_display(env->mlx_ptr);
		free(env->mlx_ptr);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
