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

size_t	ft_strnstr_len(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big && !little)
		return (-1);
	i = 0;
	j = 0;
	if (little[j] == '\0')
		return (0);
	while (i < len && big[i])
	{
		while (big[i + j] == little[j] && big[i + j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return (i);
		j = 0;
		i++;
	}
	return (0);
}
