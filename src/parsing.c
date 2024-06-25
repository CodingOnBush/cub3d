/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:14:09 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 16:41:58 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"

static int	ft_check_file(char *file)
{
	int		fd;
	char	*ext;

	ext = ft_strchr(file, '.');
	if (!ext)
		return (ft_err("No file extension", FAILURE));
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (ft_err("Invalid file extension", FAILURE));
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
		return (perror(file), FAILURE);
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

static int	ft_get_all_lines(t_env *env, char *cubfile)
{
	int	fd;
	int	row;
	int	len;

	fd = open(cubfile, O_RDONLY);
	if (fd == -1)
		return (perror(cubfile), FAILURE);
	env->file.height = ft_count_lines(cubfile);
	env->file.content = (char **)malloc(sizeof(char *) * (env->file.height
				+ 1));
	if (!env->file.content)
		return (FAILURE);
	row = 0;
	while (row < env->file.height)
	{
		env->file.content[row] = get_next_line(fd);
		len = ft_strlen(env->file.content[row]);
		if (len > 0 && env->file.content[row][len - 1] == '\n')
			env->file.content[row][len - 1] = '\0';
		// printf("line = [%s]\n", env->file.content[row]);
		row++;
	}
	env->file.content[row] = NULL;
	close(fd);
	return (SUCCESS);
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

static int	ft_get_infos(t_env *env, char **split)
{
	// printf("split %p\n", split);
	if (!split)
		return (GOON);
	if (!split[0] && env->file.count == 6)
		return (ft_free_split(split), STOP);
	if (!split[0])
		return (ft_free_split(split), GOON);
	if (ft_splitlen(split) == 2 && ft_get_id(split[0]) != -1)
	{
		env->img[ft_get_id(split[0])].path = ft_strdup(split[1]);
		env->file.count++;
	}
	else if (ft_splitlen(split) == 4 && ft_get_id(split[0]) == CEIL || ft_get_id(split[0]) == FLOOR)
	{
		env->file.colors[ft_get_id(split[0])][R] = ft_atoi(split[1]);
		env->file.colors[ft_get_id(split[0])][G] = ft_atoi(split[2]);
		env->file.colors[ft_get_id(split[0])][B] = ft_atoi(split[3]);
		env->file.count++;
	}
	else
		return (ft_free_split(split), STOP);
	return (ft_free_split(split), GOON);
}

static int	ft_get_map(t_env *env, char *line)
{
	// printf("line = [%s]\n", line);
	int	mapw;
	int	len;

	mapw = 0;
	while (line[mapw])
		mapw++;
	return (SUCCESS);
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
	char	**cpy;
	int		row;
	int		col;

	env->map = (char **)malloc(sizeof(char *) * env->mapw);
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
			printf("[%c]", map[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}
}

static void	ft_set_mapsizes(t_env *env, char **content)
{
	if (!content || !*content)
		return ;
	// printf("content = [%s]\n", *content);
	while (**content == '\n')
		content++;
	while (*content != NULL)
	{
		if (ft_strlen(*content) > env->mapw)
			env->mapw = ft_strlen(*content);
		content++;
		env->maph++;
	}
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

static int	ft_analyze_file(t_env *env)
{
	char	**content;
	char	**split;

	content = env->file.content;
	while (*content != NULL)
	{
		split = ft_split(*content, ' ');
		if (ft_get_infos(env, split) == STOP)
			break ;
		// printf("CONTENT = [%s]\n", *content);

		content++;
	}
	if (env->file.count != 6)
		return (ft_err("Wrong infos about game", FAILURE));
	ft_set_mapsizes(env, content);
	// printf("mapw = [%d], maph = [%d]\n", env->mapw, env->maph);
	if (env->mapw == 0 || env->maph == 0)
		return (ft_err("Map empty", FAILURE));
	if (env->mapw < 3 || env->maph < 3)
		return (ft_err("Map too small", FAILURE));
	if (ft_create_map(env) == FAILURE)
		return (FAILURE);
	ft_fill_map(env, content);
	return (SUCCESS);
}

static int	ft_check_map(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	if (map == NULL || map[0] == NULL)
		return (ft_err("Map empty", FAILURE));
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

static int	ft_find_player(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	col = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph)
		{
			if (ft_strchr("NSEW", map[col][row]) != NULL)
			{
				env->px = col + 0.5;
				env->py = row + 0.5;
				env->pdir = map[col][row];
				map[col][row] = '0';
				ft_update_dir(env);
				return (SUCCESS);
			}
			row++;
		}
		col++;
	}
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

static int	ft_check_col(char **map, int col, int maph)
{
	int	row;

	row = 0;
	while (row < maph && map[col][row] == ' ')
		row++;
	if (row == maph)
		return (SUCCESS);
	if (map[col][row] != '1')
		return (FAILURE);
	else if (map[col][row] == '1')
		return (SUCCESS);
	return (SUCCESS);
}

static int	ft_check_row(char **map, int row, int mapw)
{
	int	col;

	col = 0;
	while (col < mapw && map[col][row] == ' ')
		col++;
	if (col == mapw)
		return (SUCCESS);
	if (map[col][row] != '1')
		return (FAILURE);
	else if (map[col][row] == '1')
		return (SUCCESS);
	return (SUCCESS);
}

static int	ft_map_is_closed(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	col = 0;
	while (col < env->mapw)
	{
		if (ft_check_col(map, col, env->maph) == FAILURE)
			return (ft_err("Map is not closed", FAILURE));
		col++;
	}
	row = 0;
	while (row < env->maph)
	{
		if (ft_check_row(map, row, env->mapw) == FAILURE)
			return (ft_err("Map is not closed", FAILURE));
		row++;
	}
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
	if (ft_check_map(env) == FAILURE)
		return (FAILURE);
	
	// ft_print_file_infos(env);
	
	if (ft_find_player(env) == FAILURE)
		return (FAILURE);
	
	// printf("px = [%f], py = [%f]\n", env->px, env->py);
	
	if (ft_check_textures(env) == FAILURE)
		return (FAILURE);
	
	// ft_print_map(env);
	
	if (ft_map_is_closed(env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
