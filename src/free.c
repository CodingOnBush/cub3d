/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:46 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 15:42:49 by momrane          ###   ########.fr       */
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
	i = 0;
	while (file->texpath[i] != NULL)
	{
		free(file->texpath[i]);
		i++;
	}
	if (file->texpath != NULL)
		free(file->texpath);
}

static void	ft_free_win(t_win *win)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		// if (win->img[i].mlx_img != NULL)
		// 	mlx_destroy_image(win->mlx_ptr, win->img[i].mlx_img);
		if (win->img[i].path != NULL)
			free(win->img[i].path);
		i++;
	}
	if (win->mlx_ptr != NULL)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr != NULL)
		free(win->mlx_ptr);
}

void	ft_free_env(t_env *env)
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
	ft_free_file(&env->file);
	ft_free_win(&env->win);
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
