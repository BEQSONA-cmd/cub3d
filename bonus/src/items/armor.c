/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   armor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:06:38 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:23:41 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_armor(t_cube *c)
{
	t_item	*item;

	item = (t_item *)ft_calloc(sizeof(t_item), 1);
	item->name = "Boots of speed";
	item->fontSize = 0.37;
	item->use = &equip;
	item->props.id = 37;
	item->props.slot = BOOTS;
	item->props.effect = 10;
	c->items[37] = *item;
}
