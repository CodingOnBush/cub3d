/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:51:21 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 16:20:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_flood_fill(t_env *env, int px, int py)
{
	if (px < 0 || px >= env->mapw || py < 0 || py >= env->maph)
		return (FAILURE);
	if (env->map[px][py] == '1' || env->map[px][py] == 'x')
		return (SUCCESS);
	if (env->map[px][py] == '0')
		env->map[px][py] = 'x';
	else
		return (FAILURE);
	if (ft_flood_fill(env, px + 1, py) == FAILURE)
		return (FAILURE);
	if (ft_flood_fill(env, px - 1, py) == FAILURE)
		return (FAILURE);
	if (ft_flood_fill(env, px, py + 1) == FAILURE)
		return (FAILURE);
	if (ft_flood_fill(env, px, py - 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	ft_replace_map(char **map, int mapw, int maph)
{
	int	row;
	int	col;

	col = 0;
	while (col < mapw)
	{
		row = 0;
		while (row < maph)
		{
			if (map[col][row] == 'x')
				map[col][row] = '0';
			row++;
		}
		col++;
	}
}

static int	ft_check_cols(t_env *env)
{
	int	col;
	int	row;

	col = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph && ft_iswhitespace(env->map[col][row]) == YES)
			row++;
		if (row == env->maph)
			return (FAILURE);
		col++;
	}
	return (SUCCESS);
}

static int	ft_check_rows(t_env *env)
{
	int	row;
	int	col;

	row = 0;
	while (row < env->maph)
	{
		col = 0;
		if (env->map[col][row] && env->map[col][row] == '\0')
			return (ft_err("Map is not closed\n", FAILURE));
		while (col < env->mapw && env->map[col][row]
			&& env->map[col][row] == ' ')
			col++;
		if (col == env->mapw)
			return (FAILURE);
		row++;
	}
	return (SUCCESS);
}

int	ft_map_is_closed(t_env *env)
{
	int const	px = env->px;
	int const	py = env->py;

	if (ft_check_rows(env) == FAILURE)
		return (ft_err("Empty line in map\n", FAILURE));
	if (ft_check_cols(env) == FAILURE)
		return (ft_err("Map is not closed COLS\n", FAILURE));
	if (ft_flood_fill(env, px, py) == FAILURE)
		return (ft_err("Map is not closed\n", FAILURE));
	ft_replace_map(env->map, env->mapw, env->maph);
	return (SUCCESS);
}
