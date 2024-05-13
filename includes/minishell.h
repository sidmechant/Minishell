/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ajjo <ael-ajjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:47:49 by ael-ajjo          #+#    #+#             */
/*   Updated: 2022/09/29 05:44:56 by ael-ajjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define NO_EXIT 21

# define MINISHELL "Minishell - $> "

extern int	g_exitcode;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_pars
{
	int				pipefd[2];
	int				savefd[2];
	struct s_env	*env;
	struct s_cmd	*command;
}				t_pars;

typedef struct s_cmd
{
	int				status;
	pid_t			cmd_pid;
	char			**agr;
	int				infile;
	int				outfile;
	int				redi;
	int				arg;
	int				files;
	int				cmd;
	char			*strcmd;
	char			*strarg;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	struct s_pars	*pars;
}				t_cmd;

typedef struct s_iter
{
	int	i;
	int	j;
}				t_iter;

typedef struct s_norme
{
	char	**strs;
	char	**tmp;
}				t_norme;

//------------------------------------------------------------------//
//						In folder : builtins						//
//------------------------------------------------------------------//

/***** In file : cd.c *****/
void			cd_error_msgs(char *arg, int error);
void			free_buffers(char *s1, char *s2);
int				is_pwd(char *str);
void			update_pwd(t_pars *pars);
void			ft_cd(t_pars *pars, t_cmd *current);
/***** In file : echo.c *****/
int				check_echo_n(char *str);
void			ft_echo(t_pars *pars, t_cmd *current);
/***** In file : env.c *****/
void			ft_env(t_pars *pars, t_cmd *current);
/***** In file : exit.c *****/
int				get_exitcode(char *str);
int				check_digit(char *str);
void			exit_program(t_pars *pars, t_cmd *current, int optno);
void			ft_exit(t_pars *pars, t_cmd *current);
/***** In file : export.c *****/
void			replace_variable(t_pars *pars, char *arg, t_env *ptr);
void			add_variable(t_pars *pars, char *arg);
int				check_forbidden_export_variable(char *arg);
int				search_export_variable(t_pars *pars, char *arg);
void			ft_export(t_pars *pars, t_cmd *current);
/***** In file : pwd.c *****/
void			ft_pwd(t_pars *pars, t_cmd *current);
/***** In file : unset.c *****/
int				check_forbidden_env_variable(char *arg);
void			remove_variable(t_pars *pars, t_env *ptr);
int				search_env_variable(t_pars *pars, char *arg);
void			ft_unset(t_pars *pars, t_cmd *current);

//------------------------------------------------------------------//
//						In folder : execution						//
//------------------------------------------------------------------//

/***** In file : exec_1.c *****/
void			exec_command_line(t_pars *pars, char *s);
void			wait_processes(t_pars *pars);
void			pipe_manipulation(t_pars *pars, t_cmd *current, int cmd_nbr);
void			exec_child(t_pars *pars, t_cmd *current, int cmd_nbr, char *s);
void			exec_command(t_pars *pars, t_cmd *current);
/***** In file : exec_2.c *****/
int				is_builtin(char *check);
int				count_command(t_pars *pars);
t_cmd			*last_command(t_pars *pars);
void			create_pipe(t_pars *pars, t_cmd *current, int cmd_nbr);
/***** In file : exec_3.c *****/
void			exec_builtin(t_pars *pars, t_cmd *current);
void			exec_builtin_inout(t_pars *pars, t_cmd *current);
void			exec_builtin_in(t_pars *pars, t_cmd *current);
void			exec_builtin_out(t_pars *pars, t_cmd *current);
void			solo_builtin(t_pars *pars, t_cmd *current);
/***** In file : exec_4.c *****/
void			exec_failed_1(t_pars *pars, t_cmd *cmd, char **strs, int error);
void			exec_failed_2(t_pars *pars, t_cmd *cmd, char **strs, int error);
char			*find_path(char **paths, t_cmd *current);
char			*command_with_path(t_pars *pars, t_cmd *current);
/***** In file : exec_5.c *****/
void			duplicate_solo_cmd(t_pars *pars, t_cmd *current);
void			duplicate_first(t_pars *pars, t_cmd *current);
void			duplicate_last(t_pars *pars, t_cmd *current);
void			duplicate_normal_1(t_pars *pars, t_cmd *current);
void			duplicate_normal_2(t_pars *pars, t_cmd *current);
/***** In file : exec_6.c *****/
char			**transform_empty_env(void);
char			**transform_duplicate(t_env *tmp, char **strs, int size);
char			**transform_env(t_env *env);
void			exec_slash_command(t_pars *pars, t_cmd *current);
void			close_in_child(t_pars *pars);
void			close_out_child(t_pars *pars);

//------------------------------------------------------------------//
//						In folder : parsing							//
//------------------------------------------------------------------//

/***** In file : lexer.1.c *****/
int				negative_expand(char *str, int i);
int				ft_check_expand(char *str, char c, int i);
int				ft_negative_quote(char *str);
int				lex_quote(char *str);
int				lexer_shell(char **str, t_pars *pars);
/***** In file : lexer.2.c *****/
int				lex_pipe(char *str);
int				lexer_redi(char *str);
int				lexer_last_redi(char *str);
int				lexer_redi_pipe(char *str);
int				lexer_redirection_char(char *str);
/***** In file : lexer_3.c *****/
int				lexer_sens(char *str);
int				lexer_tripleredi(char *str);
/***** In file : parser_1.c *****/
int				ft_replace_neg(char *str);
char			*ft_replace(char *str, char *node, int i, int j);
char			*ft_replace_exitcode(char *str, int i, int j, t_pars *pars);
char			*ft_init_pars(char *str, t_pars *pars);
char			*ft_init_pars2(char *str, t_pars *pars);
/***** In file : parser_2.c *****/
char			*ft_save_pos_expand(char *str, int i, int j, t_pars *pars);
/***** In file : token_1.c *****/
int				id_files(char *str, int *c, int i, t_cmd *cmd);
int				id_redir(char *str, int *c, int i, t_cmd *cmd);
int				ft_negative_char(char *str);
t_cmd			*command_attribution(t_pars *pars, t_cmd *cmd);
void			token(char *str, t_cmd **cmd, t_pars *pars);
/***** In file : token_2.c *****/
void			open_double_infile(char *limit, t_cmd *cmd, int exp, char *s);
char			*ft_positive_token(char *str, t_cmd *cmd);
void			openfiles(char *str, int c, int j, t_cmd *cmd);
int				ft_positive_char(char *str);
char			*recup_token(char *str);
/***** In file : token_3.c *****/
void			fill_tab_exec(t_cmd *cmd, t_pars *pars);
void			saves_arg(char *str, int i, int j, t_cmd *cmd);
int				id_arg(char *str, int i, char c, t_cmd *cmd);
void			saves_cmd(char *str, int i, int j, t_cmd *cmd);
int				id_cmd(char *str, int i, char c, t_cmd *cmd);

//------------------------------------------------------------------//
//						In folder : sources							//
//------------------------------------------------------------------//

/***** In file : main.c *****/
t_env			*get_environment(char **envp);
void			initialize_struct(t_pars *pars);
int				check_eof_or_void(char *str, t_env **envp);
void			file_error(t_pars *pars, t_cmd *current, int cmd_nbr);
/***** In file : signals.c *****/
void			sigint_handler(int status);
void			child_signal_return(int signum, t_cmd *current, int *flag);
char			*ft_init_pars2(char *str, t_pars *pars);
/***** In file : norme.c *****/
int				pospos(char *str, char *c);
void			open_single_outfile(char *str, t_cmd *cmd, char *tmp);
void			open_single_infile(char *str, t_cmd *cmd, char *tmp);
void			open_double_outfile(char *str, t_cmd *cmd, char *tmp);
int				norme_init(t_norme *tab, int l);
/***** In file : normal.c *****/
void			free_norme_1(char *s1, char *s2, char *s3);
void			norme_random(char *str, t_pars *pars);
void			ft_bzero(void *ptr, size_t n);
void			argus(int ac, char **av);
void			norme_chelou(char *str, t_cmd *cmd);
//------------------------------------------------------------------//
//						In folder : utils							//
//------------------------------------------------------------------//

/***** In file : compare_utils_1.c *****/
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*ft_strchr(char *str, int c);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
/***** In file : compare_utils_2.c *****/
int				ft_isquote(int c);
char			if_quote(char c, int *i);
int				check_space(char *str);
int				find_slash(char *str);
int				ft_strcmpenv(char *str, char *env, int len);
/***** In file : compare_utils_3.c *****/
int				is_equal(char *str);
int				find_export_variable(char *arg, char *variable);
int				find_env_variable(char *arg, char *variable);
/***** In file : free_utils.c *****/
void			env_list_clear(t_env **envp);
void			cmd_list_clear(t_cmd **cmds);
void			all_clear(t_pars *pars, int flag);
char			**free_strs(char **ptr);
char			**ft_free(char **tab, int i);
/***** In file : list_utils.c *****/
t_env			*ft_lstnew(char *str);
void			ft_lstadd_back(t_env **alst, t_env *new);
t_env			*ft_lstlast(t_env *lst);
/***** In file : malloc_utils_1.c *****/
int				ft_strlen(char *str);
char			*ft_strdup(char *s);
int				ft_charsize(long n);
char			*ft_fill(char *str, int len, long nb);
char			*ft_itoa(int n);
/***** In file : malloc_utils_2.c *****/
int				ft_words(char *str);
char			*ft_catchwords(char *str);
int				ft_cntword(char const *s, char c, int n);
char			**ft_split(char *s);
char			**ft_split2(char *s, char c);
/***** In file : malloc_utils_3.c *****/
char			**secure_split_paths(char **strs, int n);
int				ft_wordcount(char const *str, char c);
char			*ft_strndup(char const *src, int j, int *index);
char			**ft_fill_split(char const *s, char c, char **strs);
char			**ft_split_paths(char const *s, char c);
/***** In file : malloc_utils_4.c *****/
int				ft_strlen(char *str);
int				ft_lengood(char *str, unsigned int len, unsigned int s);
char			*ft_substr(char *s, unsigned int start, unsigned int len);
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2);
/***** In file : print_utils.c *****/
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			write_util(int count);
char			*ft_create(char *tmp, t_cmd *cmd);
char			*malloc_void(t_cmd *cmd);
void			open_double_infile_2(char *limit, t_cmd *cmd, char *s);
void			norme_print(t_cmd *cmd, char *input);

#endif