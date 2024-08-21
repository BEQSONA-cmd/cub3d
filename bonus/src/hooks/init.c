/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:18 by escura            #+#    #+#             */
/*   Updated: 2024/08/17 20:37:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void init_hooks(void)
{
    const t_render *r = render();
    const t_cube *c = cube();

    mlx_do_key_autorepeaton(r->mlx);
    
    mlx_hook(r->win, KeyPress, KeyPressMask, key_down, (void *)c);
    mlx_hook(r->win, KeyRelease, KeyReleaseMask, key_up, (void *)c);
    // mlx_hook(r->win, MotionNotify, PointerMotionMask, mouse_move, (void *)c);
    // mlx_hook(r->win, ButtonPress, ButtonPressMask, mouse_click, (void *)c);

    // mlx_mouse_hide(r->mlx, r->win);
}