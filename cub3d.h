/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:37:56 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/15 15:36:15 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>

#define MAP_WIDTH       10
#define MAP_HEIGHT      10
#define TILE            32
#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   512
#define MOVE_SPEED      1.33
#define ROT_SPEED       0.075
#define PI              3.14159
#define NUM_RAYS        704
#define MINIMAP_WIDTH   320

extern int	map[MAP_WIDTH][MAP_HEIGHT];

typedef struct s_ray
{
    double camera_x;
    double dir_x;
    double dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int hit;
    int side;
    double perp_wall_dist;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

//in radiani adica 0 = drept, PI/2 = sus, Pi = stanga, 3*PI/4 = jos, 2*PI = 0.
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_player	player;
	t_img		map_img;
	int			keys[4];
}	t_game;

void	draw_map(t_game *game);
int		check_collision(double x, double y);
void	draw_circle(t_img *img, int cx, int cy, int r, int color);
void	draw_line(t_img	*img, int x1, int y1, int x2, int y2, int color);
void	draw_player_2d(t_game *game);
int		handle_key(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_3d_view(t_game *game);

