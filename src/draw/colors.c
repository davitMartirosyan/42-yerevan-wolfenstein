/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:44:50 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/24 19:24:03 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb(char *txt)
{
	int		i;
	char	*copy;
	char	**split;

	copy = ft_strdup(txt);
	i = -1;
	while (copy[++i])
		if (!ft_isdigit(copy[i]))
			copy[i] = 2;
	split = ft_split(copy, 2);
	i = (ft_atoi(split[0]) << 16) | (ft_atoi(split[1]) << 8)
		| ft_atoi(split[2]);
	free_char_pp(&split);
	free(copy);
	return (i);
}

void	mpp(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	rgb_tohex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	set_rgb(t_texture *texture, t_texel *texel, int x, int y)
{
	texel->r = texture->img[x * texture->bpp / 8 + y * texture->size];
	texel->g = texture->img[x * texture->bpp / 8 + y * texture->size + 1];
	texel->b = texture->img[x * texture->bpp / 8 + y * texture->size + 2];
}
