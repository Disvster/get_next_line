/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:11:26 by manmaria          #+#    #+#             */
/*   Updated: 2025/05/15 23:11:54 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	ltotal;
	char	*scat;

	if (!s1)
		return (0);
	ltotal = ft_strclen(s1, 0) + ft_strclen(s2, 0);
	scat = (char *)malloc(sizeof(char) * (ltotal + 1));
	if (!scat)
		return (NULL);
	i = 0;
	while (i < ft_strclen(s1, 0))
	{
		scat[i] = s1[i];
		i++;
	}
	while (i < ltotal)
	{
		scat[i] = s2[i - ft_strclen(s1, 0)];
		i++;
	}
	scat[i] = '\0';
	return (scat);
}

size_t	ft_strclen(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;	
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strclen(s, 0);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;
	size_t	mult;
	size_t	i;

	if (nmemb != 0 && size != 0 && (nmemb > ((size_t)-1 / size)))
		return (NULL);
	mult = nmemb * size;
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < mult)
		arr[i++] = '\0';
	return (arr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	if (!dst && !size)
		return (0);
	dst_len = ft_strclen(dst, 0);
	src_len = ft_strclen(src, 0);
	if (size == 0 || dst_len >= size)
		return (src_len + size);
	i = 0;
	while (src[i] && (i + dst_len + 1) < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strclen(src, 0));
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strclen(src, 0));
}
