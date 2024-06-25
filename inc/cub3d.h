/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 16:43:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
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

#include <math.h>
#include <stdbool.h>

# define SUCCESS 0
# define FAILURE 1

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define CANVAS 4

# define CEIL 0
# define FLOOR 1

# define R 0
# define G 1
# define B 2

# define STOP 0	// Stop some action
# define GOON 1	// Continue some action 

# define M_PI 3.14159265358979323846

// # define KeyPressMask 1L<<0
// # define KeyReleaseMask 1L<<1


typedef struct s_ray
{
	double 	cameraX;
	double 	rayDirX;
	double	rayDirY;
	int		mapX;
	int 	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int 	stepX;
	int 	stepY;
	int 	hit;
	int 	side;
	int 	texCol;
	double	planeX;
	double	planeY;
	double	dirX;
	double	dirY;
	double	ms;
	double	rs;
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
	int		colors[2][3];
	int		count;
}			t_file;

typedef struct s_env
{
	t_file	file;
	char	**map;
	t_img	img[5];
	void	*mlx_ptr;
	void	*win_ptr;
	int		winw;
	int		winh;
	int		mapw;
	int		maph;
	double	px;
	double	py;
	char	pdir;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rotleft;
	int		rotright;
	t_ray	ray;
}			t_env;

/*	UTILS	*/
int		ft_err(char *str, int ret);
int		ft_splitlen(char **split);
int		ft_get_id(char *str);
void	ft_update_dir(t_env *env);

/*	PARSING	*/
int		ft_parsing(t_env *env, char *cubfile);

/*	INIT	*/
void	ft_init_env(t_env *env);

/*	DRAW	*/
int		ft_render(t_env *env);

/*	HOOKS	*/
int		ft_win_cross(t_env *env);
int		ft_key_hook(int keycode, t_env *env);
int		ft_key_released(int keycode, t_env *env);
int		ft_key_pressed(int keycode, t_env *env);

/*	FREE	*/
void	ft_free_env(t_env *env);
void	ft_free_split(char **split);

/*	MLX	*/
void	ft_load_images(t_env *env);

#endif