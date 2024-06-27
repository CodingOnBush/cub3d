/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:14:09 by momrane           #+#    #+#             */
/*   Updated: 2024/06/27 20:03:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_check_file_extension(char *file, char *ext)
{
	char	*point;

	point = ft_strrchr(file, '.');
	if (!point)
	{
		printf("file = [%s]\n", file);
		return (ft_err("No file extension", FAILURE));
	}
	if (ft_strcmp(point, ext) != 0)
		return (ft_err("Invalid file extension", FAILURE));
	return (SUCCESS);
}

static int	ft_check_file(char *file)
{
	int		fd;

	if (ft_check_file_extension(file, ".cub") == FAILURE)
		return (FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	close(fd);
	return (SUCCESS);
}

static int	ft_count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), -1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static void	ft_remove_spaces_at_end(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = ' ';
	while (len > 0 && line[len - 1] == ' ')
	{
		line[len - 1] = '\0';
		len--;
	}
}

static int	ft_get_all_lines(t_env *env, char *cubfile)
{
	int	fd;
	int	row;
	int	len;

	fd = open(cubfile, O_RDONLY);
	if (fd == -1)
		return (perror(cubfile), FAILURE);
	env->file.height = ft_count_lines(cubfile);
	if (env->file.height == -1)
		return (close(fd), FAILURE);
	if (env->file.height == 0)
		return (close(fd), ft_err("Empty file", FAILURE));
	env->file.content = (char **)malloc(sizeof(char *) * (env->file.height + 1));
	if (!env->file.content)
		return (close(fd), FAILURE);
	env->file.content[env->file.height] = NULL;
	row = 0;
	while (row < env->file.height)
	{
		env->file.content[row] = get_next_line(fd);
		len = ft_strlen(env->file.content[row]);
		ft_remove_spaces_at_end(env->file.content[row]);
		row++;
	}
	return (close(fd), SUCCESS);
}

static void	ft_print_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
	{
		printf("split is NULL\n");
		return ;
	}
	while (split[i])
	{
		printf("[%s] | ", split[i]);
		i++;
	}
	if (split[i] == NULL)
		printf("[NULL]");
	printf("\n\n");
}

static int	ft_is_color(char **split)
{
	int	id;

	if (!split || !*split)
		return (NO);
	id = ft_get_id(split[0]);
	if (id == CEIL || id == FLOOR)
		return (YES);
	return (NO); 
}

static int	ft_rgb_isvalid(t_env *env)
{
	if (env->file.colors[FLOOR][R] < 0 || env->file.colors[FLOOR][R] > 255)
		return (NO);
	if (env->file.colors[FLOOR][G] < 0 || env->file.colors[FLOOR][G] > 255)
		return (NO);
	if (env->file.colors[FLOOR][B] < 0 || env->file.colors[FLOOR][B] > 255)
		return (NO);
	if (env->file.colors[CEIL][R] < 0 || env->file.colors[CEIL][R] > 255)
		return (NO);
	if (env->file.colors[CEIL][G] < 0 || env->file.colors[CEIL][G] > 255)
		return (NO);
	if (env->file.colors[CEIL][B] < 0 || env->file.colors[CEIL][B] > 255)
		return (NO);
	return (YES);
}

static int	ft_get_infos(t_env *env, char **split)
{
	if (!split)
		return (ft_free_splitmore(split), GOON);
	if (!split[0])
		return (ft_free_splitmore(split), GOON);
	if (ft_get_id(split[0]) == -1)
		return (ft_free_splitmore(split), STOP);
	if (ft_splitlen(split) == 2 && ft_get_id(split[0]) != -1)
	{
		env->file.count++;
		if (env->img[ft_get_id(split[0])].path != NULL)
			return (ft_free_splitmore(split), GOON);
		env->img[ft_get_id(split[0])].path = ft_strdup(split[1]);
	}
	else if (ft_splitlen(split) == 4 && ft_is_color(split) == YES)
	{
		env->file.colors[ft_get_id(split[0])][R] = ft_atoi(split[1]);
		env->file.colors[ft_get_id(split[0])][G] = ft_atoi(split[2]);
		env->file.colors[ft_get_id(split[0])][B] = ft_atoi(split[3]);
		env->file.count++;
	}
	else
		return (ft_free_splitmore(split), STOP);
	return (ft_free_splitmore(split), GOON);
}

static void	ft_print_file_infos(t_env *env)
{
	printf("NO = [%s]\n", env->img[NORTH].path);
	printf("SO = [%s]\n", env->img[SOUTH].path);
	printf("WE = [%s]\n", env->img[WEST].path);
	printf("EA = [%s]\n", env->img[EAST].path);
	printf("FLOOR = [%d, %d, %d]\n", env->file.colors[FLOOR][R], env->file.colors[FLOOR][G], env->file.colors[FLOOR][B]);
	printf("CEIL = [%d, %d, %d]\n", env->file.colors[CEIL][R], env->file.colors[CEIL][G], env->file.colors[CEIL][B]);
}

static void	ft_free_array(char **array, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(array[i++]);
	free(array);
}

static int	ft_create_map(t_env *env)
{
	// char	**cpy;
	int		row;
	int		col;

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

static void	ft_print_map(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	row = 0;
	while (row < env->maph)
	{
		col = 0;
		while (col < env->mapw)
		{
			// if ((int)(env->px) == col && (int)(env->py) == row)
			// 	printf("[P]");
			// else
				printf("[%c]", map[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}
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

static int	ft_gettype(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NORTH);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SOUTH);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (EAST);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (WEST);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CEIL);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR);
	return (-1);
}

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

static int	ft_analyze_file(t_env *env)
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
	if (ft_check_infos_error(env) == FAILURE)
		return (FAILURE);
	if (ft_set_mapsizes(env, content) == FAILURE)
		return (FAILURE);
	if (ft_create_map(env) == FAILURE)
		return (FAILURE);
	ft_fill_map(env, content);
	return (SUCCESS);
}

static int	ft_check_invalid_char(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	if (map == NULL || map[0] == NULL)
		return (ft_err("Map missing", FAILURE));
	col = 0;
	row = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph)
		{
			if (ft_strchr(" 01NSEW", map[col][row]) == NULL)
				return (ft_err("Invalid character in map", FAILURE));
			row++;
		}
		col++;
	}
	return (SUCCESS);
}

static void	ft_set_player_pos(t_env *env, int col, int row, char **map)
{
	env->px = col + 0.5;
	env->py = row + 0.5;
	env->pdir = map[col][row];
	map[col][row] = '0';
	ft_update_dir(env);
}

static int	ft_find_player(t_env *env)
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

static int	ft_check_textures(t_env *env)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		// printf("path = [%s]\n", env->img[i].path);
		if (ft_check_file_extension(env->img[i].path, ".xpm") == FAILURE)
			return (FAILURE);
		if (env->img[i].path == NULL)
			return (ft_err("Missing texture", FAILURE));
		fd = open(env->img[i].path, O_RDONLY);
		if (fd == -1)
			return (perror(env->img[i].path), FAILURE);
		close(fd);
		i++;
	}
	return (SUCCESS);
}

static void	ft_remove_all_spaces_at_end(t_env *env)
{
	int	row;
	int	col;

	row = 0;
	while(row < env->maph)
	{
		col = env->mapw - 1;
		while(col >= 0 && env->map[col][row] == ' ')
		{
			env->map[col][row] = ' ';
			col--;
		}
		row++;
	}
}

static int	ft_reverse_map(t_env *env)
{
	char	**cpy;
	int		row;
	int		col;

	cpy = (char **)malloc(sizeof(char *) * (env->mapw));
	if (!cpy)
		return (FAILURE);
	col = 0;
	while (col < env->mapw)
	{
		cpy[col] = malloc(sizeof(char) * env->maph);
		if (!cpy[col])
			return (ft_free_array(cpy, col), FAILURE);
		row = 0;
		while (row < env->maph)
		{
			cpy[col][row] = env->map[env->mapw - col - 1][row];
			row++;
		}
		col++;
	}
	ft_free_array(env->map, env->mapw);
	env->map = cpy;
	ft_remove_all_spaces_at_end(env);
	return (SUCCESS);
}


int	ft_parsing(t_env *env, char *cubfile)
{
	if (ft_check_file(cubfile) == FAILURE)
		return (FAILURE);
	if (ft_get_all_lines(env, cubfile) == FAILURE)
		return (FAILURE);
	if (ft_analyze_file(env) == FAILURE)
		return (FAILURE);
	if (ft_check_invalid_char(env) == FAILURE)
		return (FAILURE);
	// ft_print_map(env);
	ft_reverse_map(env);
	// ft_print_map(env);
	if (ft_find_player(env) == FAILURE)
		return (FAILURE);
	if (ft_map_is_closed(env) == FAILURE)
		return (FAILURE);
	// if (ft_map_is_closed(env) == FAILURE)
	// 	return (FAILURE);
	if (ft_check_textures(env) == FAILURE)
		return (FAILURE);
	// printf("player pos = [%f, %f]\n", env->px, env->py);



	printf("\n\n MAAAAAAAAAAAAAAAAAAAAAAAAP \n\n");
	int row = 0;
	int col = 0;
	while (row < env->maph)
	{
		col = 0;
		printf("{%d} :\t", row);
		while (col < env->mapw)
		{
			printf("[%c]", env->map[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}

	return (SUCCESS);
}
