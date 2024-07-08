/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:50:57 by momrane           #+#    #+#             */
/*   Updated: 2024/07/08 13:56:47 by momrane          ###   ########.fr       */
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

static int	ft_set_mapsizes2(t_env *env, char **content)
{
	int	len;

	// if (content && *content)
	// 	printf("*content: [%s]\n", *content);
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

static void	ft_print_content(char **content)
{
	int i = 0;

	printf("CONTENTTTTTTTTTTTTTTTTTTTTTTTTTT:\n");
	while (content[i] != NULL)
	{
		printf("%s\n", content[i]);
		i++;
	}
}

// static void	ft_fill_map(t_env *env, char **content)
// {
// 	char	**map;
// 	int		row;
// 	int		col;

// 	ft_print_content(content);
// 	map = env->map;
// 	row = 0;
// 	while (row < env->maph)
// 	{
// 		col = 0;
// 		while (col < env->mapw && content[row][col] != '\0')
// 		{
// 			map[col][row] = content[row][col];
// 			col++;
// 		}
// 		row++;
// 	}
// }

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
	printf("north texture	: [%s]\n", env->img[NORTH].path);
	printf("south texture	: [%s]\n", env->img[SOUTH].path);
	printf("west texture	: [%s]\n", env->img[WEST].path);
	printf("east texture	: [%s]\n", env->img[EAST].path);
	printf("floor color	: %d %d %d\n", env->file.colors[FLOOR][R], env->file.colors[FLOOR][G], env->file.colors[FLOOR][B]);
	printf("ceil color	: %d %d %d\n", env->file.colors[CEIL][R], env->file.colors[CEIL][G], env->file.colors[CEIL][B]);
}

// static char	**ft_jump_to_map(t_env *env)
// {
// 	char	**split;
// 	char	**content;

// 	content = env->file.content;
// 	while (*(content) != NULL)
// 	{
// 		if (ft_gettype(*content) == CEIL || ft_gettype(*content) == FLOOR)
// 			split = ft_splitmore(*content, " ,");
// 		else
// 			split = ft_splitmore(*content, " ");
// 		if (ft_get_infos(env, split) == STOP)
// 			break ;
// 		content++;
// 	}
// 	return (content);
// }

static void	ft_print_map(char **map, int mapw, int maph)
{
	int	row;
	int	col;

	row = 0;
	while (row < maph)
	{
		col = 0;
		while (col < mapw)
		{
			printf("[%c]", map[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}
}

static char	*ft_skip_empty_lines(t_env *env, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_err("Missing map", FAILURE), NULL);
	while (line != NULL)
	{
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		if (line[0] != '\0')
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

static int	ft_set_map_size(t_env *env, int fd)
{
	char	*line;
	int		empty;

	line = ft_skip_empty_lines(env, fd);
	if (!line)
		return (FAILURE);
	empty = 0;
	while (line != NULL)
	{
		env->maph++;
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		// printf("line : [%s]\n", line);
		if (line[0] == '\0')
			empty++;
		else
			empty = 0;
		if (ft_strlen(line) > env->mapw)
			env->mapw = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	env->maph = env->maph - empty;
	return (SUCCESS);
}

static char	*ft_skip_map_infos(t_env *env, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_err("Missing map", FAILURE), close(fd), NULL);
	printf("env->file.count : %d\n", env->file.count);
	while (line != NULL && env->file.count > 0)
	{
		env->file.count--;
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		// printf("line : [%s]\n", line);
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (ft_err("Missing map", FAILURE), close(fd), NULL);
	return (line);
}

static int	ft_fill_map(t_env *env, char *filepath)
{
	char	*line;
	int		fd;
	int		col;
	int		row;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (ft_err_title(), perror(filepath), FAILURE);
	line = ft_skip_map_infos(env, fd);
	row = 0;
	while (line != NULL)
	{
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		printf("line : [%s]\n", line);
		// col = 0;
		// while (col < env->mapw && line[col] != '\0')
		// {
		// 	env->map[col][row] = line[col];
		// 	col++;
		// }
		row++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), SUCCESS);
}

int	ft_analyze_file(t_env *env, char *filepath)
{
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (ft_err_title(), perror(filepath), FAILURE);
	if (ft_parse_map_infos(env, fd) == FAILURE)
		return (close(fd), FAILURE);
	if (ft_set_map_size(env, fd) == FAILURE)
		return (close(fd), FAILURE);
	close(fd);
	if (ft_create_map(env) == FAILURE)
		return (FAILURE);
	if (ft_fill_map(env, filepath) == FAILURE)
		return (FAILURE);
	ft_print_map(env->map, env->mapw, env->maph);
	return (SUCCESS);
}
