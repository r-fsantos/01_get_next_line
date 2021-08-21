/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 21:58:58 by rfelicio          #+#    #+#             */
/*   Updated: 2021/08/20 23:49:19 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		while (*s != '\0' && *s != (char)c)
			++s;
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, s1len);
	ft_memcpy(str + s1len, s2, s2len);
	str[s1len + s2len] = '\0';
	return (str);
	// char	*str;
	// size_t	s1len;
	// size_t	s2len;

	// if (s1 == NULL || s2 == NULL)
	// 	return (NULL);
	// s1len = ft_strlen(s1);
	// s2len = ft_strlen(s2);
	// str = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	// if (str == NULL)
	// 	return (NULL);
	// ft_memcpy(str, s1, s1len);
	// ft_memcpy(str + s1len, s2, s2len);
	// str[s1len + s2len] = '\0';
	// return (str);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len] != '\0')
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (n--)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		++i;
	}
	return (dst);
}


void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dststart;
	unsigned char	*srcstart;

	if (!dst && !src)
		return (NULL);
	dststart = (unsigned char *)dst;
	srcstart = (unsigned char *)src;
	if (dststart <= srcstart)
		ft_memcpy(dststart, srcstart, len);
	else
	{
		while (len--)
			*(dststart + len) = *(srcstart + len);
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
		ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}

/*
** Allocates and returns a substring from the char const *s.
** The main logic is to verify if it is possible to match the
** substring as it is described by the params start and len.
** In this function it is import to considerer cases in which:
**
**		1. The user make some mistakes like passing an start index
**		that points to an region outside from the char const *s;
**		RETURN VALUE: The only substr possible to be formed: "\0"
**		2. size_t len is bigger than ft_strlen(s) an start is correct.
**		In this case, the len should be redefined.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (!len || start > slen)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > (slen - start))
		len = slen - start;
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	return ((char *)ft_memmove((void *)str, (void *)(s + start), len));
}
