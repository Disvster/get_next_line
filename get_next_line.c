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

int	find_line(char s)
{
	if (s == '\n')
			return (1);
	return (0);
}

char	*add_mem(char *stash, size_t size)
{
	char	*nstash;
	size_t	lenb;
	
	lenb = ft_strlen(stash);
	nstash = ft_calloc(sizeof(char), (size + lenb + 1));
	if (!nstash)
		return (NULL);
	if (stash)
		ft_strlcpy(nstash, stash, size + lenb + 1);
	// 	free(stash);
	return (nstash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024]; // ulimit -n command shows max fd possible
	char		*buffer;
	ssize_t		bread;
	size_t		i;

	if (fd < 0 ||BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	buffer = NULL;
	while (1)
	{
		stash[fd] = add_mem(stash[fd], BUFFER_SIZE); // adicionamos memoria para receber read
		bread = read(fd, stash[fd], BUFFER_SIZE); // read, var para checkar if em baixo
		if (bread == -1 || !stash[fd])
			return (NULL);
		buffer = add_mem(buffer, BUFFER_SIZE); // adiciono memoria para receber o que esta no stash
		ft_strlcat(buffer, stash[fd], ft_strlen(buffer) + BUFFER_SIZE + 1); // recebe o stash
		i = 0;
		while (find_line(buffer[i]) != 1 && buffer[i]) // percorro a struing ate new line
			i++;
		if (buffer[i] == '\n') // if TRUE entao devolvo o que esta no buffer mais a newline
		{
			char *tmp;
			tmp = ft_substr(buffer, 0, i + 1);
			free(buffer);
			buffer = tmp;
			break ;
		}
		else // ELSE dou free a stash e recebe novo read
		{
			free(stash[fd]);
			continue ;
		}
		// nao estou a ler ate \0 estou a saltar os bytes lido na iteracao anterior
	}
	return (buffer);
}

#include <stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	char	*line = NULL;
	int	fd = open(av[1], O_RDONLY);
	printf("%s", line = get_next_line(fd));
	printf("%s", line = get_next_line(fd));
	printf("%s", line = get_next_line(fd));
	// printf("%s", line = get_next_line(fd));
}
	// read(fd, stash[fd], BUFFER_SIZE);
	// i = ft_strnlen(stash[fd], BUFFER_SIZE);
	// line = malloc(sizeof(char) * (i + 1));
	// if (!line)
	// 	return (NULL);
	// line[++i] = 0;
	// if (stash[fd][--i] == '\n')
	// 	line[i] = '\n';
	// while (i-- > 0)
	// {
	// 	line[i] = stash[fd][i];
	// }
	// free(stash[fd]);
	// return (line);
