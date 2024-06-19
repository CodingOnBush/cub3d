/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:46 by momrane           #+#    #+#             */
/*   Updated: 2024/06/19 17:18:04 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_data(t_data *data)
{
	
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
