/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:28:17 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/24 20:24:05 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*set_matrix_line(char *strline, int map_w)
{
	int	i;
	int	*map_line;

	map_line = malloc(sizeof(int) * map_w);
	i = 0;
	while (i <= map_w)
	{
		if (i < (int)ft_strlen(strline) && !ft_isspace(strline[i]))
			map_line[i] = strline[i] - '0';
		else if (i >= (int)ft_strlen(strline) || ft_isspace(strline[i]))
			map_line[i] = -1;
		i++;
	}
	return (map_line);
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

void	set_instances(t_game *game)
{
	int	i;

	i = 0;
	while (game->sdl[i])
	{
		if (contains(game->sdl[i], ".xpm"))
		{
			put_textures(game, i);
			game->news++;
		}
		else if (contains(game->sdl[i], ","))
		{
			put_colors(game, i);
			game->colors++;
		}
		else
			game->map = set_map(game->map, '\n', game->sdl[i]);
		i++;
	}
	if (game->news != 4 || game->colors != 2 || !game->north || !game->south
		|| !game->west || !game->east || !game->map)
		failure();
}

void	set_matrix(t_game *game)
{
	char	**split;

	split = ft_split(game->map, '\n');
	get_map_sizes(game, split);
	set_int_matrix(game, split);
	free_char_pp(&split);
}

void	set_int_matrix(t_game *game, char **split)
{
	int	i;

	i = -1;
	game->mmap = malloc(sizeof(int *) * game->map_h);
	if (!game->mmap)
		failure();
	while (split[++i])
		game->mmap[i] = set_matrix_line(split[i], game->map_w);
}
