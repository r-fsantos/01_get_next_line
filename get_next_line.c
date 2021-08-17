/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 21:51:45 by rfelicio          #+#    #+#             */
/*   Updated: 2021/08/16 22:59:39 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** DEVELOPMENT NOTES:
** 	- verificacoes iniciais
**	- verificar se há conteúdo na variavel estatica (?? não terminado com '\n')
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
**
*/
char	*get_next_line(int fd)
{
	ssize_t		bytesread;
	ssize_t		i;
	char		*snippet;
	char		*next_line;
	static char	*buffer = NULL;

	buffer = " "; // todo: remove this line 
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	snippet = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!snippet)
		return (NULL);
	// write helper from this point...  hp_read_line
	bytesread = 1;
	bytesread = read(fd, (void *)snippet, BUFFER_SIZE);
	i = 0;
	while (snippet[i] != '\n' && snippet[i] != '\0' && bytesread)
		++i;
	// TODO: Check for previous values on the buffer. If there are any
	next_line = ft_substr((char const *)snippet, 0, i);
	return (next_line);
}
