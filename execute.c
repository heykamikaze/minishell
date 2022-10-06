/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:24 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_helper(char *command)
{
	int	len;

	len = ft_strlen(command);
	while (len && command[len] != '/')
		len--;
	if (len == 0)
		return (NULL);
	return (command);
}

char	*find_path_deep_helper(char *command, char **paths)
{
	char	*path;
	char	*path_command;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path_command = ft_strjoin(path, command);
		if (path)
			free(path);
		if (!access(path_command, 0))
			return (path_command);
		i++;
		if (path_command)
			free(path_command);
	}
	return (NULL);
}

char	*find_path(char *command, char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	if (env[i])
		paths = ft_split((env[i] + 5), ':');
	else
		return (NULL);
	if (!access(command, 0))
		return (find_path_helper(command));
	if (command[0] == '/')
		return (command);
	return (find_path_deep_helper(command, paths));
}

void	ft_print_err_exec(char **command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	execute(char *command, char **env, t_struct *st)
{
	char	**r_command;
	char	*path;

	if (!ft_pipe_util(command, st))
	{
		r_command = ft_split_wquots(command);
		if (!ft_strncmp("exit ", r_command[0], 5) \
		|| !ft_strncmp("exit", r_command[0], 5))
		{
			if (r_command[1])
				exit(ft_atoi(r_command[1]));
			exit(0);
		}
		path = find_path(r_command[0], env);
		if (!path)
			ft_print_err_exec(r_command);
		execve(path, r_command, env);
		ft_error_cmd(r_command[0], r_command[1], errno);
	}
	exit(errno);
}
