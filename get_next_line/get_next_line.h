/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:06:47 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/16 00:44:29 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<unistd.h>
# include<stdlib.h>
# include<fcntl.h>
# include<stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	fft_strlen(char *str);
char	*fft_strchr(const char *s, int c);
char	*fft_strdup(char *s1);
char	*fft_strjoin(char const *s1, char const *s2);
char	*fft_substr(char *s, unsigned int start, size_t len);

#endif
