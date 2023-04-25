/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:18:07 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/25 18:52:19 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check(char *n, int i, float *f);

float	ft_atof(char *n)
{
	int		i;
	int		sign;
	float	f;
	float	cout;

	f = 0.0;
	i = 0;
	sign = 1;
	cout = 0;
	while (n[i] && ft_isspace(n[i]))
		i++;
	if (n[i] == '-')
		sign = -1;
	if (n[i] == '-' || n[i] == '+')
		i++;
	while (n[i] && ft_isdigit(n[i]))
		f = f * 10.0 + (n[i++] - '0');
	check(n, i, &f);
	return (f * sign);
}

static void	check(char *n, int i, float *f)
{
	int	cout;

	cout = 0;
	if (n[i++] == '.')
	{
		while (n[i] && ft_isdigit(n[i]))
		{
			*(f) = *(f) * 10.0 + (n[i++] - '0');
			cout++;
		}
		while (cout--)
			*(f) = floor(*(f)) * 0.1;
	}
}
