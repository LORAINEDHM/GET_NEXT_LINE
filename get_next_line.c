/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:11:31 by lduhamel          #+#    #+#             */
/*   Updated: 2019/11/28 16:55:41 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1. Read buf + '\0' a la fin du buf
// 2. join_buf => joint les buf tant qu il n y a pas de '\n'
//  (Malloc => Len des buf assembles + du prochain but a joindre (dans la limite du '\n' s'il y a).
//  Au 1er tour, on ne rentre pas dans la 1ere boucle car str (temp) = NULL, donc on copie dans le nouvel str uniquement le 1er buf lu (soit jusqu'à au '\0', soit jusqu'au '\n').
// 3. Strchr => s'il y a un '\n' dans le buf qu'il vient de lire, on copie ce qu'il y a après le '\n' dans rest.
// 4. On lit le buffer suivant.
// 5. *line = str
// 6. Str = rest (on utilise strdup et pas strdup_v2 puisque meme em presence de plusieurs '\n' on veut tout garder).
//  strchr => si jamais rest contient des '\n' (cela signifie qu'il y avait plusieurs '\n' dans le dernier buffer lu avant de copier str) ; 
// 	dans ce cas, rest = ce qu'il y a après le 1er '\n', et on copie str dans la nouvelle line jusqu'au '\n', et on ne lit pas le buffer suivant.
//  Si jamais il y a encore des '\n' dans rest, on répète l'operation.
// 7. Une fois qu'il n'y a plus de '\n' dans rest (str), nous pouvons lire le buffer suivant.
//  join_buf => Si rest existe, il sera copie dans str, et on ajoutera les buffer un a un jusqu'a trouver un '\n'.
//  et ainsi de suite.

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
	if (s == NULL)
		return (NULL);
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return ((char*)s + i + 1);
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

int         ft_read(int fd, char **str, char **rest)
{
	int ret;
	char *temp;
	char buf[BUFFER_SIZE + 1];

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
			break;
		}
	}
    return (ret);
}

void       ft_put_rest(int fd, char **rest, char *str)
{
    char *temp;
    
    if (rest[fd] != NULL)
	{
		if ((str = ft_strdup(rest[fd])) == NULL)
			return (NULL);
		free(rest[fd]);
		rest[fd] = NULL;
	}
	if ((temp = ft_strchr(str, '\n')) != 0)
	{
		if ((temp = ft_strdup(temp)) == NULL || (str = ft_strdup_v2(str)) == NULL)
			return (NULL);
		free(rest[fd]);
		rest[fd] = temp;
	}
}

int			get_next_line(int fd, char **line)
{
	char *str;
	//char *temp;
	int	ret;
	static char *rest[OPEN_MAX];
    
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
         return (-1);
	ret = 0;
	str = NULL;  
    ft_put_rest(fd, rest, str);
            return (-1);
	// if (rest[fd] != NULL)
	// {
	// 	if ((str = ft_strdup(rest[fd])) == NULL)
	// 		return (-1);
	// 	free(rest[fd]);
	// 	rest[fd] = NULL;
	// }
	// if ((temp = ft_strchr(str, '\n')) != 0)
	// {
	// 	if ((temp = ft_strdup(temp)) == NULL || (str = ft_strdup_v2(str)) == NULL)
	// 		return (-1);
	// 	free(rest[fd]);
	// 	rest[fd] = temp;
	// }
    
	else
	{
        if ((ret = ft_read(fd, &str, rest)) == -1)
            return (-1);
        if (ret == 0 && str == NULL)
			    return((*line = ft_strdup("")) == NULL ? -1 : 0);
        if (ret < 0)
			return (-1);
	}
	*line = str;
	if (ret == 0 && rest[fd] == NULL)
	 	return (0);
	return (1);
}

// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char *line = NULL;
// 	while ((get_next_line(fd, &line)) > 0)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 		printf("%s\n", line);
// 		free(line);
// 	system("leaks a.out");
// 	return 0;
// }