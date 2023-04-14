/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:46:33 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/14 06:30:35 by tumolabs         ###   ########.fr       */
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

