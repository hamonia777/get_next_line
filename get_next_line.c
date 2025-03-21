/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:24:52 by jinwpark          #+#    #+#             */
/*   Updated: 2025/03/21 16:15:47 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*jw_merge(char *str1, char *str2)
{
	char *merge_str;

	merge_str = ft_strjoin(str1,str2);
	free(str1);
	free(str2);
	return (merge_str);
}

char	*jw_read(char *backup, int fd)
{
	int		read_count;
	char	*merge_str;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	read_count = 1;
	while (read_count > 0)
	{
		read_count = read(fd, buf, BUFFER_SIZE);
		merge_str = jw_merge(backup, buf);
		if (ft_strchr(buf, '\n') != 0)
			break;
		backup = merge_str;
	}
	backup[ft_strlen(backup)] = '\0';
	return (merge_str);
}

char	*jw_cutting(char *backup)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	str = malloc(i + 1);
	while (j < i)
	{
		str[j] = backup[j];
		j++;
	}
	return (str);
}

char	*jw_update(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	tmp = malloc(i + 1);
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char	buf[BUFFER_SIZE + 1];
	char	*str;
	ssize_t		buf_num;

	if (!buf || fd < 0)
	{
		return (NULL);
	}
	backup = jw_read(backup,fd);
	str = jw_cutting(backup);
	backup = jw_update(str);
	return (str);
}