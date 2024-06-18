/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/18 17:24:59 by momrane          ###   ########.fr       */
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

# define SUCCESS 0
# define FAILURE 1

# define M_PI 3.14159265358979323846

extern int worldMap[24][24];

typedef struct s_img
{
    void	*mlx_img;	// what is returned by mlx_new_image()
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
	int		w;
	int		h;
}			t_img;

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

typedef struct s_sim
{
	char	**map;	// map
	int		mapw;	// map width
	int		maph;	// map height
	double	px;		// x position of the player
	double	py;		// y position of the player
}			t_sim;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

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
}			t_ray;

typedef struct s_cub3d
{
	t_mlx	mlx;
	t_img	img;
	t_img	buf;
	t_cst	cst;
	t_sim	sim;
	t_ray	ray;
}			t_cub3d;

/*	FREE	*/
void	ft_free_cube3d(t_cub3d *cub3d);

void	ft_pixel_put(t_cub3d *c, int col, int y, int color);
void	ft_draw_column(t_cub3d *c, int col, double perpWallDist);
void	ft_draw_texture(t_cub3d *c, t_img tex, int zoom);

int	ft_win_cross(t_cub3d *param);
int	ft_key_hook(int keycode, t_cub3d *c);

/*	INIT	*/
void	ft_init_cst(t_cst *cst);
void	ft_init_ray(t_ray *ray);
void	ft_init_sim(t_sim *sim);

double	ft_get_perp_wall_dist(t_cub3d *c, int col);


#endif