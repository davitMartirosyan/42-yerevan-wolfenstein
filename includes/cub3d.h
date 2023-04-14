/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:55:14 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/14 06:53:23 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../mlx/mlx.h"
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
    int         map_h;
    int         map_w;
    int         floor_color;
    int         ceiling_color;
    int         **mmap;
    int         news;
    int         colors;
    char        **sdl;
    char        *north;
    char        *south;
    char        *west;
    char        *east;
    char        *map;
    t_player    *player;
}   t_game;


t_game  *init(void);
void    parser(t_game *game, char *filename);
char    **create_map_buffer(char *filename);
void    failure(void);
void	free_char_pp(char ***pp);
void    set_instances(t_game *game);
char	*set_map(char *s1, int delimiter, char *s2);
int     contains(char *source, char *find);
void    put_textures(t_game *game, int i);
void    put_colors(t_game *game, int i);
int     rgb(char *txt);
char    *path(char *line);