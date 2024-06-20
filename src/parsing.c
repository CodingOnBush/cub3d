/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:37:40 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 11:50:27 by momrane          ###   ########.fr       */
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
	int		nb_lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	nb_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		nb_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb_lines);
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

static void	ft_fill_file_content(char **tab, char *file)
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

static int	ft_get_longest(char **file_content, int i, int nb_lines)
{
	int		j;
	int		longest_line;
	int		len;

	longest_line = 0;
	while (i < nb_lines)
	{
		j = 0;
		len = ft_strlen(file_content[i]);
		while (j < len && file_content[i][j] && file_content[i][j] != '\0' && file_content[i][j] != '\n')
			j++;
		if (j > longest_line)
			longest_line = j;
		i++;
	}
	return (longest_line);
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
		new_line[i] = '#';
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

static char	**ft_create_map(int i, int nb_lines, t_data *data, t_cub3d *c)
{
	char	**map;
	int		longest_line;
	int		j;
	int		k;
	
	longest_line = ft_get_longest(data->file_content, i, nb_lines);
	c->data.mapw = longest_line;
	c->data.maph = nb_lines - i;
	map = malloc(sizeof(char *) * (nb_lines - i + 1));
	if (!map)
		return (NULL);
	j = 0;
	while (j < nb_lines - i)
	{
		map[j] = ft_alloc_and_init(longest_line);
		if (!map[j])
			return (ft_free_array(map, j), NULL);
		j++;
	}
	map[j] = NULL;
	j = 0;
	while (j < nb_lines - i)
	{
		k = 0;
		while (k < ft_strlen(data->file_content[i + j]) && data->file_content[i + j][k])
		{
			if (data->file_content[i + j][k] != ' ' && data->file_content[i + j][k] != '\n')
				map[j][k] = data->file_content[i + j][k];
			k++;
		}
		j++;
	}
	return (map);
}

static int	ft_data_is_full(t_data *data)
{
	if (data->no && data->so && data->we && data->ea && data->f && data->c)
		return (SUCCESS);
	return (FAILURE);
}

static int	ft_splitlen(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

static int	ft_parse_data(char **split, t_data *data)
{
	char	*first;
	int		len;

	len = ft_splitlen(split);
	first = split[0];
	if (!first)
		return (SUCCESS);
	if (ft_strncmp(first, "NO", 2) == 0 && len == 2)
		data->no = ft_get_texture(split[1]);
	else if (ft_strncmp(first, "SO", 2) == 0 && len == 2)
		data->so = ft_get_texture(split[1]);
	else if (ft_strncmp(first, "WE", 2) == 0 && len == 2)
		data->we = ft_get_texture(split[1]);
	else if (ft_strncmp(first, "EA", 2) == 0 && len == 2)
		data->ea = ft_get_texture(split[1]);
	else if (ft_strncmp(first, "F", 1) == 0 && len == 4)
		ft_set_color(data, split, 'F');
	else if (ft_strncmp(first, "C", 1) == 0 && len == 4)
		ft_set_color(data, split, 'C');
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_parse_assets(char **file_content, int nb_lines, t_data *data, t_cub3d *c)
{
	char	**split;

	data->i = 0;
	while (data->i < nb_lines)
	{
		if (file_content[data->i][0] != '\n')
		{
			split = ft_split(file_content[data->i], ' ');
			if (!split)
				return (err("split failed", FAILURE));
			if (ft_parse_data(split, data) == FAILURE)
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
	int		nb_lines;
	char	*test;

	if (ac != 2)
		return (printf("Error: Wrong number of arguments\n"), FAILURE);
	if (ft_check_file(av[1]) == FAILURE)
		return (FAILURE);
	nb_lines = ft_count_lines(av[1]);
	cub->data.file_content = malloc(sizeof(char *) * (nb_lines + 1));
	if (!cub->data.file_content)
		return (FAILURE);
	ft_fill_file_content(cub->data.file_content, av[1]);
	if (ft_parse_assets(cub->data.file_content, nb_lines, &(cub->data), cub) == FAILURE)
	{
		printf("Error: Parsing assets failed\n");
		return (FAILURE);
	}
	cub->data.map = ft_create_map(cub->data.i, nb_lines, &(cub->data), cub);
	if (!cub->data.map)
	{
		printf("Error: Map creation failed\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
