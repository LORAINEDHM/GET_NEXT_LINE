/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:22:17 by lduhamel          #+#    #+#             */
/*   Updated: 2019/12/10 13:00:46 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		ft_strlen_v2(char *str)
{
	size_t	i;

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
		free(src);
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
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen_v2(temp) +
					ft_strlen_v2(buf) + 1))))
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
		free(temp);
	return (str);
}
