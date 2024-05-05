/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/05/05 19:08:48 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../lib/libft/inc/libft.h"
# include "../lib/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

// open
# include <sys/stat.h>
# include <fcntl.h>
// close - read - write
# include <unistd.h>
// printf - perror
# include <stdio.h>
// malloc - free - exit
# include <stdlib.h>
// strerror 
# include <string.h>
// lib math - "Toutes les fonctions de la lib math (-lm man man 3 math)""
// minilibx - "Toutes les fonctions de la MinilibX"

# define SUCCESS 0
# define FAILURE 1

/*	UTILS	*/
int	ft_strcmp(char *s1, char *s2);

/*	PARSING	*/
int	ft_parsing(int ac, char **av);

#endif