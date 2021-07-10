/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:22:05 by lduhamel          #+#    #+#             */
/*   Updated: 2019/12/10 13:00:26 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int			ft_read(int fd, char **str, char **rest)
{
	int		ret;
	char	*temp;
	char	buf[BUFFER_SIZE + 1];

	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((*str = ft_join_buf(*str, buf)) == NULL)
			return (-1);
		if ((temp = ft_strchr(buf, '\n')) != 0)
		{
			if ((temp = ft_strdup(temp)) == NULL)
				return (-1);
			free(rest[fd]);
			rest[fd] = temp;
			break ;
		}
	}
	return (ret);
}

int			ft_put_rest(int fd, char **rest, char **str)
{
	char	*temp;

	if (rest[fd] != NULL)
	{
		if ((*str = ft_strdup(rest[fd])) == NULL)
			return (-1);
		free(rest[fd]);
		rest[fd] = NULL;
	}
	if ((temp = ft_strchr(*str, '\n')) != 0)
	{
		if ((temp = ft_strdup(temp)) == NULL)
			return (-1);
		if ((*str = ft_strdup_v2(*str)) == NULL)
			return (-1);
		free(rest[fd]);
		rest[fd] = temp;
		return (-2);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		*str;
	int			ret;
	static char	*rest[OPEN_MAX];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (-1);
	ret = 0;
	str = NULL;
	if ((ret = ft_put_rest(fd, rest, &str)) == -1)
		return (-1);
	if (ret != -2)
	{
		if ((ret = ft_read(fd, &str, rest)) == -1)
			return (-1);
		if (ret == 0 && str == NULL)
			return ((*line = ft_strdup("")) == NULL ? -1 : 0);
		if (ret < 0)
			return (-1);
	}
	*line = str;
	if (ret == 0 && rest[fd] == NULL)
		return (0);
	return (1);
}
