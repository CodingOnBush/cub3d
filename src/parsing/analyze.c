/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:50:57 by momrane           #+#    #+#             */
/*   Updated: 2024/07/06 13:31:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_infos_error(t_env *env)
{
	if (ft_rgb_isvalid(env) == NO)
		return (ft_err("Invalid color", FAILURE));
	else if (env->file.count < 6)
		return (ft_err("Map infos not conform", FAILURE));
	else if (env->file.count >= 7)
		return (ft_err("Too much infos about game", FAILURE));
	return (SUCCESS);
}

static int	ft_set_mapsizes(t_env *env, char **content)
{
	int	len;

	while (*content != NULL && **content == '\0')
		content++;
	while (*(content) != NULL)
	{
		len = ft_strlen(*(content));
		if (len > env->mapw)
			env->mapw = len;
		(content)++;
		env->maph++;
	}
	if (env->mapw == 0 || env->maph == 0)
		return (ft_err("Map missing", FAILURE));
	if (env->mapw < 3 || env->maph < 3)
		return (ft_err("Map too small", FAILURE));
	return (SUCCESS);
}

static void	ft_fill_map(t_env *env, char **content)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	row = 0;
	while (row < env->maph)
	{
		col = 0;
		while (col < env->mapw && content[row][col] != '\0')
		{
			map[col][row] = content[row][col];
			col++;
		}
		row++;
	}
}

static int	ft_create_map(t_env *env)
{
	int	row;
	int	col;

	env->map = (char **)malloc(sizeof(char *) * (env->mapw));
	if (!env->map)
		return (FAILURE);
	col = 0;
	while (col < env->mapw)
	{
		env->map[col] = malloc(sizeof(char) * env->maph);
		if (!env->map[col])
			return (ft_free_array(env->map, col), FAILURE);
		row = 0;
		while (row < env->maph)
		{
			env->map[col][row] = ' ';
			row++;
		}
		col++;
	}
	return (SUCCESS);
}

void ft_print_split(char **split)
{
	int i = 0;
	int j = 0;

	while (split[i] != NULL)
	{
		printf("%s  ", split[i]);
		i++;
	}
	printf("\n");
}

static void	print_data(t_env *env)
{
	printf("north texture	: %s\n", env->img[NORTH].path);
	printf("south texture	: %s\n", env->img[SOUTH].path);
	printf("west texture	: %s\n", env->img[WEST].path);
	printf("east texture	: %s\n", env->img[EAST].path);
	printf("floor color	: %d %d %d\n", env->file.colors[FLOOR][R], env->file.colors[FLOOR][G], env->file.colors[FLOOR][B]);
	printf("ceil color	: %d %d %d\n", env->file.colors[CEIL][R], env->file.colors[CEIL][G], env->file.colors[CEIL][B]);
}

int	ft_analyze_file(t_env *env)
{
	char	**content;
	char	**split;

	content = env->file.content;
	while (*(content) != NULL)
	{
		if (ft_gettype(*content) == CEIL || ft_gettype(*content) == FLOOR)
			split = ft_splitmore(*content, " ,");
		else
			split = ft_splitmore(*content, " ");
		if (ft_get_infos(env, split) == STOP)
			break ;
		content++;
	}

	/*
	fill these variables:
		env->img[NORTH].path
		env->img[SOUTH].path
		env->img[WEST].path
		env->img[EAST].path
		env->file.colors[FLOOR]
		env->file.colors[CEIL]
	*/
	
	print_data(env);
	
	if (ft_field_empty(env) == YES)
		return (ft_err("A field is missing", FAILURE));
	if (ft_check_infos_error(env) == FAILURE)
		return (FAILURE);
	

	// MAP CREATION
	if (ft_set_mapsizes(env, content) == FAILURE)
		return (FAILURE);
	if (ft_create_map(env) == FAILURE)
		return (FAILURE);
	ft_fill_map(env, content);
	return (SUCCESS);
}
