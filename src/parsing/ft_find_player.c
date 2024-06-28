/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:06:52 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 17:07:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_set_player_pos(t_env *env, int col, int row, char **map)
{
	env->px = col + 0.5;
	env->py = row + 0.5;
	env->pdir = map[col][row];
	map[col][row] = '0';
	ft_update_dir(env);
}

int	ft_find_player(t_env *env)
{
	int		row;
	int		col;
	int		count;

	col = 0;
	count = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph)
		{
			if (ft_strchr("NSEW", env->map[col][row]) != NULL)
			{
				ft_set_player_pos(env, col, row, env->map);
				count++;
			}
			if (count > 1)
				return (ft_err("Too many players in map", FAILURE));
			row++;
		}
		col++;
	}
	if (count == 1)
		return (SUCCESS);
	return (ft_err("No player in map", FAILURE));
}
