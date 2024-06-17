/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/17 09:47:02 by allblue          ###   ########.fr       */
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
# include <fcntl.h>		// close - read - write
# include <unistd.h>	// printf - perror
# include <stdio.h>		// malloc - free - exit
# include <stdlib.h>	// strerror 
# include <string.h>
// lib math - "Toutes les fonctions de la lib math (-lm man man 3 math)""
// minilibx - "Toutes les fonctions de la MinilibX"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_img
{
    void	*mlx_img;	// what is returned by mlx_new_image()
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx;

typedef struct s_cst
{
	double	ms;
	double	rs;
	int		width;
	int		height;
	double	planeX;	//the 2d raycaster version of camera plane
	double	planeY;	//the 2d raycaster version of camera plane
	double	dirX;	//initial direction vector
	double	dirY;	//initial direction vector
}			t_cst;

typedef struct s_sim
{
	char	**map;	// map
	int		mapw;	// map width
	int		maph;	// map height
	double	px;		// x position of the player
	double	py;		// y position of the player
}		t_sim;

typedef struct s_cub3d
{
	t_mlx	mlx;
	t_img	img;
	t_cst	cst;
	t_sim	sim;
}			t_cub3d;

/*	UTILS	*/
int		ft_strcmp(char *s1, char *s2);
void	ft_free_cube3d(t_cub3d *cub3d);

/*	PARSING	*/
int		ft_parsing(int ac, char **av);

#endif