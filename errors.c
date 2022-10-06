/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:19 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip(t_struct *st)
{
	if (st && st->line != NULL)
		free(st->line);
	return (0);
}

int	ft_error(t_struct *st, int code)
{
	if (code == 1)
	{
		ft_mshfree1(st, 1, -1);
		ft_putstr_fd("malloc error\n", 2);
		exit(1);
	}
	if (code == 3)
	{
		ft_putstr_fd("msh: syntax error near unexpected token '|'", 2);
		ft_putstr_fd("\n", 2);
	}
	if (code == 4)
	{
		ft_putstr_fd("minishell: parse error", 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}

void	ft_error_cmd(char *cmd, char *arg, int status)
{
	ft_convert_error(status);
	if (g_error == 110)
		ft_putstr_fd("Command not found\n", 2);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		if (arg)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
		if (status == 13)
			ft_putstr_fd("is a directory", 2);
		else
			ft_putstr_fd(strerror(status), 2);
	}
	write(2, "\n", 1);
}

void	ft_convert_error(int status)
{
	if (status == 2)
		g_error = 1;
	else if (status == 20)
		g_error = 1;
	else if (status == 13)
		g_error = 126;
	else
		g_error = status;
}
