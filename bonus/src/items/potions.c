/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:29:39 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_potions(t_cube *c)
{
	int					i;
	const t_fullitem	potions[] = {\
		{"Speed", 112, NULL, 3000, &consume, NULL}, \
		NULL
	};

	i = 0;
	while (potions[i].name != NULL)
	{
		c->items[potions[i].id] = *create_item(&potions[i]);
		i++;
	}
}
