/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_is_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:51:21 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 18:01:58 by momrane          ###   ########.fr       */
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

// static void	ft_print_col(t_env *env, int col)
// {
// 	int	row;

// 	row = 0;
// 	printf("{%d}\n", col);
// 	while (row < env->maph)
// 	{
// 		printf("[%c]\n", env->map[col][row]);
// 		row++;
// 	}
// 	printf("\n\n");
// }

// static void	ft_print_map(t_env *env)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (row < env->maph)
// 	{
// 		col = 0;
// 		while (col < env->mapw)
// 		{
// 			printf("[%c]", env->map[col][row]);
// 			col++;
// 		}
// 		printf("\n");
// 		row++;
// 	}
// }

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

// static void	ft_print(t_env *env)
// {
// 	int	row;
// 	int	col;

// 	printf("mapw = %d maph = %d\n", env->mapw, env->maph);
// 	row = 0;
// 	while (row < env->maph)
// 	{
// 		col = 0;
// 		while (col < env->mapw)
// 		{
// 			printf("[%c]", env->map[col][row]);
// 			col++;
// 		}
// 		printf("\n");
// 		row++;
// 	}
// }

static int	ft_check_cols(t_env *env)
{
	int	col;
	int	row;

	col = 0;
	while(col < env->mapw)
	{
		if (ft_col_is_empty(env, col) == NO)
			break;
		col++;
	}
	if (col == env->mapw - 1 || col == 0)
		return (SUCCESS);
	return (FAILURE);
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
		return (ft_err("Map is not closed\n", FAILURE));
	if (ft_flood_fill(env, px, py) == FAILURE)
		return (ft_err("Map is not closed\n", FAILURE));
	ft_replace_map(env->map, env->mapw, env->maph);
	return (SUCCESS);
}
