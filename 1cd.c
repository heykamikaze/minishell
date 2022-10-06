/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:51:02 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *var, t_struct *st)
{
	int		len;
	t_list	*dup;

	len = ft_strlen(var);
	dup = st->content;
	while (dup)
	{
		if (!ft_strncmp(dup->content, var, len))
			break ;
		dup = dup->next;
	}
	if (!dup)
		return (NULL);
	return (ft_strdup(dup->content + len));
}

int	ft_cd_minus(t_struct *st)
{
	char	*prev_dir;

	prev_dir = find_env("OLDPWD=", st);
	if (!prev_dir)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(prev_dir) != 0)
	{
		free(prev_dir);
		ft_error_cmd("cd: ", NULL, errno);
		return (1);
	}
	else
		return (ft_cd_minus_helper(prev_dir, st));
}

int	ft_cd_deep_helper(char *current_dir, t_struct *st, char **splited)
{
	char	cwd[PATH_MAX];
	char	*prev_dir;

	prev_dir = ft_strjoin("export OLDPWD=", current_dir);
	ft_export(prev_dir, st);
	free(prev_dir);
	free(current_dir);
	getcwd(cwd, PATH_MAX);
	current_dir = ft_strjoin("export PWD=", cwd);
	ft_export(current_dir, st);
	free(current_dir);
	ft_myfree(splited);
	set_envp(st);
	return (0);
}

int	ft_cd_helper(t_struct *st, char **splited)
{
	char	*current_dir;

	current_dir = find_env("PWD=", st);
	if (chdir(splited[1]) != 0)
	{
		free(current_dir);
		ft_error_cmd("cd", splited[1], errno);
		ft_myfree(splited);
		return (1);
	}
	else
		return (ft_cd_deep_helper(current_dir, st, splited));
}

int	ft_cd(char *args, t_struct *st)
{
	char	**splited;

	splited = ft_split_wquots(args);
	if (splited[1] == NULL)
	{
		ft_myfree(splited);
		return (chdir("/"));
	}
	else if (!ft_strcmp(splited[1], "-"))
	{
		ft_myfree(splited);
		return (ft_cd_minus(st));
	}
	else
		return (ft_cd_helper(st, splited));
}
