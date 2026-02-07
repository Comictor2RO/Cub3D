/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:23:18 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/07 16:25:37 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movements_up_down(t_game *game, double new_x, double new_y)
{
	if (game->keys[0])
	{
		new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->keys[1])
	{
		new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	movements_left_right(t_game *game, double new_x, double new_y)
{
	if (game->keys[2])
	{
		new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->keys[3])
	{
		new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}
