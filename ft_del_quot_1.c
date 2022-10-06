/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_quot_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:37 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delquot(char *s, char *nl)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] == 34)
		{
			j++;
			while (s[j] != 34 && s[j])
				nl[i++] = s[j++];
		}
		else if (s[j] == 39)
		{
			j++;
			while (s[j] != 39 && s[j])
				nl[i++] = s[j++];
		}
		if (s[j] == 34 || s[j] == 39)
			j++;
		nl[i++] = s[j++];
	}
	nl[i] = '\0';
}

void	ft_swap_string(t_struct *s, int x, char *k)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (s->splited[x][i] == ' ' && s->splited[x][i])
		i++;
	while (s->splited[x][i] != ' ' && s->splited[x][i])
		i++;
	tmp = ft_substr(s->splited[x], i, (ft_strlen(s->splited[x]) - i));
	tmp2 = ft_strjoin(k, tmp);
	if (s->splited[x])
		free(s->splited[x]);
	if (tmp)
		free(tmp);
	if (k)
		free(k);
	s->splited[x] = tmp2;
}

void	ft_changefirstcomm(t_struct *st)
{
	int		i;
	char	**tmp;
	char	*tmp2;
	char	*nl;

	i = 0;
	while (st->splited[i])
	{
		tmp = ft_split(st->splited[i], ' ');
		if (ft_quot(tmp[0]) == 0)
		{
			if (ft_strrchr(tmp[0], 34) || ft_strrchr(tmp[0], 39))
			{
				nl = malloc(sizeof(char) * (ft_strlen(tmp[0]) - 1));
				if (nl == NULL)
					ft_error(st, 1);
				ft_delquot(tmp[0], nl);
				tmp2 = nl;
				ft_swap_string(st, i, tmp2);
			}
		}
		ft_myfree(tmp);
		i++;
	}
}

int	check_name_var_pars(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str))
		if (*str != '_')
			return (0);
	while (str && *str && *str != '=' && *str != '$'
		&& *str != 34 && *str != 39)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	ft_checkenv_d_pars(char *s)
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
	if (check_name_var_pars(tmp + 1) == 0)
	{
		if (tmp)
			free(tmp);
		return (1);
	}
	if (tmp)
		free(tmp);
	return (0);
}
