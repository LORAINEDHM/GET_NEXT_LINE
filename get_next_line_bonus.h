/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:22:13 by lduhamel          #+#    #+#             */
/*   Updated: 2019/12/10 13:02:53 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

size_t		ft_strlen_v2(char *str);
char		*ft_strdup(char *src);
char		*ft_strdup_v2(char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_join_buf(char *temp, char *buf);
int			ft_read(int fd, char **str, char **rest);
int			ft_put_rest(int fd, char **rest, char **str);
int			get_next_line(int fd, char **line);
#endif
