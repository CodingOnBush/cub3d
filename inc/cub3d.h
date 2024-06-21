/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/21 14:40:27 by momrane          ###   ########.fr       */
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

# define CEIL 0
# define FLOOR 1

# define R 0
# define G 1
# define B 2

# define STOP 0	// Stop some action
# define GOON 1	// Continue some action 

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
	char	**content;
	int		width;
	int		height;
	char	*texpath[4];
	int		rgbfloor[3];
	int		rgbsky[3];
	int		colors[2][3];
	int		count;
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
	/*
	remove t_map struct and move its members to t_env
	char	**map;
	int		mapw;
	int		maph;
	int		px;
	int		py;
	*/
	t_ray	ray;
	t_win	win;
}			t_env;

/*	UTILS	*/
int		ft_err(char *str, int ret);
int		ft_splitlen(char **split);
int	ft_get_id(char *str);

/*	FREE	*/
void	ft_free_env(t_env *env);
void	ft_free_split(char **split);

/*	INIT	*/
void	ft_init_env(t_env *env);

/*	PARSING	*/
int		ft_parsing(t_env *env, char *cubfile);

#endif