/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:06:32 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/16 00:45:52 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	fft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*fft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (str[i] != (unsigned char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return ((char *) str + i);
}

char	*fft_strdup(char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = (char *)malloc(fft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i ++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*fft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	if (!s2)
		return ((char *)s1);
	i = 0;
	j = 0;
	newstr = (char *)malloc(fft_strlen((char *)s1) + fft_strlen((char *)s2) + 1);
	if (!newstr)
		return (NULL);
	while (s1[j])
	{
		newstr[j] = s1[j];
		j++;
	}
	while (i < fft_strlen((char *)s2))
	{
		newstr[fft_strlen((char *)s1) + i] = s2[i];
		i ++;
	}
	newstr[fft_strlen((char *)s1) + i] = '\0';
	return (newstr);
}

char	*fft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*substring;

	i = 0;
	j = 0;
	if (fft_strlen((char *)s + start) < len)
		len = fft_strlen((char *)s + start);
	substring = (char *)malloc(sizeof (char) * (len + 1));
	if (!substring)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			substring[j] = s[i];
			j++;
		}
		i++;
	}
	substring[j] = '\0';
	return (substring);
}
