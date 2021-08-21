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
	char		*snippet;
	char		*next_line;
	static char	*buffer = NULL; // static always starts with zero?

	snippet = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, snippet, 0) IS_INVALID)
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
** This procedure only reads/unwrap the context of the file descriptor,
** appending/updating it to the pointer stored of the static char.
** This is made in this way:
**		-
**		-
*/
void	ft_less(int fd, char **stream)
{
	char	*buf; // TODO REFACTOR: buf[BUFFER_SIZE]
	char	*old_address;
	ssize_t	bytesread;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // TODO: DRY!!!!!!!!
	bytesread = read(fd, (void *)buf, BUFFER_SIZE);
	// if (bytesread < BUFFER_SIZE && *stream != NULL)
	// if (bytesread == 0)
	// {
	// 	*stream[bytesread] = '\0';
	// 	return ;
	// }
	if (buf && bytesread >= 0) //   IS_VALID)
	{
		buf[bytesread] = '\0';
		while(!ft_strchr(buf, NEW_LINE) && bytesread IS_VALID)
		{
			old_address = *stream;
			*stream = ft_strjoin(old_address, buf);
			if (old_address) // TODO: Remove this if, its redundant
			{
				free(old_address);
				old_address = NULL;
			}
			bytesread = read(fd, (void *)buf, BUFFER_SIZE); // TODO: DRY!!!!!!!!
			buf[bytesread] = '\0';
		}
		old_address = *stream;
		*stream = ft_strjoin(old_address, buf);
		if (old_address)
		{
			free(old_address);
			old_address = NULL;
		}
	}
	free(buf); // TODO REFACTOR: buf[BUFFER_SIZE]
	buf = NULL;
}

char	*ft_get_line(char **stream)
{
	int		len;
	char	*line;
	char	*snippet;

	if(*stream == NULL || (*(*stream)) == '\0')
		return (GNL_EOF);
	len = 0;
	snippet = *stream;
	while (snippet[len] != '\n' && snippet[len] != '\0')
		++len;
	line = ft_substr(snippet, 0, len + 1);
	*stream = ft_strjoin(snippet + len + 1, MOCK_DATA);
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