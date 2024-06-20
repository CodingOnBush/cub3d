/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 23:32:59 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/inc/libft.h"
# include "../lib/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/stat.h>
# include <fcntl.h>	
# include <unistd.h>
# include <stdio.h>	
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define SUCCESS 0
# define FAILURE 1

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define M_PI 3.14159265358979323846

typedef struct s_ray
{
	double 	cameraX;
	double 	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	double	planeX;
	double	planeY;
	double	dirX;
	double	dirY;
	double	ms;
	double	rs;
	int		mapX;
	int 	mapY;
	int 	stepX;
	int 	stepY;
	int 	hit;
	int 	side;
	int 	texCol;
}			t_ray;

typedef struct s_img
{
	char	*path;
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		llen;
    int		endian;
	int		imgw;
	int		imgh;
}			t_img;

typedef struct	s_file
{
	char	**file;
	int		filew;
	int		height;
	char	*texpath[4];
	int		rgbfloor[3];
	int		rgbsky[3];
}			t_file;

typedef struct	s_map
{
	char	**map;
	int		mapw;
	int		maph;
	int		px;
	int		py;
}			t_map;

typedef struct	s_win
{
	void	*mlx;
	void	*win;
	int		winw;
	int		winh;
	t_img	img[5];
}			t_win;

typedef struct s_env
{
	t_file	file;
	t_map	map;
	t_ray	ray;
	t_win	win;
}			t_env;

/*	UTILS	*/
int		ft_err(char *str, int ret);

/*	FREE	*/
void	ft_free_env(t_env *env);

/*	INIT	*/
void	ft_init_env(t_env *env);

/*	PARSING	*/
int		ft_parsing(t_env *env, char *cubfile);

#endif