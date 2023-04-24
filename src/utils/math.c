/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:35:23 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/24 20:17:52 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_radian(double degree)
{
	return (degree * PI / 180.0);
}

double	replace_angle_360(double angle)
{
	if (angle > 360)
		angle = angle - 360;
	else if (angle < 0)
		angle = angle + 360;
	return (angle);
}
