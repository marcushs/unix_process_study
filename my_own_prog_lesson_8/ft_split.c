#include "reminder_exe.h"

static int	count_strings(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_strlen_sep(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*make_word(char const *s, char c)
{
	char	*word;
	int		i;
	int		len;

	len = ft_strlen_sep(s, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static char	**ft_splitter(char **strs, char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			strs[i] = make_word(s, c);
			if (!strs[i])
			{
				while (i >= 0)
					free(strs[i--]);
				free(strs);
				return (NULL);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	strs[i] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**new_strs;

	if (!s)
		return (NULL);
	new_strs = (char **)malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!new_strs)
		return (NULL);
	return (ft_splitter(new_strs, s, c));
}
