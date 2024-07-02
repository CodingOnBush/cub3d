/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:02:37 by momrane           #+#    #+#             */
/*   Updated: 2024/07/02 18:36:57 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_file_extension(char *file, char *ext)
{
	char	*point;

	point = ft_strrchr(file, '.');
	if (!point)
	{
		return (ft_err("No file extension", FAILURE));
	}
	if (ft_strcmp(point, ext) != 0)
		return (ft_err("Invalid file extension", FAILURE));
	return (SUCCESS);
}

int	ft_check_file(char *file)
{
	int	fd;

	if (ft_check_file_extension(file, ".cub") == FAILURE)
		return (FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_err_title();
		return (perror(file), FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
