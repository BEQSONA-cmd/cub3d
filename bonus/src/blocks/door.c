/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42wolfsburg.de>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/21 13:14:12 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_block	*init_block(t_map *map_info, char c)
{
	t_block	*blocks;
	int		i;
	int		j;
	int		k;
	int		count;

	map_info->blocks = NULL;
	count = count_c(map_info->map, c);
	blocks = ft_malloc(sizeof(t_block) * (count + 1));
	i = 0;
	j = 0;
	k = 0;
	while (map_info->map[i] != NULL)
	{
		j = 0;
		while (map_info->map[i][j] != '\0')
		{
			if (map_info->map[i][j] == c)
			{
				blocks[k].x = j;
				blocks[k].y = i;
				blocks[k].s_x = j;
				blocks[k].s_y = i;
				blocks[k].id = k;
				blocks[k].type = c;
				k++;
			}
			j++;
		}
		i++;
	}
	blocks[k].x = -1;
	blocks[k].y = -1;
	blocks[k].id = -1;
	blocks[k].s_x = -1;
	blocks[k].s_y = -1;
	blocks[k].type = '\0';
	return (blocks);
}

int	get_side(int x, int y, char **map)
{
	if (map[y][x - 1] == '1')
		return (1);
	else if (map[y - 1][x] == '1')
		return (2);
	else if (map[y][x + 1] == '1')
		return (3);
	else if (map[y + 1][x] == '1')
		return (4);
	return (0);
}

void	open_door(float angle, int id)
{
	static bool	opening = false;
	t_player	*p;
	t_map		*map;
	int			side;

	p = player();
	map = cube()->map;
	side = 0;
	if (id == -1)
		return ;
	if (!opening)
		opening = true;
	side = get_side(map->doors[id].s_x, map->doors[id].s_y, map->map);
	if (!side)
		return ;
	if (side == 1 && map->doors[id].x >= map->doors[id].s_x - 0.9)
		map->doors[id].x -= 0.05;
	else if (side == 2 && map->doors[id].y >= map->doors[id].s_y - 0.9)
		map->doors[id].y -= 0.05;
	else if (side == 3 && map->doors[id].x <= map->doors[id].s_x + 0.9)
		map->doors[id].x += 0.05;
	else if (side == 4 && map->doors[id].y <= map->doors[id].s_y + 0.9)
		map->doors[id].y += 0.05;
	if (side == 1 && map->doors[id].x <= map->doors[id].s_x - 0.9)
		p->opened = true;
	else if (side == 2 && map->doors[id].y <= map->doors[id].s_y - 0.9)
		p->opened = true;
	else if (side == 3 && map->doors[id].x >= map->doors[id].s_x + 0.9)
		p->opened = true;
	else if (side == 4 && map->doors[id].y >= map->doors[id].s_y + 0.9)
		p->opened = true;
	if (p->opened)
	{
		p->interact = false;
	}
}

void	close_door(float angle, int id)
{
	t_player	*p;
	t_map		*map;
	int			side;
	static bool	closing = false;

	p = player();
	map = cube()->map;
	side = 0;
	if (id == -1)
		return ;
	if (!closing)
		closing = true;
	side = get_side(map->doors[id].s_x, map->doors[id].s_y, map->map);
	if (!side)
		return ;
	if (side == 1 && map->doors[id].x <= map->doors[id].s_x)
		map->doors[id].x += 0.05;
	else if (side == 2 && map->doors[id].y <= map->doors[id].s_y)
		map->doors[id].y += 0.05;
	else if (side == 3 && map->doors[id].x >= map->doors[id].s_x)
		map->doors[id].x -= 0.05;
	else if (side == 4 && map->doors[id].y >= map->doors[id].s_y)
		map->doors[id].y -= 0.05;
	if (side == 1 && map->doors[id].x >= map->doors[id].s_x)
		p->opened = false;
	else if (side == 2 && map->doors[id].y >= map->doors[id].s_y)
		p->opened = false;
	else if (side == 3 && map->doors[id].x <= map->doors[id].s_x)
		p->opened = false;
	else if (side == 4 && map->doors[id].y <= map->doors[id].s_y)
		p->opened = false;
	if (!p->opened)
	{
		p->interact = false;
	}
}
