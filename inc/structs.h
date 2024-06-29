/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:59:43 by momrane           #+#    #+#             */
/*   Updated: 2024/06/29 10:39:49 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vec
{
	double	x;
	double	y;
}			t_vec;

typedef struct s_ray
{
	double	rayDirX;
	double	rayDirY;
	int		lineHeight;
	int		mapX;
	int		mapY;
	int		side;//was a NS or a EW wall hit?

	t_vec	raydir;

	//length of ray from current position to next x or y-side
	t_vec	sidedist;

	//length of ray from one x or y-side to next x or y-side
	t_vec	deltadist;

	
	t_vec	plane;
	t_vec	dir;
	
	double	cameraX;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		texCol;
	double	planeX;
	double	planeY;
	double	dirX;
	double	dirY;
	double	ms;
	double	rs;
	int		pitch;
	int		drawStart;
	int		drawEnd;
	double	wallx;		//where exactly the wall was hit
	double 	step;
	double texPos;
	int texY;
	int wall;
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

typedef struct s_file
{
	char	**content;
	int		width;
	int		rows;
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

#endif