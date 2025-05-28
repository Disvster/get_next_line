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
	len = ft_strclen(stash, '\n');
	if (stash[len] == '\n')
		len++;
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

	stash_len = ft_strclen(stash, 0);
	buffer_len = ft_strclen(*buffer, 0);
	tmp = ft_calloc(sizeof(char), stash_len + buffer_len + 1);
	if (!tmp)
		return (free(*buffer), free(stash), NULL);
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

	// if (!tmp)
	// {
	// 	if (*buffer)
	// 		free(*buffer);
	// 	if (stash)
	// 		free(stash);
	// 	*buffer = NULL;
	// 	return (NULL);
	// }

char	*ft_free_stash(char **stash, char *line, ssize_t bread)
{
	char	*n_stash;
	size_t	flen;

	if (!line || bread <= 0)
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (line);
	}
	flen = ft_strclen(*stash, 0) - ft_strclen(line, 0);
	n_stash = ft_substr(*stash, ft_strclen(line, 0), flen);
	if (!n_stash)
	{
		free(*stash);
		*stash = NULL;
		return (free(line), NULL);
	}
	free(*stash);
	*stash = n_stash;
	return (line);
}

	// if (!*stash && line)
	// 	return (free(line), NULL);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	ssize_t		bread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stash(&stash, NULL, 0));
	bread = 1;
	line = NULL;
	buffer = NULL;
	// while (bread > 0 && find_line(stash))
	// {
	// 	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	// 	if (!buffer)
	// 		return (ft_free_stash(&stash, NULL, 0));
	// 	bread = read(fd, buffer, BUFFER_SIZE);
	// 	if (bread == 0)
	// 		break ;
	// 	if (bread == -1)
	// 		return (free(buffer), ft_free_stash(&stash, NULL, bread));
	// 	stash = ft_stash_copycat(stash, &buffer);
	// 	if (!stash)
	// 		return (NULL);
	// }
	while (bread > 0 && find_line(stash))
	{
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buffer)
			return (ft_free_stash(&stash, NULL, 0));
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread > 0)
			stash = ft_stash_copycat(stash, &buffer);
		else
			free(buffer);
		if (!stash || bread == -1)
			return (ft_free_stash(&stash, NULL, bread));
	}
	// free(buffer);
	// buffer = NULL;
	line = ft_trimstash(stash);
	return (ft_free_stash(&stash, line, bread));
}

	// if (!line)
	// 	return (ft_free_stash(&stash, NULL, bread));

// #include <stdio.h>
// #include <string.h>
// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	int	fd = open(av[1], O_RDONLY);
// 	char *line = get_next_line(fd);
// 	printf("1char.txt\nstrcmp -> %i\n", strcmp(line, "0"));
// 	free(line);
// 	close(fd);
// 	return (0);
// }

// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*line = NULL;
// 	// (void)av;
// 	// int	fd = -1;/*open(av[1], O_RDONLY);*/
// 	int	fd = open(av[1], O_RDONLY);
// 	printf("1 -> %s\n", line = get_next_line(fd));
// 	free(line);
// 	printf("2 -> %s\n", line = get_next_line(fd));
// 	free(line);
// 	close(fd);
// 	printf("3 -> %s\n", line = get_next_line(-1));
// 	free(line);
// 	fd = open(av[1], O_RDONLY);
// 	printf("4 -> %s\n", line = get_next_line(fd));
// 	free(line);
// 	printf("5 -> %s\n", line = get_next_line(fd));
// 	free(line);
// 	printf("6 -> %s\n", line = get_next_line(fd));
// 	printf("7 -> %s\n", line = get_next_line(fd));
// 	printf("8 -> %s\n", line = get_next_line(fd));
// }
//
//
// #include <stdio.h>
// #include <unistd.h>
// void	ft_putstr(char *line)
// {
// 	write(1, line, ft_strclen(line, 0));
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*line = NULL;
// 	int	fd = open(av[1], O_RDONLY);
// 	line = get_next_line(fd);
// 		ft_putstr(line);
// 	free(line);
// 	close(fd);
// 	open(av[1], O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		ft_putstr(line);
// 		free(line);
// 	}
// 	//line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// }
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
