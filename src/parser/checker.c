/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:00:40 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/16 01:07:50 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static int      check_top_bottom(char *board);
static int      check_middle(t_game *game, char **board);
static void     set_player(t_game *game, int pos_dir);

int check_board(t_game *game, char **board)
{
    if (!check_top_bottom(board[0]))
        return (0);
    if (!check_top_bottom(board[game->map_h - 1]))
        return (0);
    if (!check_middle(game, board))
        return (0);
    return (1);
}

static int  check_middle(t_game *game, char **board)
{
    int y;
    int len;

    y = -1;
    len = 0;
    while (board[++y])
    {
        len = ft_strlen(board[y]);
        if (board[y][0] != '1' || board[y][len - 1] != '1')
            return (0);
    }
    return (1);
}

static int  check_top_bottom(char *board)
{
    int i;

    i = -1;
    while (board[++i])
    {
        if (board[i] != '1')
            return (0);
    }
    return (1);
}

void player(t_game *game)
{
    int shooter;
    int y;
    int x;
    
    y = 0;
    shooter = 0;
    while (y < game->map_h)
    {
        x = 0;
        while (x < game->map_w)
        {
            if (game->mmap[y][x] == 30 || game->mmap[y][x] == 35
                || game->mmap[y][x] == 39 || game->mmap[y][x] == 21)
            {
                game->player->pos.x = x + 1;
                game->player->pos.y = y + 1;
                set_player(game, game->mmap[y][x]);
                game->mmap[y][x] = 0;
                shooter++;
            }
            x++;
        }
        y++;
    }
    if (shooter != 1)
        failure();
}

static void    set_player(t_game *game, int pos_dir)
{
    if (pos_dir == 30) //N
    {
        game->player->dir.x = 0;
        game->player->dir.y = -1;
        game->player->plane.x = -0.66 * game->player->dir.y;
        game->player->plane.y = 0.66 * game->player->dir.x;
    }
    else if (pos_dir == 35) //S
    {
        game->player->dir.x = 0;
        game->player->dir.y = 1;
        game->player->plane.x = 0.66 * game->player->dir.y;
        game->player->plane.y = -0.66 * game->player->dir.x;
    }
    else if (pos_dir == 39) //W
    {
        game->player->dir.x = 1;
        game->player->dir.y = 0;
        game->player->plane.x = 0.66 * game->player->dir.y;
        game->player->plane.y = -0.66 * game->player->dir.x;
    }
    else if(pos_dir == 21)//E
    {
        game->player->dir.x = -1;
        game->player->dir.y = 0;
        game->player->plane.x = 0.66 * game->player->dir.y;
        game->player->plane.y = -0.66 * game->player->dir.x;
    }
}