/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 23:56:47 by anwar             #+#    #+#             */
/*   Updated: 2026/08/22 23:56:47 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static void	free_all(char **words, size_t filled)
{
	size_t	i;

	i = 0;
	while (i < filled)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static char	*next_word(const char **s, char c)
{
	const char	*start;
	char		*word;
	size_t		len;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	len = (size_t)(*s - start);
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, start, len);
	word[len] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**words;
	size_t	n_words;
	size_t	i;

	n_words = count_words(s, c);
	words = (char **)malloc((n_words + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	while (i < n_words)
	{
		words[i] = next_word(&s, c);
		if (!words[i])
		{
			free_all(words, i);
			return (NULL);
		}
		i++;
	}
	words[n_words] = NULL;
	return (words);
}
