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

#include "get_next_line_bonus.h"

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
	i = 0;
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	return (line);
}

void	ft_stash_copycat(char **stash, char **buffer)
{
	char	*tmp;
	size_t	ttlen;

	ttlen = ft_strclen(*stash, 0) + ft_strclen(*buffer, 0) + 1;
	tmp = ft_strdup(*stash);
	if (!tmp)
		tmp = ft_calloc(sizeof(char), 1);
	free(*stash);
	*stash = ft_calloc(sizeof(char), ttlen);
	if (!*stash)
		return ;
	ft_strlcpy(*stash, tmp, ttlen - ft_strclen(*buffer, 0));
	ft_strlcat(*stash, *buffer, ttlen);
	free(*buffer);
	*buffer = NULL;
	free(tmp);
}

void	ft_free_stash(char **stash, char *line)
{
	char	*tmp;
	size_t	flen;

	if (!line)
	{
		free (*stash);
		*stash = NULL;
		return ;
	}
	flen = ft_strclen(*stash, 0) - ft_strclen(line, 0) + 1;
	tmp = ft_strdup(*stash);
	free(*stash);
	*stash = ft_calloc(sizeof(char), flen);
	ft_strlcpy(*stash, tmp + ft_strclen(line, 0), flen);
	free(tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	char		*line;
	ssize_t		bread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bread = 1;
	line = NULL;
	buffer = NULL;
	while (bread > 0 && find_line(stash[fd]))
	{
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread == 0)
			break ;
		if (bread == -1)
			return (ft_free_stash(&stash[fd], NULL), free(buffer), NULL);
		ft_stash_copycat(&stash[fd], &buffer);
		if (!stash[fd])
			return (NULL);
	}
	line = ft_trimstash(stash[fd]);
	ft_free_stash(&stash[fd], line);
	return (free(buffer), line);
}

// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*line = NULL;
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
#include <stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	char	*line = NULL;
	int	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
