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

char	*get_next_line(int fd)
{
	static char	*stash[1024]; // stashing the strings being read
	char		*line;
	char		*tmp;

	if (fd < 0 ||BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
	 	stash[fd] = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	// if (!stash[fd])
	// 	return (NULL);
	line = NULL;
	tmp = NULL;
	while (1)
	{
		if (!stash[fd])
			stash[fd] = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		if (!stash[fd] || read(fd, stash[fd], BUFFER_SIZE) == -1)
			return (NULL);
		stash[fd] = ft_strjoin(stash[fd], line);
		tmp = ft_strjoin(stash[fd], line);
		free(line);
		line = tmp;
		if (find_line(stash[fd][ft_strlen(line) - 1]) != 0)
			continue ;
		else
		{
			write(1, "aqui\n", 5);
			break ;
		}
	}
	if (read(fd, stash[fd], BUFFER_SIZE) == 0)
		free(stash[fd]);
	return (line);
}

	// tenho que alocar memoria para stash * BUFFER_SIZE 
	// dar lhe o que ta no read * BUFFER_SIZE 
	// strdup de stash -> line
	// se line na ultima posicao for newline -> return (line)
	// senao -> strjoin do proximo read para stash[fd]
	// volta ao inicio do loop;
	// 
	// stash comeca com tamanho de buffer_size
	// e lhe aplicado o read
	// stash e copiado para line
	// line so se devolve se encontrarmos linha ou EOF (read == 0)
	// senao adiciona-se mais memoria a stash * BUFFER_SIZE 
	// e continua o processo mas stash agora recebe um join do result do read
	//
	// se encontramos a newline ou o EOF antes da memoria total alocada
	// temos de dar free a memoria que foi alocada mas nao utilizada
	// e so depois return (line)
	// so damos free a stash[fd] quando EOF is reached

#include <stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	printf("gnl -> %s\n", get_next_line(open(av[1], O_RDONLY)));
	printf("gnl -> %s\n", get_next_line(open(av[1], O_RDONLY)));
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
