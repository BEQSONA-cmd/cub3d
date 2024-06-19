/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 11:58:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define COLOR 0x00FFFF00

void draw_line(int len)
{
	const t_cube *c = cube();
	const t_player *p = player();

	int x1 = p->x_px;
	int y1 = p->y_px;
	int x2 = p->x_px + p->x_dir * len;
	int y2 = p->y_px + p->y_dir * len;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		mlx_pixel_put(c->mlx, c->win, x1, y1, COLOR);

		if (x1 == x2 && y1 == y2)
			break;

		int e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}



void	draw_player()
{
	const t_cube *c = cube();
	const t_player *p = player();
	int	i;

	i = 0;
	movement();
	while (i < 5)
	{
		mlx_pixel_put(c->mlx, c->win, p->x_px + i - 2.5, p->y_px - 		2.5, 0x00FF0000);
		mlx_pixel_put(c->mlx, c->win, p->x_px - 	2.5, p->y_px + i - 	2.5, 0x00FF0000);
		mlx_pixel_put(c->mlx, c->win, p->x_px + i - 2.5, p->y_px + 		2.5, 0x00FF0000);
		mlx_pixel_put(c->mlx, c->win, p->x_px + 	2.5, p->y_px + i - 	2.5, 0x00FF0000);
		i++;
	}
}

int	draw(t_cube *c)
{
	int		i;
	int		j;
	void *wall = load_image("assets/Square.xpm");

	usleep(16666);
	clean_window();

	i = 0;
	j = 0;
	while (i < c->map->height)
	{
		j = 0;
		while (j < c->map->width)
		{
			if (c->map->map[i][j] == '1')
				draw_image(wall, j * BLOCK_SIZE, i * BLOCK_SIZE);
			j++;
		}
		i++;
	}

	draw_player();
	draw_line((float)100);
	
	destroy_image(wall);
	return (0);
}

void	start_game(void)
{
	t_cube	*c;
	t_player *p;

	c = cube();
	print_map_info();
	
	c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");

	init_hooks();
}
