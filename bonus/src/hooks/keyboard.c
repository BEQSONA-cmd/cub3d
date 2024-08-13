/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:33:44 by escura            #+#    #+#             */
/*   Updated: 2024/08/13 11:48:21 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

// Existing key press function
int key_down(int keycode)
{
    if (keycode == ESC)
        exit_game(0);

    player_keydown(keycode);

    return (0);
}

// Existing key release function
int key_up(int keycode)
{
   
    player_keyup(keycode);

    return (0);
}
