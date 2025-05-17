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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;	
	size_t	len;

	i = 0;
	len = ft_strlen(s);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	ltotal;
	char	*scat;

	if (!s1)
		return (0);
	ltotal = ft_strlen(s1) + ft_strlen(s2);
	scat = (char *)malloc(sizeof(char) * (ltotal + 1));
	if (!scat)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		scat[i] = s1[i];
		i++;
	}
	while (i < ltotal)
	{
		scat[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	scat[i] = '\0';
	return (scat);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p_s;
	size_t			i;

	i = 0;
	p_s = s;
	while (i < n)
		p_s[i++] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	mult;

	if (nmemb != 0 && size != 0 && (nmemb > ((size_t)-1 / size)))
		return (NULL);
	mult = nmemb * size;
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, mult);
	return (arr);
}
