#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	int		*fds;
	char	**lines;
	int		i;
	int		done;

	if (argc < 2)
		return (1);

	fds = malloc(sizeof(int) * (argc - 1));
	lines = malloc(sizeof(char *) * (argc - 1));
	if (!fds || !lines)
		return (1);

	i = 0;
	while (i < argc - 1)
	{
		fds[i] = open(argv[i + 1], O_RDONLY);
		lines[i] = NULL;
		i++;
	}

	done = 0;
	while (done < argc - 1)
	{
		done = 0;
		i = 0;
		while (i < argc - 1)
		{
			if (fds[i] < 0)
			{
				done++;
				i++;
				continue;
			}
			if (lines[i])
				free(lines[i]);
			lines[i] = get_next_line(fds[i]);
			if (!lines[i])
			{
				close(fds[i]);
				fds[i] = -1;
				done++;
			}
			else
				printf("%s", lines[i]);
			i++;
		}
	}

	i = 0;
	while (i < argc - 1)
	{
		if (lines[i])
			free(lines[i]);
		i++;
	}
	free(lines);
	free(fds);
	return (0);
}
