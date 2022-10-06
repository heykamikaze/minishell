/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:51:57 by ksaffron          #+#    #+#             */
/*   Updated: 2022/07/21 10:44:40 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_import(char *st, char *str, int i, int j)
{
	char	*newline;
	int		zh[2];

	zh[0] = 0;
	newline = malloc(sizeof(char) * \
			(ft_strlen(str) + ft_strlen(st) - j + 1));
	if (!newline)
		ft_error(NULL, 1);
	while (zh[0] < i)
	{
		newline[zh[0]] = st[zh[0]];
		zh[0]++;
	}
	zh[1] = 0;
	while (str[zh[1]])
		newline[zh[0]++] = str[zh[1]++];
	i += j;
	while (st[i])
		newline[zh[0]++] = st[i++];
	newline[zh[0]] = '\0';
	if (st)
		free(st);
	if (str)
		free(str);
	return (newline);
}

int	ft_enver(t_struct *st, int index, int i, int j)
{
	char	*newline;
	int		z;

	z = 0;
	newline = malloc(sizeof(char) * \
			(ft_strlen(st->splited[index]) - j + 1));
	if (!newline)
		ft_error(st, 1);
	while (z < i)
	{
		newline[z] = st->splited[index][z];
		z++;
	}
	i += j;
	while (st->splited[index][i])
		newline[z++] = st->splited[index][i++];
	newline[z] = '\0';
	if (st->splited[index])
		free(st->splited[index]);
	st->splited[index] = newline;
	return (-1);
}

int	ft_swap_env(t_struct *st, int index, int i)
{
	char	*name;
	int		j;
	int		tmp;
	char	*str;

	tmp = i + 1;
	if (ft_checkenv_d_pars(&st->splited[index][i]) == 2)
		return (ft_swap_ask(st, index, i));
	else if (ft_isdigit(st->splited[index][i + 1]))
		return (ft_enver(st, index, i, 2));
	else if (ft_checkenv_d_pars(&st->splited[index][i]))
		return (0);
	while (ft_isalnum(st->splited[index][tmp]) && st->splited[index][tmp])
		tmp++;
	j = 1 + (tmp - (i + 1));
	name = ft_substr(st->splited[index], i, j);
	name[ft_strlen(name) + 1] = '\0';
	name[ft_strlen(name)] = '=';
	str = find_env(name + 1, st);
	if (name != NULL)
		free(name);
	if (str == NULL)
		return (ft_enver(st, index, i, j));
	st->splited[index] = ft_import(st->splited[index], str, i, j);
	return (ft_strlen(str) - 1);
}

int	ft_check_pipes(t_struct *st)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	ft_where_is_quot(st->line[i], 1);
	while (st->line[i])
	{
		j = i;
		if (ft_where_is_quot(st->line[i], 0) == 0 && st->line[i] == '|')
		{
			flag = 0;
			while (st->line[j + 1] != '|' && st->line[j + 1])
			{
				if (st->line[j + 1] != ' ')
					flag = 1;
				j++;
			}
			if (flag == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_cutter(t_struct *st)
{
	int		i;
	char	*tmp;

	i = 0;
	while (st->commands[i])
	{
		tmp = ft_strtrim(st->commands[i], " ");
		if (st->commands[i])
			free(st->commands[i]);
		st->commands[i] = tmp;
		i++;
	}
}
