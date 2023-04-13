/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 06:25:08 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/17 10:07:55 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *buffer, int ch)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == ch)
			return ((char *)buffer + i);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] && c[i] != '\0')
		i++;
	return (i);
}

char	*join(char *stat, char *buffer)
{
	char	*join;
	size_t	i;
	size_t	c;

	if (!stat)
	{
		stat = (char *)malloc(sizeof(char) * 1);
		stat[0] = '\0';
	}
	if (!stat || !buffer)
		return (NULL);
	i = -1;
	c = -1;
	join = (char *)malloc(sizeof(char)
			* (ft_strlen(stat) + ft_strlen(buffer) + 1));
	if (!join)
		return (NULL);
	while (stat[++i] != '\0')
		join[i] = stat[i];
	while (buffer[++c])
		join[i++] = buffer[c];
	join[i] = '\0';
	free(stat);
	return (join);
}
