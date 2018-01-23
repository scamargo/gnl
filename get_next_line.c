/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 20:35:38 by scamargo          #+#    #+#             */
/*   Updated: 2018/01/22 18:30:22 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char static	*get_line(const int fd, char **str_arr)
{
	int i;
	char *new;
	char *result;
	//read str until you find newline
	i = 0;
	if((new = ft_strchr(str_arr[fd], '\n')))
	{
		//null terminated next line and move arr pointer
		*new = '\0';
		new++;
		result = str_arr[fd];
		str_arr[fd] = new;
		return (result);
	}
	result = str_arr[fd];
	str_arr[fd] = "";
	return (result);
}

int		get_next_line(const int fd, char **line)
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
	*line = get_line(fd, str_arr);
	if (**line)
		return (1);
	return (0);
}
