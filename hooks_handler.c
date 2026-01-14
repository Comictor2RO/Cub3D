/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:16 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/14 16:25:17 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->window);
		exit(0);
	}
	if (keycode == 119 || keycode == 'w')
		game->keys[0] = 1;
	if (keycode == 115 || keycode == 's')
		game->keys[1] = 1;
	if (keycode == 97 || keycode == 'a')
		game->keys[2] = 1;
	if (keycode == 100 || keycode == 'd')
		game->keys[3] = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 'w')
		game->keys[0] = 0;
	if (keycode == 115 || keycode == 's')
		game->keys[1] = 0;
	if (keycode == 97 || keycode == 'a')
		game->keys[2] = 0;
	if (keycode == 100 || keycode == 'd')
		game->keys[3] = 0;
	return (0);
}
