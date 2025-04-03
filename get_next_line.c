/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:24:52 by jinwpark          #+#    #+#             */
/*   Updated: 2025/04/02 22:43:20 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*jw_free(char *buf, char **backup)
{
	free(buf);
	if (*backup)
	{
		free(*backup);
		*backup = NULL;
	}
	return (NULL);
}

static char	*jw_read(int fd, char *backup)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(backup, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (jw_free(buf, &backup));
		buf[bytes_read] = '\0';
		if (!backup)
			backup = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(backup, buf);
			free(backup);
			backup = tmp;
		}
	}
	free(buf);
	return (backup);
}

static char	*jw_copy(const char *src, size_t len)
{
	char	*line;
	size_t	i;

	i = 0;
	line = malloc(len + 1);
	while (i < len)
	{
		line[i] = src[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*jw_extract(char **backup)
{
	char	*newline;
	char	*line;
	char	*tmp;
	size_t	len;

	newline = ft_strchr(*backup, '\n');
	if (newline)
	{
		len = newline - *backup + 1;
		line = jw_copy(*backup, len);
		tmp = ft_strdup(newline + 1);
		free(*backup);
		*backup = tmp;
		if (*backup && !(*backup)[0])
		{
			free(*backup);
			*backup = NULL;
		}
	}
	else
	{
		line = *backup;
		*backup = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = jw_read(fd, backup);
	if (!backup || backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	return (jw_extract(&backup));
}
