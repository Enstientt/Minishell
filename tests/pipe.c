#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

///////////////////// GET_next_LINE ////////////////////////

size_t fft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *fft_strchr(const char *s, int c)
{
    int i;
    unsigned char *str;

    i = 0;
    str = (unsigned char *)s;
    while (str[i] != (unsigned char)c)
    {
        if (str[i] == '\0')
            return (0);
        i++;
    }
    return ((char *)str + i);
}

char *fft_strdup(char *s1)
{
    size_t i;
    char *s2;

    i = 0;
    s2 = (char *)malloc(fft_strlen(s1) + 1);
    if (!s2)
        return (NULL);
    while (s1[i])
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
    return (s2);
}

char *fft_strjoin(char const *s1, char const *s2)
{
    size_t i;
    size_t j;
    char *newstr;

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
        i++;
    }
    newstr[fft_strlen((char *)s1) + i] = '\0';
    return (newstr);
}

char *fft_substr(char *s, unsigned int start, size_t len)
{
    size_t i;
    size_t j;
    char *substring;

    i = 0;
    j = 0;
    if (fft_strlen((char *)s + start) < len)
        len = fft_strlen((char *)s + start);
    substring = (char *)malloc(sizeof(char) * (len + 1));
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

static char *next_line(char **str_remainder)
{
    size_t f;
    char *line;
    char *to_free;

    to_free = *str_remainder;
    f = 0;
    while ((*str_remainder)[f] != '\n' && (*str_remainder)[f] != '\0')
        f++;
    if (fft_strchr(*str_remainder, '\n'))
    {
        line = fft_substr(*str_remainder, 0, f + 1);
        *str_remainder = fft_strdup(*str_remainder + (f + 1));
    }
    else
    {
        line = fft_substr(*str_remainder, 0, f);
        *str_remainder = NULL;
    }
    free(to_free);
    return (line);
}

static void ft_tofill(int fd, char *buff, char **str)
{
    size_t read_bytes;
    char *tofree;

    read_bytes = 1;
    while (read_bytes)
    {
        read_bytes = read(fd, buff, BUFFER_SIZE);
        buff[read_bytes] = '\0';
        tofree = *str;
        *str = fft_strjoin(*str, buff);
        free(tofree);
        if ((fft_strchr(*str, '\n')))
            break;
    }
}

char *get_next_line(int fd)
{
    static char *str;
    char *line;
    char *buff;

    buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return (0);
    if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, buff, 0) < 0))
    {
        free(buff);
        return (NULL);
    }
    if (!str)
        str = fft_strdup("");
    ft_tofill(fd, buff, &str);
    free(buff);
    line = next_line(&str);
    if (!line[0])
    {
        free(line);
        return (NULL);
    }
    return (line);
}

////////////////////////////////////////////////////////////

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    while (s1[i] == s2[i])
    {
        if (s1[i] == '\0' && s2[i] == '\0')
            return (0);
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void ft_putstr_fd(char *s, int fd)
{
    int i;

    if (!s || !fd)
        return;
    i = 0;
    while (s[i])
    {
        ft_putchar_fd(s[i], fd);
        i++;
    }
}

///////////////////////////////////////////////////////////////////////////

int main (void)
{
    int     fd[2];
    char    *buffer;
    int     buffer_size;

    buffer = malloc(sizeof(char));
    if (pipe(fd) == -1)
    {
        printf ("error in pipe creation\n");
        return (-1);
    }
    while (1)
    {
        free(buffer);
        buffer = ;
        if (ft_strcmp(buffer, "END\n") == 0)
        {
            buffer_size = 1;
            break;
        }
    }
    printf("Write file: %d\n", fd[1]);
    while (buffer_size)
    {
        buffer_size = printf ("%s", get_next_line(fd[0]));
    }
    printf("Read file: %d\n", fd[0]);
    return (0);
}
