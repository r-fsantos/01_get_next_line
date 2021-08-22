/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 21:51:45 by rfelicio          #+#    #+#             */
/*   Updated: 2021/08/21 00:07:17 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_less(int fd, char **stream);
char	*ft_get_line(char **stream);
/*
** DEVELOPMENT NOTES:
** 	- get_next_line protection:
** 		- fd < 0; BUFFER_SIZE <= 0;
**		- snippet pointer protection;
**		- error on read, when reading 0 bytes;
**	- checks if static var contains '\n'
**		- true: 
**			- copiar pra linha que vou retornar?
**			- ler o proximo buffer e apender;
**		- false:
**			- ler o proximo buffer
**
**	- ler até encontrar uma linha
**	- read(fd, (void *)nextline, BUFFER_SIZE)
**		- Consideracoes:
**			- Se dentro do nextline eu tiver um \n e mais caracteres, i.e.:
**			  while(nextline[i] != NEW_LINE && nextline[i] != NULL) ++i;
*/
char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*buffer = NULL;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) IS_INVALID)
		return (NULL);
	if (!ft_strchr(buffer, NEW_LINE)) // se eu ja tiver um buffer com \n, nesse momento
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
		return (NULL); //(GNL_EOF);
	len = 0;
	line = NULL;
	snippet = *stream;
	while (snippet[len] != '\n' && snippet[len] != '\0')
		++len;
	if (snippet[len] == '\n')
		++len;
	line = ft_substr(snippet, 0, len);
	*stream = ft_strjoin(snippet + len, ""); //MOCK_DATA);
	free(snippet);
	return (line);
}

// try to remove this from here in the future... 
// if(!buffer)
// 	buffer = ft_strdup("");
// snippet = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// if (!snippet)
// 	return (NULL);
// // write helper from this point...  hp_read_line
// bytesread = 1;
// bytesread = read(fd, (void *)snippet, BUFFER_SIZE);
// i = 0;
// while (snippet[i] != '\n' && snippet[i] != '\0' && bytesread)
// 	++i;
// // TODO: Check for previous values on the buffer. If there are any
// next_line = ft_substr((char const *)snippet, 0, i);
// return (next_line);
// ft_less(fd, &buffer);
// next_line = ft_get_line(&buffer);