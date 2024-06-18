/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:37:40 by momrane           #+#    #+#             */
/*   Updated: 2024/06/18 11:56:34 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_check_file(char *file)
{
	int		fd;
	char	*ext;

	ext = ft_strchr(file, '.');
	if (ext == NULL)
		return (printf("Error\nWrong file extension\n"), FAILURE);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (printf("Error\nWrong file extension\n"), FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	close(fd);
	return (SUCCESS);
}

int	ft_count_lines(char *file)
{
	int		fd;
	int		nb_lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	nb_lines = 0;
	while (get_next_line(fd, &line) > 0)
	{
		nb_lines++;
		free(line);
	}
	close(fd);
	return (nb_lines);
}

char **ft_fill_map(char *file, int nb_lines)
{
	int		fd;
	int		i;
	char	*line;
	char	**file_info;

	file_info = malloc(sizeof(char *) * (nb_lines + 1));
	if (!file_info)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), NULL);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		file_info[i] = line;
		i++;
	}
	file_info[i] = NULL;
	close(fd);
	return (file_info);	
}

char	*ft_get_texture(char *line)
{
	char **infos;
	char *path;
	
	infos = ft_split(line, ' ');
	if (!infos)
		return (NULL);
	if (infos[2] != NULL)
		return (free(infos), NULL);
	if (infos[1] == NULL)
		return (free(infos), NULL);
	path = ft_strdup(infos[1]);
	return (free(infos), path);
}

int	ft_parse_map(char **file_info, int nb_lines, t_data *data)
{
	int		i;

	i = 0;
	while (i < nb_lines)
	{
		if (file_info[i][0] == 'N' && file_info[i][1] == 'O')
			data->no = ft_get_texture(file_info[i]);
		else if (file_info[i][0] == 'S' && file_info[i][1] == 'O')
			data->so = ft_get_texture(file_info[i]);
		else if (file_info[i][0] == 'W' && file_info[i][1] == 'E')
			data->we = ft_get_texture(file_info[i]);
		else if (file_info[i][0] == 'E' && file_info[i][1] == 'A')
			data->ea = ft_get_texture(file_info[i]);
		// else if (file_info[i][0] == 'S')
		// 	printf("Sprite\n");
		// else if (file_info[i][0] == 'F')
		// 	printf("Floor\n");
		// else if (file_info[i][0] == 'C')
		// 	printf("Ceiling\n");
		// else if (file_info[i][0] == '1')
		// 	printf("Map\n");
		// else
		// 	return (printf("Error\nInvalid map\n"), FAILURE);
		i++;
	}
}

int	ft_parsing(int ac, char **av)
{
	int		nb_lines;
	char	**file_info;
	t_data	*data;
	
	printf("Start parsing\n");
	if (ac != 2)
		return (printf("Error\nWrong number of arguments\n"), FAILURE);
	if (ft_check_file(av[1]) == FAILURE)
		return (FAILURE);
	nb_lines = ft_count_lines(av[1]);
	data->file_info = ft_fill_map(av[1], nb_lines);
	if (ft_parse_map(av[1], nb_lines, data) == FAILURE)
		return (FAILURE);
	free_data(data);
	return (SUCCESS);
}
