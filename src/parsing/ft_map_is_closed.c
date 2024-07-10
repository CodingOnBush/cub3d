/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_is_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:51:21 by momrane           #+#    #+#             */
/*   Updated: 2024/07/10 10:59:58 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_flood_fill(t_env *env, int px, int py)
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

static int	ft_col_is_empty(t_env *env, int col)
{
	int	row;

	row = 0;
	while (row < env->maph)
	{
		if (ft_iswhitespace(env->map[col][row]) == NO)
			return (NO);
		row++;
	}
	return (YES);
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
			return (ft_err("Map is not closed", FAILURE));
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
		return (ft_err("Empty line in map", FAILURE));
	if (ft_flood_fill(env, px, py) == FAILURE)
		return (ft_err("Map is not closed", FAILURE));
	if (ft_check_each_zero(env) == FAILURE)
		return (ft_err("Map is not closed", FAILURE));
	ft_reset_map(env->map, env->mapw, env->maph);
	return (SUCCESS);
}
