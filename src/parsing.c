/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:37:40 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 07:25:26 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	err(char *msg, int ext)
{
	printf("Error: %s\n", msg);
	return (ext);
}

static int	ft_count_lines(char *file)
{
	int		fd;
	int		file_height;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	file_height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		file_height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (file_height);
}

static char	*ft_get_texture(char *file_path)
{
	int		fd;

	if (!file_path)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (perror(file_path), NULL);
	close(fd);
	return (ft_strdup(file_path));
}

static void	ft_set_color(t_data *data, char **split, char c)
{	
	if (!split)
		return ;
	if (c == 'F')
	{
		data->f = malloc(sizeof(t_color));
		if (!data->f)
			return ;
		data->f->r = ft_atoi(split[1]);
		data->f->g = ft_atoi(split[2]);
		data->f->b = ft_atoi(split[3]);
	}
	else if (c == 'C')
	{
		data->c = malloc(sizeof(t_color));
		if (!data->c)
			return ;
		data->c->r = ft_atoi(split[1]);
		data->c->g = ft_atoi(split[2]);
		data->c->b = ft_atoi(split[3]);
	}
}

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_check_file(char *file)
{
	int		fd;
	char	*ext;

	ext = ft_strchr(file, '.');
	if (ext == NULL)
		return (printf("Error: Wrong file extension\n"), FAILURE);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (printf("Error: Wrong file extension\n"), FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	close(fd);
	return (SUCCESS);
}

static void	ft_fill_raw(char **tab, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return ;
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		tab[i] = line;
		i++;
	}
	tab[i] = NULL;
	close(fd);
}

static int	ft_get_maxw(char **raw, int start_row, int file_height)
{
	int	maxw;
	int	len;

	maxw = 0;
	len = 0;
	while (raw[start_row] != NULL)
	{
		len = ft_strlen(raw[start_row]);
		// printf("[%d]\t[%s]\t[%d]\n", start_row, raw[start_row], len);
		if (len > maxw)
			maxw = len;
		start_row++;
	}
	return (maxw);
}

static char	*ft_alloc_and_init(int longest)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (longest + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < longest)
	{
		new_line[i] = '1';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

static void	ft_free_array(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
}

static char	**ft_create_map(t_cub3d *cub, int start_row, int file_height)
{
	char	**map;
	int		maxw;
	int		row;
	int		col;
	
	// printf("file_height = %d\n", file_height);
	maxw = ft_get_maxw(cub->data.raw, start_row, file_height);
	// printf("longest line = %d\n", maxw);
	cub->data.mapw = maxw;
	cub->data.maph = file_height - start_row;
	// printf("start_row = %d\n", start_row);
	// printf("cub->data.maph = %d\n", cub->data.maph);
	map = malloc(sizeof(char *) * (cub->data.maph + 1));
	if (!map)
		return (NULL);
	row = 0;
	while (row < cub->data.maph)
	{
		map[row] = ft_alloc_and_init(maxw);
		if (!map[row])
			return (ft_free_array(map, row), NULL);
		row++;
	}
	map[row] = NULL;
	row = 0;
	while (row < cub->data.maph)
	{
		col = 0;
		while (col < ft_strlen(cub->data.raw[start_row + row]) && cub->data.raw[start_row + row][col])
		{
			if (cub->data.raw[start_row + row][col] == 'N')
			{
				// printf("PLAYER FOUND at [%d][%d]\n", row, col);
				cub->data.px = row;
				cub->data.py = col;
				map[row][col] = '0';
			}
			else if (cub->data.raw[start_row + row][col] != ' ' && cub->data.raw[start_row + row][col] != '\n')
				map[row][col] = cub->data.raw[start_row + row][col];
			col++;
		}
		row++;
	}
	return (map);
}

static int	ft_data_is_full(t_data *data)
{
	if (data->no && data->so && data->we && data->ea && data->f && data->c)
		return (SUCCESS);
	return (FAILURE);
}

// static int	ft_splitlen(char **split)
// {
// 	int i;

// 	i = 0;
// 	while (split[i] != NULL)
// 		i++;
// 	return (i);
// }

static int	ft_parse_data(char **split, t_data *data, t_cub3d *c)
{
	char	*first;
	int		len;

	len = ft_splitlen(split);
	first = split[0];
	if (!first)
		return (SUCCESS);
	if (ft_strncmp(first, "NO", 2) == 0 && len == 2)
	{
		data->no = ft_get_texture(split[1]);
		// c->buf[0].type = NORTH;
	}
	else if (ft_strncmp(first, "SO", 2) == 0 && len == 2)
	{
		data->so = ft_get_texture(split[1]);
		// c->buf[1].type = SOUTH;
	}
	else if (ft_strncmp(first, "WE", 2) == 0 && len == 2)
	{
		data->we = ft_get_texture(split[1]);
		// c->buf[2].type = WEST;
	}
	else if (ft_strncmp(first, "EA", 2) == 0 && len == 2)
	{
		data->ea = ft_get_texture(split[1]);
		// c->buf[3].type = EAST;
	}
	else if (ft_strncmp(first, "F", 1) == 0 && len == 4)
		ft_set_color(data, split, 'F');
	else if (ft_strncmp(first, "C", 1) == 0 && len == 4)
		ft_set_color(data, split, 'C');
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_parse_assets(char **raw, int file_height, t_data *data, t_cub3d *c)
{
	char	**split;

	data->i = 0;
	while (data->i < file_height)
	{
		if (raw[data->i][0] != '\n')
		{
			split = ft_split(raw[data->i], ' ');
			if (!split)
				return (err("split failed", FAILURE));
			if (ft_parse_data(split, data, c) == FAILURE)
			{
				ft_free_split(split);
				break;
			}
			ft_free_split(split);
		}
		data->i++;
	}
	if (ft_data_is_full(data) == FAILURE)
		return (err("data is not full", FAILURE));
	return (SUCCESS);
}

static void	print_file_info(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("[%d]\t[%s]\n", i, arr[i]);
		i++;
	}
}

int	ft_parsing(t_cub3d *cub, int ac, char **av)
{
	int		file_height;
	char	*test;

	if (ac != 2)
		return (printf("Error: Wrong number of arguments\n"), FAILURE);
	if (ft_check_file(av[1]) == FAILURE)
		return (FAILURE);
	file_height = ft_count_lines(av[1]);
	cub->data.raw = malloc(sizeof(char *) * (file_height + 1));
	if (!cub->data.raw)
		return (FAILURE);
	ft_fill_raw(cub->data.raw, av[1]);
	if (ft_parse_assets(cub->data.raw, file_height, &(cub->data), cub) == FAILURE)
	{
		printf("Error: Parsing assets failed\n");
		ft_free_array(cub->data.raw, file_height);
		return (FAILURE);
	}
	cub->data.map = ft_create_map(cub, cub->data.i, file_height);
	if (!cub->data.map)
	{
		printf("Error: Map creation failed\n");
		ft_free_array(cub->data.raw, file_height);
		return (FAILURE);
	}
	return (SUCCESS);
}
