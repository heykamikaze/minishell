/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:53:06 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_struct *st)
{
	char	*tmp;
	int		num;
	char	*digit;

	tmp = find_env("SHLVL=", st);
	num = ft_atoi(tmp) + 1;
	free(tmp);
	digit = ft_itoa(num);
	tmp = ft_strjoin("export SHLVL=", digit);
	free(digit);
	ft_export(tmp, st);
	free(tmp);
}

void	ft_init(t_struct *st, int arg1, char **arg2, char **arg3)
{
	int	i;

	i = -1;
	st->line = NULL;
	st->commands = NULL;
	st->splited = NULL;
	st->promptflag = 1;
	st->argc = arg1;
	st->argv = arg2;
	st->env = NULL;
	st->exit = 0;
	g_error = 0;
	st->pip.lpipe[0] = -1;
	st->pip.lpipe[1] = -1;
	st->pip.rpipe[0] = -1;
	st->pip.rpipe[1] = -1;
	st->content = NULL;
	st->pip.in = -1;
	st->last_r = NULL;
	st->pip.curr_index = 0;
	while (arg3[++i])
		if (ft_strncmp(arg3[i], "OLDPWD=", 7))
			ft_lstadd_back(&(st->content), ft_lstnew(ft_strdup(arg3[i])));
	set_shlvl(st);
	rl_catch_signals = 0;
}

void	ft_sigex(t_struct *st)
{
	ft_putstr("exit\n");
	if (st->line)
		free(st->line);
	if (st->commands)
		ft_myfree(st->commands);
	exit(1);
}
