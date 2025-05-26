/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:30:39 by manmaria          #+#    #+#             */
/*   Updated: 2025/05/15 23:10:26 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_line(char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s == '\n')
			return (0);
		s++;
	}
	return (1);
}

char	*ft_trimstash(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!stash || !*stash)
		return (NULL);
	len = ft_strclen(stash, '\n') + 1;
	line = ft_calloc(sizeof(char), len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	return (line);
}

char	*ft_stash_copycat(char *stash, char **buffer)
{
	char	*tmp;
	size_t	stash_len;
	size_t	buffer_len;
	size_t	i;

	if (!*buffer)
		return (stash);
	stash_len = ft_strclen(stash, 0);
	buffer_len = ft_strclen(*buffer, 0);
	tmp = ft_calloc(sizeof(char), stash_len + buffer_len + 1);
	if (!tmp)
		return (free(buffer), *buffer = NULL, NULL);
	i = -1;
	if (stash)
	{
		while (++i < stash_len)
			tmp[i] = stash[i];
		free(stash);
	}
	i = stash_len - 1;
	while (++i < (stash_len + buffer_len))
		tmp[i] = (*buffer)[i - stash_len];
	free(*buffer);
	*buffer = NULL;
	return (tmp);
}
// {
// 	char	*tmp;
//
// 	if (stash)
// 	{
// 		tmp = ft_strdup(stash);
// 		free(stash);
// 		stash = NULL;
// 	}
// 	else
// 	{
// 		tmp = ft_calloc(sizeof(char), 1);
// 		stash = NULL;
// 	}
// 	if (!tmp)
// 		return (NULL);
// 	stash = ft_strjoin(tmp, *buffer);
// 	free(*buffer);
// 	*buffer = NULL;
// 	free(tmp);
// 	if (!stash)
// 		return (NULL);
// 	return (stash);
// }
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strclen(s, 0))
		return (ft_strdup(""));
	if (len > ft_strclen(s + start, 0))
		len = ft_strclen(s + start, 0);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_free_stash(char **stash, char **line)
{
	char	*n_stash;
	size_t	flen;

	// if (!*stash && !*line)
	// 	return (NULL);
	if (!*line && *stash)
		return (free(*stash), *stash = NULL);
	if (!*stash  && *line)
		return (free(*line), *line = NULL);
	flen = ft_strclen(*stash, 0) - ft_strclen(*line, 0);
	n_stash = ft_substr(*stash, ft_strclen(*line, 0), flen);
	if (!n_stash)
	{
		free(*stash);
		*stash = NULL;
		return (free(*line), *line = NULL);
	}
	free(*stash);
	*stash = n_stash;
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	ssize_t		bread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bread = 1;
	line = NULL;
	buffer = NULL;
	while (bread > 0 && find_line(stash))
	{
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread == 0)
			break ;
		if (bread == -1)
			return (/*ft_free_stash(&stash, NULL)*, */free(buffer), NULL);
		stash = ft_stash_copycat(stash, &buffer);
		if (!stash)
			return (NULL);
	}
	line = ft_trimstash(stash);
	return (free(buffer), ft_free_stash(&stash, &line));
}
		
		// if (bread <= 0)
		// 	break ;
// 	OU
		// if (bread == 0)
		// 	break ;
		// if (bread == -1)
		// 	return (/*ft_free_stash(&stash, NULL)*, */free(buffer), NULL);

// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*line = NULL;
// 	// (void)av;
// 	// int	fd = -1;/*open(av[1], O_RDONLY);*/
// 	int	fd = open(av[1], O_RDONLY);
// 	printf("%s", line = get_next_line(fd));
// 	free(line);
// 	printf("%s", line = get_next_line(fd));
// 	free(line);
// 	printf("%s", line = get_next_line(fd));
// 	free(line);
// 	printf("%s", line = get_next_line(fd));
// 	free(line);
// 	printf("%s", line = get_next_line(fd));
// 	free(line);
// 	printf("%s", line = get_next_line(fd));
// 	printf("%s", line = get_next_line(fd));
// 	printf("%s", line = get_next_line(fd));
// }
//
// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*line = NULL;
// 	int	fd = open(av[1], O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
