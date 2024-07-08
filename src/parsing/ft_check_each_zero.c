/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_each_zero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:10:10 by momrane           #+#    #+#             */
/*   Updated: 2024/07/08 18:22:09 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check_each_zero(t_env *env)
{
	int	col;
	int	row;

	col = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph)
		{
			if (env->map[col][row] == '0')
			{
				if (ft_flood_fill(env, col, row) == FAILURE)
					return (FAILURE);
			}
			row++;
		}
		col++;
	}
	return (SUCCESS);
}
