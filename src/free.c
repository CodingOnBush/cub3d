/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:46 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 23:33:22 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_free_file(t_file *file)
{
	int	i;

	if (file->file != NULL)
	{
		i = 0;
		while (file->file[i])
			free(file->file[i++]);
		free(file->file);
	}
	i = 0;
	while (file->texpath[i])
		free(file->texpath[i++]);
	free(file->texpath);
}

static void	ft_free_win(t_win *win)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (win->img[i].path != NULL)
			free(win->img[i].path);
		if (win->img[i].mlx_img != NULL)
			mlx_destroy_image(win->mlx, win->img[i].mlx_img);
		i++;
	}
	if (win->mlx != NULL)
		mlx_destroy_window(win->mlx, win->win);
	if (win->mlx != NULL)
		free(win->mlx);
}

void	ft_free_env(t_env *env)
{
	int	i;

	if (env->map.map != NULL)
	{
		i = 0;
		while (env->map.map[i])
			free(env->map.map[i++]);
		free(env->map.map);
	}
	ft_free_file(&env->file);
	ft_free_win(&env->win);
}

void	ft_free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
