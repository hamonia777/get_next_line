/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:24:52 by jinwpark          #+#    #+#             */
/*   Updated: 2025/03/26 20:15:13 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*jw_read(int fd)
{
	int		read_count;
	char	*merge_str;
	char	*buf;
	char	*tmp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	merge_str = NULL;
	read_count = 1;
	while (read_count > 0)
	{
		read_count = read(fd, buf, BUFFER_SIZE);
		if(read_count <= 0)
			break;
		buf[read_count] = '\0';
		tmp = merge_str;
		if (!merge_str)
			merge_str = ft_strdup(buf);
		else
			merge_str = ft_strjoin(merge_str, buf);
		free(tmp);
		if (ft_strchr(buf, '\n') != 0)
			break ;
	}
	free(buf);
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
	if (backup[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = backup[j];
		j++;
	}
	str[j] = '\0';
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
	if (str[i] == '\n')
		i++;
	tmp = malloc(i + 1);
	if(!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*str;
	char		*tmp;
	if (fd < 0)
		return (NULL);
	if(!backup)
		backup = jw_read(fd);
	else
	{
		tmp = ft_strjoin(backup, jw_read(fd));
		backup = tmp;
	}
	if(!backup)
		return (NULL);
	str = jw_cutting(backup);
	if(!str)
		return (NULL);
	backup = jw_update(backup);
	if(!backup)
		return (NULL);
	return (str);
}