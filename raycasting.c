/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:23 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/14 16:32:11 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d_view(t_game *game)
{
	int		ray;
	double	fov;
	double	ray_angle;
	double	distance;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		y;

	ray = 0;
	fov = PI / 3; //PI / 3 = 60 de grade adica unghiul pe care il vezi cu camera
                  //merge de la -30 de grade pana la +30 de grade
	while (ray < NUM_RAYS)
	{
		ray_angle = (game->player.angle - fov / 2) + (ray * fov / NUM_RAYS);
		distance = cast_single_ray(game, ray_angle);
		distance = distance * cos(ray_angle - game->player.angle);
		wall_height = (TILE * WINDOW_HEIGHT) / distance;
		draw_start = (WINDOW_HEIGHT / 2) - (wall_height / 2);
		draw_end = (WINDOW_HEIGHT / 2) + (wall_height / 2);

		if (draw_start < 0) 
			draw_start = 0;
		if (draw_end >= WINDOW_HEIGHT) 
			draw_end = WINDOW_HEIGHT - 1;
		y = 0;
		// Cer
		while (y < draw_start)
			my_mlx_pixel_put(&game->map_img, MINIMAP_WIDTH + ray, y++, 0x87CEEB);
		// Zid
		while (y < draw_end)
			my_mlx_pixel_put(&game->map_img, MINIMAP_WIDTH + ray, y++, 0xFFFFFF);
		// Podea
		while (y < WINDOW_HEIGHT)
			my_mlx_pixel_put(&game->map_img, MINIMAP_WIDTH + ray, y++, 0x404040);
		ray++;
	}
}

double	cast_single_ray(t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;

	ray_x = game->player.x;
	ray_y = game->player.y;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	while (1)
	{
		ray_x += ray_dir_x * 0.1;
		ray_y += ray_dir_y * 0.1;

		int map_x = (int)(ray_x / TILE);
		int map_y = (int)(ray_y / TILE);

		if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
			return (1000.0);

		if (map[map_y][map_x] == 1)
		{
			double dx = ray_x - game->player.x;
			double dy = ray_y - game->player.y;
			return (sqrt(dx * dx + dy * dy));
		}
	}
}
