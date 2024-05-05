/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:46 by momrane           #+#    #+#             */
/*   Updated: 2024/05/05 19:28:26 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_free_cube3d(t_cub3d *cub3d)
{
	if (cub3d->mlx_ptr)
	{
		if (cub3d->win_ptr)
		{
			mlx_clear_window(cub3d->mlx_ptr, cub3d->win_ptr);
			mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
		}
		mlx_destroy_display(cub3d->mlx_ptr);
		free(cub3d->mlx_ptr);
	}
}
