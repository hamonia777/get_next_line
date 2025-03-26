/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:01:34 by jinwpark          #+#    #+#             */
/*   Updated: 2025/03/25 22:45:52 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	num;

	num = 0;
	if (!str)
		return (0);
	while (str[num])
	{
		num++;
	}
	return (num);
}

char	*ft_strdup(const char *s)
{
	char	*tmp;
	char	*addr;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	addr = tmp;
	while (s[i])
	{
		*tmp = s[i];
		tmp++;
		i++;
	}
	*tmp = '\0';
	return (addr);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char	tmp;
	int				i;

	i = 0;
	tmp = (unsigned char)c;
	while ((unsigned char)str[i] != tmp)
	{
		if ((unsigned char)str[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)&str[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen((const char *)s1) + ft_strlen((const char *)s2) + 1);
	str = (char *)malloc (len);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
