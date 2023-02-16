#ifndef REMINDER_EXE_H
# define REMINDER_EXE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
//utils
char	**ft_split(char const *s, char c);
int		count_elements(char **strs);
int		check_char_strs(char **s);
long	ft_atoi(const char *str);
#endif
