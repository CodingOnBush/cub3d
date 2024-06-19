/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:46 by momrane           #+#    #+#             */
/*   Updated: 2024/06/19 17:29:51 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_data(t_data *data)
{
	int i;

	i = 0;
	if (!data)
		return ;
	if (data->file_content)
	{
		while(data->file_content[i])
		{
			free(data->file_content[i]);
			i++;
		}
		free(data->file_content);
	}
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
}

void	ft_free_cube3d(t_cub3d *c)
{
	if (!(c->mlx.mlx_ptr))
		return ;
	if (c->mlx.win_ptr)
	{
		mlx_clear_window(c->mlx.mlx_ptr, c->mlx.win_ptr);
		mlx_destroy_window(c->mlx.mlx_ptr, c->mlx.win_ptr);
	}
	mlx_destroy_display(c->mlx.mlx_ptr);
	free(c->mlx.mlx_ptr);
	free_data(&c->data);
	ft_free_sim(&c->sim);
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

void	ft_free_sim(t_sim *sim)
{
	int i;

	i = 0;
	if (!sim->map)
		return ;
	while (sim->map[i])
	{
		free(sim->map[i]);
		i++;
	}
	free(sim->map);
}