/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:46:33 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/22 00:51:24 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     rgb(char *txt)
{
    int     i;
    char    *copy;
    char    **split;

    copy = ft_strdup(txt);
    i = -1;
    while (copy[++i])
        if (!ft_isdigit(copy[i]))
            copy[i] = 2;
    split = ft_split(copy, 2);
    i = (ft_atoi(split[0]) << 16) | (ft_atoi(split[1]) << 8) | ft_atoi(split[2]);
    free_char_pp(&split);
    free(copy);
    return (i);
}

void set_rgb(t_texture *texture, unsigned char *red, unsigned char *green, unsigned char *blue, int x, int y)
{
    *blue = texture->data[x * texture->bpp / 8 + y * texture->size_line];
    *green = texture->data[x * texture->bpp / 8 + y * texture->size_line + 1];
    *red = texture->data[x * texture->bpp / 8 + y * texture->size_line + 2];
}

int rgb_tohex(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}
