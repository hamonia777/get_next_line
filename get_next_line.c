/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:24:52 by jinwpark          #+#    #+#             */
/*   Updated: 2025/04/01 21:38:08 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*buf;
	ssize_t		bytes_read;
	char		*tmp;
	char		*newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// 1) 버퍼 할당
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);

	bytes_read = 1;
	// 2) 읽기 루프: backup에 '\n'이 없고, read 반환값이 0이 아닐 동안 반복
	while (!ft_strchr(backup, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			// 읽기 에러 -> 누수 방지를 위해 buf와 backup 해제 후 NULL 반환
			free(buf);
			if (backup)
			{
				free(backup);
				backup = NULL;
			}
			return (NULL);
		}
		buf[bytes_read] = '\0';
		if (!backup)
			backup = ft_strdup(buf);
		else
		{
			// 기존 backup + 새로 읽은 buf 병합
			tmp = ft_strjoin(backup, buf);
			free(backup);
			backup = tmp;
		}
	}
	free(buf);
	// 3) backup이 NULL이거나 아무 내용 없으면(EOF 상황), NULL 반환
	if (!backup || backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	// 4) backup 안에 newline이 있는지 확인
	newline_pos = ft_strchr(backup, '\n');
	if (newline_pos)
	{
		// 개행 문자 포함 줄 반환
		size_t	len = newline_pos - backup + 1; // '\n'까지 길이
		char	*line = (char *)malloc(sizeof(char) * (len + 1));
		size_t	i = 0;
		if (!line)
			return (NULL);
		while (i < len)
		{
			line[i] = backup[i];
			i++;
		}
		line[i] = '\0';
		// 나머지 문자열을 tmp에 복사해 backup 대체
		tmp = ft_strdup(newline_pos + 1);
		free(backup);
		backup = tmp;
		// 만약 남은 문자열이 비어있다면 free 후 NULL
		if (backup && backup[0] == '\0')
		{
			free(backup);
			backup = NULL;
		}
		return (line);
	}
	else
	{
		// 개행 문자가 없음 -> 남은 내용이 마지막 줄
		char *line = backup;
		backup = NULL; // backup 해제
		return (line); // line은 호출자가 free해야 함
	}
}