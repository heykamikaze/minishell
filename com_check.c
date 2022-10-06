/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:52:02 by ksaffron          #+#    #+#             */
/*   Updated: 2022/07/21 10:44:44 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quot(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == 34 && (flag == 0 || flag == 1))
		{
			if (flag == 0)
				flag = 1;
			else if (flag == 1)
				flag = 0;
		}
		if (s[i] == 39 && (flag == 0 || flag == 2))
		{
			if (flag == 0)
				flag = 2;
			else if (flag == 2)
				flag = 0;
		}
		i++;
	}
	return (flag);
}

int	ft_semicolon(char **sst)
{
	int	i;
	int	j;

	i = 0;
	while (sst[i])
	{
		j = 0;
		ft_where_is_quot(sst[i][j], 1);
		while (sst[i][j])
		{
			if (ft_where_is_quot(sst[i][j], 0) == 0
				&& sst[i][j] == ';')
				return (1);
			j++;
		}	
		i++;
	}
	return (0);
}

int	check_space_inquot(t_struct *st)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	ft_where_is_quot (st->line[i], 1);
	while (st->line[i] == ' ')
		i++;
	while (st->line[i])
	{
		flag = ft_where_is_quot(st->line[i], 0);
		if ((flag != 0) && st->line[i] == ' ')
		{
			return (1);
		}
		else if ((flag == 0) && st->line[i] == ' ')
			return (0);
		i++;
	}
	return (0);
}

void	ft_opendollar(t_struct *st)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	ft_where_is_quot(' ', 1);
	while (st->splited[i])
	{
		j = 0;
		flag = ft_where_is_quot(st->splited[i][j], 1);
		while (st->splited[i][j])
		{
			flag = ft_where_is_quot(st->splited[i][j], 0);
			if (st->splited[i][j] == '$')
			{
				if (flag == 2)
					while (ft_isalnum(st->splited[i][j]) && st->splited[i][j])
						j++;
				else
					j += ft_swap_env(st, i, j);
			}
			j++;
		}
		i++;
	}
}

int	ft_com_check(t_struct *st)
{
	signal(SIGINT, sig_void);
	if (ft_quot(st->line))
		return (ft_error(st, 4));
	if (ft_check_pipes(st) || ft_check_reddir(st))
		return (ft_error(st, 4));
	st->splited = ft_split_up(st->line, "|");
	ft_changefirstcomm(st);
	if (ft_semicolon(st->splited))
	{
		ft_myfree(st->splited);
		return (ft_error(st, 4));
	}
	ft_opendollar(st);
	g_error = 0;
	if (!ft_add_pipe(st))
		return (ft_error(st, 1));
	ft_last_red(st, st->commands);
	ft_rebildredir(st);
	ft_cutter(st);
	st->commands = get_modif_arg(st->commands);
	st->commands = ft_maker_mass(st->commands);
	st->cmd = ft_createrofcmd(st);
	if (st->splited)
		free(st->splited);
	return (0);
}
