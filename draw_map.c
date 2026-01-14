/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:11 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/14 16:29:29 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_line(t_img *img, int x, int y, int len, int color)
{
	int	i;

	i = 0;
	while(i < len)
	{
		my_mlx_pixel_put(img, x, y + i, color);
		i++;
	}
}

static void	draw_horizontal_line(t_img *img, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while(i < len)
	{
		my_mlx_pixel_put(img, x + i, y, color);
		i++;
	}
}

static void draw_tile(t_img *img, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while(i < TILE)
    {
        j = 0;
        while(j < TILE)
        {
            my_mlx_pixel_put(img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_game *game)
{
    int x;
    int y;

    // Curăță buffer-ul
    x = 0;
    while(x < MAP_WIDTH * TILE)
    {
        y = 0;
        while(y < MAP_HEIGHT * TILE)
        {
            my_mlx_pixel_put(&game->map_img, x, y, 0x00333333);
            y++;
        }
        x++;
    }

    // Desenează tile-urile
    x = 0;
    while(x < MAP_WIDTH)
    {
        y = 0;
        while(y < MAP_HEIGHT)
        {
            if(map[y][x] == 1)
                draw_tile(&game->map_img, x * TILE, y * TILE, 0x00FFFFFF);
            y++;
        }
        x++;
    }

    // Desenează grid-ul
    x = 0;
    while (x < MAP_WIDTH)
    {
        y = 0;
        while (y < MAP_HEIGHT)
        {
            draw_vertical_line(&game->map_img, (x + 1) * TILE - 1, y * TILE, TILE, 0xFF000000);
            draw_horizontal_line(&game->map_img, x * TILE, (y + 1) * TILE - 1, TILE, 0xFF000000);
            y++;
        }
        x++;
    }
}
