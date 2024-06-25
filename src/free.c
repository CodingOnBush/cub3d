/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:48:17 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 13:42:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_free_file(t_file *file)
{
	int	i;

	if (file->content != NULL)
	{
		i = 0;
		while (file->content[i])
			free(file->content[i++]);
		free(file->content);
	}
}

void	ft_free_env(t_env *env)
{
	int	col;

	ft_free_file(&env->file);
	
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

	int	i;

	i = 0;
	while (i < 5)
	{
		if (env->img[i].path)
			free(env->img[i].path);
		if (env->img[i].mlx_img && env->mlx_ptr)
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
	int i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
