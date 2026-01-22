/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:16 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/22 17:14:59 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player_vectors(t_game *game)
{
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	game->player.plane_x = -sin(game->player.angle) * 0.66;
	game->player.plane_y = cos(game->player.angle) * 0.66;
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rot_amount;

	(void)y;
	delta_x = x - game->mouse_x;
	if (delta_x > 200 || delta_x < -200)
		delta_x = 0;
	if (delta_x != 0)
	{
		rot_amount = delta_x * 0.002;
		game->player.angle += rot_amount;
		update_player_vectors(game);
	}
	if (x < 100 || x > WINDOW_WIDTH - 100)
	{
		game->mouse_x = WINDOW_WIDTH / 2;
		mlx_mouse_move(game->mlx, game->window, game->mouse_x, WINDOW_HEIGHT / 2);
	}
	else
		game->mouse_x = x;
	return (0);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
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

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
