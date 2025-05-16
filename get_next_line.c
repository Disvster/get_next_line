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

size_t	ft_strnlen(char *s, size_t n)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (n == 0)
	{
		while (s[i])
			i++;
		return (i);
	}
	while (i < n && s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*stash; // stashing the strings being read
	static char	*line; // the line we want to return
	char		*buffer;
	int			i;
	int			len;

	if (fd < 0)
		return (NULL);
	i = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read(fd, buffer, BUFFER_SIZE);
	i = ft_strnlen(line, 0);
	len = ft_strnlen(buffer + i, BUFFER_SIZE);
	line = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (*line && *line != '\n'
	while (buffer[i] != '\n' || buffer[i] != -1);
	return (buffer);
}

#include <stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	printf("gnl -> %s", get_next_line(open(av[1], O_RDONLY)));
}
