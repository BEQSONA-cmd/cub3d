/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:15:41 by escura            #+#    #+#             */
/*   Updated: 2024/09/30 16:23:46 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hide_mouse(void)
{
	const t_render	*r = render();
	const t_player	*p = player();

	if (p->mouse_hook)
	{
		mlx_mouse_hide(r->mlx, r->win);
		mlx_mouse_move(r->mlx, r->win, CENTER_WIDTH, CENTER_HEIGHT);
	}
	else
		mlx_mouse_show(r->mlx, r->win);
}