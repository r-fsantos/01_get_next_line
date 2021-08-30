/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:41:15 by rfelicio          #+#    #+#             */
/*   Updated: 2021/08/30 14:48:32 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "unistd.h"
# include "stdlib.h"
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# define NEW_LINE '\n'
# define GNL_EOF NULL
# define TRUE 1
# define MOCK_DATA ""
# define IS_VALID > 0
# define IS_INVALID == -1

/*
** The complicated and little perfect GeNiLson.
*/
char	*get_next_line(int fd);
void	ft_less(int fd, char **stream);
char	*ft_get_line(char **stream);
/*
** Many thanks to the helpers && utils, writen during the libft project.
*/

char	*ft_strdup(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif