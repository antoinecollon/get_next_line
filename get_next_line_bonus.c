/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:55:47 by acollon           #+#    #+#             */
/*   Updated: 2025/05/05 17:32:11 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*save[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_and_join(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = get_line(save[fd]);
	if (!line)
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = save_rest(save[fd]);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	int		*fds;
// 	char	**lines;
// 	int		i;
// 	int		done;

// 	if (argc < 2)
// 		return (1);

// 	fds = malloc(sizeof(int) * (argc - 1));
// 	lines = malloc(sizeof(char *) * (argc - 1));
// 	if (!fds || !lines)
// 		return (1);

// 	i = 0;
// 	while (i < argc - 1)
// 	{
// 		fds[i] = open(argv[i + 1], O_RDONLY);
// 		lines[i] = NULL;
// 		i++;
// 	}

// 	done = 0;
// 	while (done < argc - 1)
// 	{
// 		done = 0;
// 		i = 0;
// 		while (i < argc - 1)
// 		{
// 			if (fds[i] < 0)
// 			{
// 				done++;
// 				i++;
// 				continue;
// 			}
// 			if (lines[i])
// 				free(lines[i]);
// 			lines[i] = get_next_line(fds[i]);
// 			if (!lines[i])
// 			{
// 				close(fds[i]);
// 				fds[i] = -1;
// 				done++;
// 			}
// 			else
// 				printf("%s", lines[i]);
// 			i++;
// 		}
// 	}

// 	i = 0;
// 	while (i < argc - 1)
// 	{
// 		if (lines[i])
// 			free(lines[i]);
// 		i++;
// 	}
// 	free(lines);
// 	free(fds);
// 	return (0);
// }