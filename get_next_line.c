/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:10:52 by npatron           #+#    #+#             */
/*   Updated: 2023/04/28 18:56:01 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*create_line(char *buffer, char *dest)
{
	char	*newdest;

	newdest = malloc(sizeof(char) * 1000);
	newdest = ft_strjoin(buffer, dest);
	free(buffer);
	return (newdest);
}

char	*read_file(int fd, char *buffer)
{
	int		i;
	char	*dest;

	i = 1;
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(dest);
			return (NULL);
		}
		dest = create_line(buffer, dest);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*dest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	return (buffer);
}

int	main(void)
{
	int		fd;
	char	*dest;

	dest = malloc(sizeof(char) * 1000 + 1);
	fd = open("test.txt", O_RDONLY);
	printf("%s \n", read_file(fd, dest));
	close(fd);
	return (0);
}
