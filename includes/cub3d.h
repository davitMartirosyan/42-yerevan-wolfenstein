/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:55:14 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/14 00:05:48 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "../libft/libft.h"

typedef struct s_vec
{
    double  x;
    double  y;
}   t_vec;

typedef struct s_player
{
    t_vec   pos;
    t_vec   dir;
    t_vec   plane;
}   t_player;

typedef struct s_game
{
    int         fd;
    int         map_h;
    int         map_w;
    int         **mmap;
    int         floor_color;
    int         ceiling_color;
    char        *north;
    char        *south;
    char        *west;
    char        *east;
    t_player    *player;
}   t_game;