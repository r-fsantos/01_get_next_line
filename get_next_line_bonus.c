/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 21:51:45 by rfelicio          #+#    #+#             */
/*   Updated: 2021/08/24 17:50:42 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

void	ft_less(int fd, char **stream);
char	*ft_get_line(char **stream);

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*buffer[OPEN_MAX];

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) IS_INVALID)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup(MOCK_DATA);
	if (!ft_strchr(buffer[fd], NEW_LINE))
		ft_less(fd, &buffer[fd]);
	next_line = ft_get_line(&buffer[fd]);
	if (buffer[fd] && buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	if (!next_line)
	{
		free(next_line);
		next_line = NULL;
	}
	return (next_line);
}

/*
** Because less is more! RFTM: less ;)
** This procedure only reads/unwrap the context of the file descriptor,
** appending/updating it to the pointer stored of the static char.
** This is made in this way:
**		-
**		-
*/
void	ft_less(int fd, char **stream)
{
	char	*buf;
	char	*old_address;
	ssize_t	bytesread;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf)
		bytesread = read(fd, (void *)buf, BUFFER_SIZE);
	if (buf && bytesread IS_VALID)
	{
		buf[bytesread] = '\0';
		while (!ft_strchr(buf, NEW_LINE) && bytesread IS_VALID)
		{
			old_address = *stream;
			*stream = ft_strjoin(*stream, buf);
			if (old_address)
				free(old_address);
			bytesread = read(fd, (void *)buf, BUFFER_SIZE);
			buf[bytesread] = '\0';
		}
		old_address = *stream;
		*stream = ft_strjoin(*stream, buf);
		if (old_address)
			free(old_address);
	}
	free(buf);
}

char	*ft_get_line(char **stream)
{
	int		len;
	char	*line;
	char	*snippet;

	if (*stream == NULL || (*(*stream)) == '\0')
		return (GNL_EOF);
	len = 0;
	line = NULL;
	snippet = *stream;
	while (snippet[len] != NEW_LINE && snippet[len] != '\0')
		++len;
	if (snippet[len] == NEW_LINE)
		++len;
	line = ft_substr(snippet, 0, len);
	*stream = ft_strdup(snippet + len);
	free(snippet);
	return (line);
}
