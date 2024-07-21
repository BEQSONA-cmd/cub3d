/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/07/19 19:03:49 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool touch_block(t_block *blocks, float px, float py)
{
	int i = 0;
	float x, y;

	if (!blocks)
		return false;
		
	while (blocks[i].x != -1)
	{
		x = blocks[i].x * BLOCK_SIZE;
		y = blocks[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y + BLOCK_SIZE)
			return true;
		i++;
	}
	return false;
}

bool is_touching(float px, float py)
{
	int		x = px / BLOCK_SIZE;
	int		y = py / BLOCK_SIZE;

	t_cube	*c = cube();
	if (x < 0 || y < 0 || x >= c->map->width || y >= c->map->height)
		return (true);
	if (c->map->map[y][x] == WALL)
		return (true);
    return (false);
}

void	draw_middle_line(void)
{
	const t_cube	*c = cube();
	int				i;

	i = 0;
	while (i < WIDTH)
	{
		mlx_pixel_put(c->mlx, c->win, i, HEIGHT / 2, 0x0000FF00);
		i++;
	}
}

void draw_cross_in_centre(void)
{
    const t_cube *c = cube();
    int x_center = WIDTH / 2;
    int y_center = HEIGHT / 2;
    int i = -7;

    while (i <= 7)
	{
		mlx_pixel_put(c->mlx, c->win, x_center + i, y_center, 0x0000FF00);
		mlx_pixel_put(c->mlx, c->win, x_center, y_center + i, 0x0000FF00);
		i++;
	}
}