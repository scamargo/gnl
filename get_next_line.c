/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 20:35:38 by scamargo          #+#    #+#             */
/*   Updated: 2018/01/22 22:09:57 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_line(const int fd, char **str_arr, char **line)
{
	int		i;
	char	*new;

	i = 0;
	if ((new = ft_strchr(str_arr[fd], '\n')))
	{
		*new = '\0';
		new++;
		*line = str_arr[fd];
		str_arr[fd] = new;
		return (1);
	}
	*line = str_arr[fd];
	str_arr[fd] = "";
	if (**line)
		return (1);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char *str_arr[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	int			reader;
	char		*temp;

	if (line == NULL || fd < 0 || read(fd, buff, 0) < 0 || fd > FD_LIMIT)
		return (-1);
	while ((reader = read(fd, buff, BUFF_SIZE)))
	{
		buff[reader] = '\0';
		if (!str_arr[fd])
			str_arr[fd] = ft_strdup(buff);
		else
		{
			temp = str_arr[fd];
			str_arr[fd] = ft_strjoin(str_arr[fd], buff);
			free(temp);
		}
	}
	return (get_line(fd, str_arr, line));
}
