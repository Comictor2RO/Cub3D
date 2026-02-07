/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:37:56 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/07 18:05:52 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>

#define TILE            32
#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   512
#define MOVE_SPEED      1.33
#define ROT_SPEED       0.075
#define PI              3.14159
#define NUM_RAYS        1024
#define MINIMAP_WIDTH   320

extern int	map[10][10];

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
	char	*path;
}	t_texture;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		hex;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_cub
{
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_west;
	t_texture	tex_east;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	int			fd;
}	t_cub;

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
	t_cub		*cub;
	int			keys[4];
	int			mouse_x;
	int			mouse_y;
}	t_game;

/* Drawing functions */
void	draw_map(t_game *game);
int		check_collision(t_game *game, double x, double y);
void	draw_circle(t_img *img, int cx, int cy, int r, int color);
void	draw_line(t_img	*img, int x1, int y1, int x2, int y2, int color);
void	draw_player_2d(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_3d_view(t_game *game);
void	draw_rays_on_minimap(t_game *game);

/* Input handlers */
int		handle_key(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
int		handle_mouse_move(int x, int y, t_game *game);
int		close_game(t_game *game);

/* Movements */
void	movements_up_down(t_game *game, double new_x, double new_y);
void	movements_left_right(t_game *game, double new_x, double new_y);

/* Parsing functions */
t_cub	*parse_cub_file(char *filename);
int		parse_textures(t_cub *cub, char *line);
int		parse_color_line(t_cub *cub, char *line);
int		parse_rgb(char *str, t_color *color);
int		add_map_line(t_map *map, char *line);
void	normalize_map(t_map *map);
int		find_player(t_map *map);
int		validate_map(t_map *map);
int		load_all_textures(t_game *game);
void	init_player_from_map(t_game *game);

/* Parsing utils */
char	*ft_strtrim_whitespace(char *str);
int		is_empty_line(char *line);
int		starts_with(char *str, char *prefix);
int		ends_with(char *str, char *suffix);
int		rgb_to_hex(int r, int g, int b);
int		is_map_line(char *line);

/* Error handling */
int		error_msg(char *msg);
void	*error_null(char *msg);
void	free_cub(t_cub *cub);
void	free_split(char **split);
void	cleanup_game(t_game *game);

