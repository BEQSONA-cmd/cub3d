/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:13:57 by escura            #+#    #+#             */
/*   Updated: 2024/07/22 18:59:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_init(void)
{
	t_minimap	*minimap;

	minimap = ft_malloc(sizeof(t_minimap));
	minimap->size = 1.8;
	minimap->x = WIDTH - MINIMAP_PIXEL_WIDTH;
	minimap->y = 0;
	minimap->radius = MINIMAP_RADIUS / minimap->size;
	get_map()->minimap = minimap;
}

t_minimap	*minimap(void)
{
	return (get_map()->minimap);
}