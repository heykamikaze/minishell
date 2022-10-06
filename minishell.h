/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:53:22 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 15:06:45 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "./libft_l/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# define BUFFER_SIZE 1

int	g_error;

typedef struct s_pip
{
	int	lpipe[2];
	int	rpipe[2];
	int	in;
	int	curr_index;
	int	last_herdoc;
}	t_pip;

typedef struct s_infor
{
	char	*line;
	char	**commands;
	char	***cmd;
	char	**splited;
	int		promptflag;
	int		argc;
	char	**argv;
	char	**env;
	int		exit;
	int		err;
	int		count;
	int		pid;
	int		*last_r;
	t_list	*content;
	t_pip	pip;
}	t_struct;

void		ft_pipex(char ***cmd, t_struct *st);
int			ft_strelki(char **cmd);
void		ft_mshfree_helper(int exc, t_struct *st);
void		ft_maker_left_redir(t_struct *st, int in);
void		ft_maker_for_do_lredir(char **cmd, int *lpipe, t_struct *st);
void		ft_maker_for_do_rredir(char **cmd, int *rpipe, t_struct *st);
void		ft_coommand_doing(char **cmd, int *rpipe, t_struct *st);
int			ft_check_buildins(char **cmd, t_struct *st, int count);
int			ft_get_counting_cmd(char ***cmd);
int			ft_cd_minus_helper(char *prev_dir, t_struct *st);
int			ft_cd(char *args, t_struct *st);
void		ft_exit(char *argv, t_struct *st);
void		ft_pwd(void);
void		ft_getting_env(t_struct *st);
int			ft_export(char *var, t_struct *st);
int			ft_unset(char *var, t_struct *st);
void		ft_echo(char *arg, t_struct *st);
void		ft_reinit_pip(t_struct *st);
void		ft_set_read(int *lpipe, int in);
void		ft_set_write(int *rpipe, int out);
void		ft_right_redir(char *cmd, t_struct *st);
int			ft_left_redir(char *cmd, t_struct *st);
void		here_doc(char *limiter);
char		*find_path(char *command, char **env);
void		execute(char *command, char **env, t_struct *st);
int			ft_pipe_util(char *arg, t_struct *st);
int			ft_mshfree1(t_struct *st, int code, int exc);
char		*ft_import(char *st, char *str, int i, int j);
int			ft_checkenv_d_pars(char *s);
int			ft_swap_ask(t_struct *st, int index, int i);
char		**ft_split_wquots(char *args);
int			set_envp(t_struct *st);
int			check_name_var(char *str);
void		ft_redirect(char *str, int *i);
void		ft_sig_void2(int signum);
void		ft_changefirstcomm(t_struct *st);
void		ft_error_cmd(char *cmd, char *arg, int status);
char		**get_modif_arg(char **argv);
char		*ft_rebilder(t_struct *st, int i, int len, int index);
char		**ft_split_up(char *s, char *c);
size_t		ft_word_count_up(char *s, char *c, int code);
char		**ft_mmyfree(char **str);
void		ft_bzero(void *s, size_t n);
void		ft_init(t_struct *st, int argc, char **argv, char **envp);
int			ft_skip(t_struct *st);
void		ft_putstr(char *s);
int			ft_com_check(t_struct *st);
int			ft_error(t_struct *st, int code);
int			ft_strcmp(char *s1, char *s2);
int			ft_strchr_up(char *b, char *c);
int			ft_parser_split_helper(char *s, int i, char *c, int code);
void		ft_com_split(t_struct *st);
char		*find_path(char *command, char **env);
char		*pipe_to_string(t_struct *st, int *i, int *j);
int			ft_where_is_quot(char s, int code);
int			ft_swap_env(t_struct *st, int index, int i);
char		**ft_split_pars_up(char *args);
size_t		ft_word_count_l(char *s, char c);
int			ft_add_pipe(t_struct *st);
int			ft_check_pipes(t_struct *st);
char		*find_env(char *var, t_struct *st);
int			ft_check_reddir(t_struct *st);
void		ft_rebildredir(t_struct *st);
int			find_name_len(char *s, int i, char c);
char		*ft_gnlstrjoin(char *remains, char *buffer);
char		*ft_skipsimic(char *s);
int			open_file_h(char *redir, char *file, int flag);
int			ft_openning_file(char *redir, char *file, int flag);
void		ft_cutter(t_struct *st);
int			ft_checkenv_d(char *s);
int			ft_bad_env(t_struct *st, int index);
void		sig_void(int sig);
void		sig_handler(int sig);
void		ft_sigex(t_struct *st);
int			ft_quot(char *s);
char		**ft_maker_mass(char **arr);
char		***ft_createrofcmd(t_struct *st);
void		ft_convert_error(int status);
int			ft_strrchr_upred(char *s, int c);
int			ft_set_in(t_struct *st, int in);
void		ft_last_red(t_struct *st, char **s);
int			ft_getlen(char *splited);
int			ft_changevar(char **splited, t_list **content, int len);
int			ft_parser_split_helper2(char *s, int i, char *c, int code);
int			ft_space_check(char *s);

#endif