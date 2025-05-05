/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:55:47 by acollon           #+#    #+#             */
/*   Updated: 2025/05/05 17:31:47 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*save_rest(char *save)
{
	size_t	i;
	char	*rest;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	rest = ft_strdup(save + i);
	free (save);
	return (rest);
}

static char	*get_line(char *save)
{
	size_t	i;

	i = 0;
	if (!save || *save == '\0')
		return (NULL);
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	return (ft_substr(save, 0, i));
}

static char	*read_and_join(int fd, char *save)
{
	char	*tmp;
	char	*new;
	ssize_t	bytes_read;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(save, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(tmp), free(save), NULL);
		tmp[bytes_read] = '\0';
		new = ft_strjoin(save, tmp);
		if (!new)
			return (free(tmp), free(save), NULL);
		free(save);
		save = new;
	}
	return (free(tmp), save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_and_join(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	if (!line)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = save_rest(save);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
