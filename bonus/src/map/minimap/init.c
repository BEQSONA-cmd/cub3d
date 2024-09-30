/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:13:57 by escura            #+#    #+#             */
/*   Updated: 2024/09/29 18:09:18 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_init(void)
{
	t_minimap	*minimap;

	minimap = ft_malloc(sizeof(t_minimap));
	minimap->x = WIDTH - MINIMAP_PIXEL_WIDTH - 10;
	minimap->y = HEIGHT - MINIMAP_PIXEL_HEIGHT - 10;
	minimap->center_x = minimap->x + MINIMAP_PIXEL_WIDTH / 2;
	minimap->center_y = minimap->y + MINIMAP_PIXEL_HEIGHT / 2;
	minimap->last_x = minimap->x + MINIMAP_PIXEL_WIDTH;
	minimap->last_y = minimap->y + MINIMAP_PIXEL_HEIGHT;
	cube()->map->minimap = minimap;
}

void	init_square(t_square *square, float angle)
{
	square->cosangle = cos(angle);
	square->sinangle = sin(angle);
	square->color = 0;
	square->x = 0;
	square->y = 0;
}

t_minimap	*minimap(void)
{
	return (cube()->map->minimap);
}