/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:46 by momrane           #+#    #+#             */
/*   Updated: 2024/06/18 15:18:36 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_data(t_data *data)
{
	int i;

	i = 0;
	while(data->file_info[i])
	{
		free(data->file_info[i]);
		i++;
	}
	if (data->file_info)
		free(data->file_info);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
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
}
