/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:56 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:46:24 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_where_is_quot(char s, int code)
{
	static int	flag = 0;

	if (code == 1)
	{
		flag = 0;
		return (flag);
	}
	if (code == 2)
	{
		return (flag);
	}
	if (s == 34 && flag == 0)
		flag = 1;
	else if (s == 34 && flag == 1)
		flag = 0;
	else if (s == 39 && flag == 0)
		flag = 2;
	else if (s == 39 && flag == 2)
		flag = 0;
	return (flag);
}

size_t	ft_word_count_up(char *s, char *c, int code)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	ft_where_is_quot(s[i], 1);
	count = ft_parser_split_helper(s, i, c, code);
	return (count);
}

static char	*ft_newword_up(char *s, char c, size_t *i)
{
	char	*arr;
	size_t	len;
	size_t	start;

	len = 0;
	ft_where_is_quot(' ', 1);
	while (s[*i] == c && s[*i])
	{
		(*i)++;
	}
	start = *i;
	while ((ft_where_is_quot(s[*i], 0) || s[*i] != c) && s[*i])
	{
		len++;
		(*i)++;
	}
	arr = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(arr, &s[start], len + 1);
	return (arr);
}

char	**ft_mmyfree_up(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split_up(char *s, char *c)
{
	char	**string;
	size_t	word_count;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	word_count = ft_word_count_up(s, c, 1);
	string = ft_calloc(word_count + 1, sizeof(char *));
	if (string == NULL)
		ft_error(NULL, 1);
	while (i < word_count)
	{
		string[i] = ft_newword_up((char *)s, c[0], &j);
		if (string[i] == NULL)
		{
			return (ft_myfree(string));
		}
		i++;
	}
	string[i] = NULL;
	return (string);
}
