/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 21:51:45 by rfelicio          #+#    #+#             */
/*   Updated: 2021/08/30 15:37:16 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_less(int fd, char **stream);
char	*ft_get_line(char **stream);

/*
** The complicated and little perfect GeNiLson.
** Takes an opened file descriptor (fd) and returns a line from it.
** If sucessful, get_next_line returns a string with a line ended or not with
** the '\n' char.
** In the presence of errors or when reaching the end of the file, returns NULL
*/
char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*buffer = NULL;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) IS_INVALID)
		return (NULL);
	if (!ft_strchr(buffer, NEW_LINE))
		ft_less(fd, &buffer);
	next_line = ft_get_line(&buffer);
	if (!next_line)
	{
		free(buffer);
		free(next_line);
		next_line = NULL;
	}
	return (next_line);
}

/*
** Because less is more! RFTM: less ;)
** This procedure reads/unwrap the content of the file pointed by the file
** descriptor (fd), appending it to the pointer stored of the static char.
** This is made in this way:
**		- Checks if buf and bytesread is valid
**			- true:
**				- Null terminate the read "string";
**				- Reads until founds a '\n'char or the file ends. Either
**				way, appends/joins the content read to the static variable.
**			- false:
**				- Memory deallocation.
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

/*
** Extracts a line to be returned by get_next_line(int fd).
** First of all:
**		- Checks if there is an error *stream == NULL OR
**		if the EOF was reached. In both scenarios, returns NULL.
**		- Sets the line len (Remembering that the line can contain the
**		'\n' char or not);
**		- If the line ends with '\n', line len should be updated.
**		- Write the current line;
**		- Removes it from the static char;
**		- Performs memory management.
*/
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
	*stream = ft_strjoin(snippet + len, MOCK_DATA);
	free(snippet);
	snippet = NULL;
	return (line);
}
