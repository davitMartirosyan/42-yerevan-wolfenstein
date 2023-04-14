/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:31:41 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/14 07:13:59 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	*set_map(char *s1, int delimiter, char *s2)
{
	char	*arguments;
	int		i;
	int		c;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	arguments = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!arguments)
		return (NULL);
	i = -1;
	c = -1;
	while (s1[++i])
		arguments[i] = s1[i];
	arguments[i++] = delimiter;
	while (s2[++c])
		arguments[i++] = s2[c];
	arguments[i] = '\0';
	free(s1);
	s1 = 0;
	return (arguments);
}