/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_split_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:28 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pipe_to_string(t_struct *st, int *i, int *j)
{
	int		len;
	char	*nl;

	len = ft_strlen(st->splited[(*i)]) + 1;
	nl = malloc(sizeof(char) * (len + 1));
	if (!nl)
		ft_error(st, 1);
	nl = ft_strjoin(nl, st->splited[(*i)]);
	nl[ft_strlen(nl)] = ' ';
	nl[ft_strlen(nl) + 1] = '\0';
	(*j)++;
	(*i)++;
	return (nl);
}

char	*ft_gnlstrjoin(char *remains, char *buffer)
{
	char	*omegalul;
	int		i;
	int		j;

	i = ft_strlen(remains) + ft_strlen(buffer);
	if (!remains && !buffer)
		return (NULL);
	omegalul = malloc(sizeof(char) * (i + 1));
	if (omegalul == NULL)
		ft_error(NULL, 1);
	i = 0;
	j = 0;
	if (remains)
	{
		while (remains[i])
			omegalul[j++] = remains[i++];
		i = 0;
	}
	while (buffer[i])
		omegalul[j++] = buffer[i++];
	omegalul[ft_strlen(remains) + ft_strlen(buffer)] = '\0';
	free(remains);
	return (omegalul);
}

int	ft_checkenv_d(char *s)
{
	int		len;
	char	*tmp;

	len = 0;
	while (s && s[len] != ' ' && s[len] != 34 && s[len] != '\0')
		len++;
	tmp = ft_substr(s, 0, len);
	if (!strncmp(tmp, "$?", 2))
	{
		if (tmp)
			free(tmp);
		return (2);
	}
	if (check_name_var(tmp + 1) == 0)
	{
		if (tmp)
			free(tmp);
		return (1);
	}
	if (tmp)
		free(tmp);
	return (0);
}

int	ft_swap_ask(t_struct *st, int index, int i)
{
	char	*digit;

	digit = ft_itoa(g_error);
	if (!digit)
		return (ft_error(st, 1));
	st->splited[index] = \
		ft_import(st->splited[index], digit, i, ft_strlen(digit) + 1);
	return (ft_strlen(digit) - 1);
}
