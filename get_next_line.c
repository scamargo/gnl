/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 20:35:38 by scamargo          #+#    #+#             */
/*   Updated: 2018/01/22 18:43:37 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int static	get_line(const int fd, char **str_arr, char **line)
{
	int i;
	char *new;
	
	i = 0;
	if((new = ft_strchr(str_arr[fd], '\n')))
	{
		*new = '\0';
		new++;
		*line = str_arr[fd];
		str_arr[fd] = new;
		return (1);
	}
	*line = str_arr[fd];
	str_arr[fd] = "";
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char *str_arr[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	int			reader;
	char		*temp;
		
	if (fd < 0 || read(fd, buff, 0) < 0)
    	return (-1);
	while ((reader = read(fd, buff, BUFF_SIZE)))
	{
		buff[reader] = '\0';
		if (!str_arr[fd])
			str_arr[fd] = ft_strdup(buff); //protext
		else
		{
			temp = str_arr[fd];
			str_arr[fd] = ft_strjoin(str_arr[fd], buff); //protect
			free(temp);
		}
	}
	return (get_line(fd, str_arr, line));
}
