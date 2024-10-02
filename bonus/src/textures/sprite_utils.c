/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:56:47 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/02 13:38:14 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	find_sprite(float x, float y, int *i)
{
	const t_sprite	*sprites = cube()->map->sprites;
	int				j;

	j = 0;
	while (sprites[*i].x != -1)
	{
		if (sprites[*i].x == x && sprites[*i].y == y)
			j++;
		(*i)++;
	}
	if (j > 0)
		return (true);
	return (false);
}

void	terminate_sprite(t_sprite **sprites, int *i)
{
	(*sprites)[*i].x = -1;
	(*sprites)[*i].y = -1;
	(*sprites)[*i].frames = -1;
	(*sprites)[*i].sprite_tex = NULL;
	(*sprites)[*i].width = -1;
	(*sprites)[*i].height = -1;
	(*sprites)[*i].type = '\0';
}

void	copy_sprites(t_sprite *src, t_sprite *dst)
{
	int	i;

	i = 0;
	while (src[i].x != -1)
	{
		dst[i] = src[i];
		i++;
	}
}

void	update_sprite_pointers(t_map *map, t_sprite *new_sprites, bool facing)
{
	t_sprite	*tmp;

	if (facing)
	{
		tmp = map->facing;
		map->facing = new_sprites;
	}
	else
	{
		tmp = map->sprites;
		map->sprites = new_sprites;
	}
	ft_free(tmp);
}