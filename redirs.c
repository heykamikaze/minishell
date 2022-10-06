/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:53:56 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 15:08:18 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_right_redir(char *cmd, t_struct *st)
{
	int	out;

	out = -1;
	(void)st;
	if (!ft_strncmp(cmd, ">>", 2))
	{
		while (*cmd == '>' || *cmd == ' ')
			cmd++;
		out = open(cmd, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else
	{
		while (*cmd == '>' || *cmd == ' ')
			cmd++;
		out = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	ft_set_write(NULL, out);
}

int	ft_left_redir(char *cmd, t_struct *st)
{
	close(st->pip.in);
	if (!ft_strncmp(cmd, "<<", 2))
	{
		while (*cmd == '<' || *cmd == ' ')
			cmd++;
		here_doc(cmd);
		st->pip.in = open(".tmp", O_RDONLY, 0777);
	}
	else
	{
		while (*cmd == '<' || *cmd == ' ')
			cmd++;
		st->pip.in = open(cmd, O_RDONLY, 0777);
		if (st->pip.in == -1)
		{
			ft_putstr_fd("msh: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(errno);
		}
	}
	return (st->pip.in);
}

void	here_doc(char *limiter)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(limiter, line) || !line)
		{
			close(fd);
			free(line);
			return ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return ;
}

int	open_file_h(char *redir, char *file, int flag)
{
	int	fd;

	fd = -2;
	if (!ft_strncmp(redir, ">>", 2) && file)
		fd = open(file, \
		O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (!ft_strncmp(redir, ">", 1) && file)
		fd = open(file, \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!flag)
		close(fd);
	return (fd);
}
