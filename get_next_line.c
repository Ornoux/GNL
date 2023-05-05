/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:10:52 by npatron           #+#    #+#             */
/*   Updated: 2023/05/05 20:17:11 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*create_line(char *save, char *buffer)
{
	char	*newsave;

	newsave = ft_strjoin(save, buffer);
	free (save);
	return (newsave);
}

char	*get_linee(char	*dest)
{
	char	*line;
	int		i;

	i = 0;
	if (!dest)
		return (NULL);
	while (dest[i] != '\n' && dest[i])
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (dest[i] && dest[i] != '\n')
	{
		line[i] = dest[i];
		i++;
	}
	if (dest[i] == '\n' && dest[i])
		line[i++] = '\n';
	return (line);
}

char	*get_next(char *dest)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (dest[i] && dest[i] != '\n')
		i++;
	if (!dest)
	{
		free(dest);
		return (NULL);
	}
	line = ft_calloc(sizeof(char), (ft_strlen(dest) - i + 1));
	j = 0;
	i += 1;
	while (dest[i] && dest[i] != '\n')
		line[j++] = dest[i++];
	free(dest);
	return (line);
}

char	*read_file(int fd, char *save)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!save)
		save = ft_strdup("");
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = 0;
		save = create_line(save, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*dest;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	dest = get_linee(save);
	save = get_next(save);
	return (dest);
}

int	main(void)
{
	int		fd;

	fd = open("test.txt", O_RDONLY);
	printf("1ere ligne : %s\n", get_next_line(fd));
	printf("2eme ligne : %s\n", get_next_line(fd));
	printf("3eme ligne : %s\n", get_next_line(fd));
	printf("4eme ligne : %s", get_next_line(fd));
	return (0);
}
