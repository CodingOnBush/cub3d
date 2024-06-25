/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 11:58:22 by momrane          ###   ########.fr       */
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

#include <math.h>
#include <stdbool.h>

/* 
# define SUCCESS 0
# define FAILURE 1
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define M_PI 3.14159265358979323846 */

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

// extern int worldMap[24][24];

/* typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
	int		w;
	int		h;
	int		type;
}			t_img; */

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx;

typedef struct s_cst
{
	double	ms;		// move speed
	double	rs;		// rotation speed
	int		width;	// window width
	int		height;	// window height
	
	double	planeX;	//the 2d raycaster version of camera plane
	double	planeY;	//the 2d raycaster version of camera plane
	double	dirX;	//initial direction vector
	double	dirY;	//initial direction vector
}			t_cst;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

typedef struct s_data
{
	char 	**raw;
	char	*no; //to free
	char	*so;
	char	*we;
	char	*ea;
	t_color	*f;
	t_color	*c;
	int		i;
	char	**map;	// map
	int		mapw;	// map width
	int		maph;	// map height
	double	px;		// x position of the player
	double	py;		// y position of the player
}			t_data;

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




/* typedef struct s_ray
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
}			t_ray; */



typedef struct	s_file
{
	char	**content;
	int		width;
	int		height;
	// char	**texpath;
	int		colors[2][3];
	int		count;
}			t_file;

typedef struct s_cub3d
{
	t_cst	cst;
	t_img	img;
	t_img	buf[4];
	t_ray	ray;
	t_data	data;
	t_mlx	mlx;
}			t_cub3d;

typedef struct s_env
{
	t_file	file;
	void	*mlx_ptr;
	void	*win_ptr;
	int		winw;
	int		winh;
	t_img	img[5];
	char	**map;
	int		mapw;
	int		maph;
	double	px;
	double	py;
	char	pdir;
	t_ray	ray;
}			t_env;

/*	INIT	*/
int	ft_init_cub3d(t_cub3d *cub);


void	ft_pixel_put(t_cub3d *cub, int c, int r, int color);

void	free_data(t_data *data);
void	ft_free_cube3d(t_cub3d *c);
void	ft_free_split(char **split);
// void	ft_free_sim(t_sim *sim);

int	ft_win_cross(t_env *env);
int	ft_key_hook(int keycode, t_cub3d *c);


int	ft_parsing(t_cub3d *cub, int ac, char **av);
int	ft_parsing2(t_env *env, char *cubfile);

void	ft_init_env(t_env *env);

int	ft_err(char *str, int ret);
int	ft_splitlen(char **split);
int	ft_get_id(char *str);

// double	ft_get_perp_wall_dist(t_cub3d *c, int col);

void	ft_draw(t_cub3d *cub, int col);

void	ft_free_env(t_env *env);
// void	ft_free_split(char **split);

int	ft_key_hook2(int keycode, t_env *env);

void	ft_draw2(t_env *env, int col);


void	ft_update_dir(t_env *env);



#endif