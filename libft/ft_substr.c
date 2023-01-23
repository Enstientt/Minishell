/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:03:16 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/14 18:33:32 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*substring;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substring = (char *)malloc(sizeof (char) * (len) + 1);
	if (!substring)
		return (0);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			substring[j] = s[i];
			j ++;
		}
		i ++;
	}
	substring[j] = '\0';
	return (substring);
}
