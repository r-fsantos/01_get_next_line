/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 21:58:58 by rfelicio          #+#    #+#             */
/*   Updated: 2021/08/24 17:25:19 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	str = (char *)malloc((len + 1) * sizeof(char));
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
	s1len = 0;
	s2len = 0;
	while(s1[s1len] != '\0')
		++s1len;
	while(s2[s2len] != '\0')
		++s2len;
	str = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, s1len);
	ft_memmove(str + s1len, s2, s2len);
	str[s1len + s2len] = '\0';
	return (str);
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
		while (len--)
			*dststart++ = *srcstart++;
	else
		while (len--)
			*(dststart + len) = *(srcstart + len);
	return (dst);
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
	size_t 	i;
	size_t	slen;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	slen = 0;
	while(s[slen] != '\0')
		++slen;
	if (!len || start > slen)
		len = 0;
	if (len > (slen - start))
		len = slen - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len && (start + i) < slen)
	{
		str[i] = s[start + i];
		++i;
	}
	str[i] = '\0';
	return (str);
}
