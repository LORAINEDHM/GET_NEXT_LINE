/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:06:05 by lduhamel          #+#    #+#             */
/*   Updated: 2019/11/26 19:05:28 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//Initialement :
//On copie dans str => chaque buffer jusqu’a rencontrer un buffer contenant ‘\n’.
//le reste est copie dans la variable rest, qui est ensuite copie dans str.
//
// 1. Si ft_strchr(str, ‘\n’) == 0 ==> tout est ok.
// 2. Si ft_strchr(str, ‘\n’ != 0 => ne pas lire le prochain buffer ==> stocker reste dans rest.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

size_t		ft_strlen_v2(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char		*ft_strdup(char *src)
{
	char		*ptr;
	size_t		i;
	
	ptr = NULL;
	i = 0;
	while (src && src[i])
		i++;
	if (!src || !(ptr = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char		*ft_strdup_v2(char *src)
{
	char		*ptr;
	size_t		i;
	
	ptr = NULL;
	if (!src || !(ptr = (char*)malloc(sizeof(char) * (ft_strlen_v2(src) + 1))))
		return (NULL);
	i = 0;
	while (src[i] != '\n')
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	if (src != NULL)
	 	free (src);
	return (ptr);
}

char		*ft_strchr(const char *s, int c)
{
	int i;
	i = 0;
	char *str;

	if (s == NULL)
		return (NULL);
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	str = ft_strdup((char*)s + i + 1);
//	free((char*)s);
	return (str);
}

char		*ft_join_buf(char *temp, char *buf)
{
	char	*str;
	int		i;
	int		j;
	i = 0;
	j = 0;
	if (buf == NULL || (buf == NULL && temp == NULL))
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen_v2(temp) + ft_strlen_v2(buf) + 1))))
		return (NULL);
	while (temp && temp[i])
	{
		str[i] = temp[i];
		i++;
	}
	while (buf && buf[j] != '\n' && buf[j])
		str[i++] = buf[j++];
	str[i] = '\0';
	if (temp != NULL)
	 	free (temp);
	return (str);
}

int			get_next_line(int fd, char **line)
{
	char *str;
	char *temp;
	int	ret;
	char buf[BUFFER_SIZE + 1];
	static char *rest[OPEN_MAX];
	
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
         return (-1);
	ret = 0;
	str = NULL;
	if (rest[fd] != NULL)
	{
		if ((str = ft_strdup(rest[fd])) == NULL)
			return (-1);
	}
	if (rest[fd] != NULL)
	{
		free(rest[fd]);
		rest[fd] = NULL;
	}
	if ((temp = ft_strchr(str, '\n')) != 0)
	{
		free(rest[fd]);
		rest[fd] = temp;
		if ((str = ft_strdup_v2(str)) == NULL)
			return (-1);
	}
	// if (rest[fd] != NULL)
	// {
	// 	free(rest[fd]);
	// 	rest[fd] = NULL;
	// }
	else
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (-1);
		if (ret == 0 && str == NULL)
		{
			if ((*line = ft_strdup("")) == NULL)
				return (-1);
			return (0);
		}
		while (ret > 0)
		{
			buf[ret] = '\0';
			if ((str = ft_join_buf(str, buf)) == NULL)
				return (-1);
			if ((temp = ft_strchr(buf, '\n')) != 0)
			{
				free(rest[fd]);
				rest[fd] = temp;
				break;
			}
			ret = read(fd, buf, BUFFER_SIZE);
		}
	}
	*line = str;
	if (ret == 0 && rest[fd] == NULL)
	 	return (0);
	return (1);
}

int main()
{
	int fd = open("text.txt", O_RDONLY);
	char *line = NULL;

	while ((get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
		printf("%s\n", line);
		free(line);
	system("leaks a.out");
	return 0;
}