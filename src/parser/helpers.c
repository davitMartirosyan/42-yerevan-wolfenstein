/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:31:41 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/15 18:45:15 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    *path(char *line)
{
    int     i;
    char    *nav;
    
    i = ft_strlen(line) - 1;
    while (i--)
        if (ft_isspace(line[i]))
            break;
    return (line + i + 1);
}

int contains(char *source, char *find)
{
    int i;
    int j;
    int k;

    i = 0;
    while (source[i])
    {
        if (source[i] == find[0])
        {
            j = 0;
            k = i;
            while (source[k] == find[j] && j < ft_strlen(find))
            {
                k++;
                j++;
            }
        }
        i++;
    }
    if (j == ft_strlen(find))
        return (1);
    return (0);
}

void    put_colors(t_game *game, int i)
{
    if (contains(game->sdl[i], "F"))
        game->floor_color = rgb(game->sdl[i]);
    else if (contains(game->sdl[i], "C"))
        game->ceiling_color = rgb(game->sdl[i]);
}

void    put_textures(t_game *game, int i)
{
    if (contains(game->sdl[i], "NO"))
        game->north = ft_strdup(game->sdl[i]);
    else if (contains(game->sdl[i], "SO"))
        game->south = ft_strdup(game->sdl[i]);    
    else if (contains(game->sdl[i], "WE"))
        game->west = ft_strdup(game->sdl[i]);
    else if (contains(game->sdl[i], "EA"))
        game->east = ft_strdup(game->sdl[i]);
}

char    **create_map_buffer(char *filename)
{
    int     fd;
    char    *line;
    char    *buffer;
    char    **split;
    
    buffer = NULL;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        failure();
    line = get_next_line(fd);
    buffer = ft_strjoin(buffer, line);
    while (line != NULL)
    {
        free(line);
        line = get_next_line(fd);
        buffer = ft_strjoin(buffer, line);
    }
    split = ft_split(buffer, '\n');
    free(line);
    free(buffer);
    close(fd);
    return (split);
}