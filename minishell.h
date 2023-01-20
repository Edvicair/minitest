/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:43:04 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/20 11:51:08 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <curses.h>

typedef struct s_env
{
	bool			egal;
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_loc
{
	void			*garb;
	struct s_loc	*next;
}				t_loc;

typedef enum s_type
{
	NO_REDIR,
	RE_G,
	H_DOC,
	RE_D,
	RE_DD,
}			t_type;

typedef struct s_redir
{
	t_type			type;
	char			*feldup;
	struct s_redir	*next;
}				t_redir;

typedef struct s_token
{
	t_redir			*redir;
	char			**cmd;
	int				child;
	struct s_token	*next;	
}				t_token;

typedef struct s_msh
{
	t_env	*env;
	char	*line;
	int		pip;
	int		fd[2];
	int		stin;
	int		in;
	int		out;
	int		*tab;
	t_token	*token;
}				t_msh;

						//PARSING//
int		is_quote(char *str);
int		split_what(char *str, int i, char quote);
int		parser(t_msh *msh);
int		strlen_quote(char *str, int min, int max);
int		find_quote(char *str, int min, int max);
int		is_pipe(char *str);
int		find_pipe(char *str, int i);
int		split_quote(char *str, int i, char quote);
int		is_quote(char *str);
int		strlen_quote(char *str, int min, int max);
int		pipe_error(char *line);
int		redir_error(char *line);
int		ft_strlen_redir(char *str);
char	**tokenizator(char *str, char c);
char	*ft_substr2(const char *s, int min, int max);
char	*space_chips(char *line);
char	*ft_substr_pipe(const char *s, unsigned int start, unsigned int end);
char	*ft_substr_redir(char *s);
t_redir	*redi_less(char *str);
t_redir	*ft_redir_last(t_redir *redir);
t_redir	*ft_redir_new(int R, char *word);
t_type	ft_choose_type(int R);
void	ft_redir_add_back(t_redir **redir, t_redir *new);
//void	freezer(t_token *token);
//int	tokenizator(char *str, t_token *token);

						// EXEC //
void	one_child(t_msh *msh, t_token *token, int i, int stin);
void	exec(t_msh *msh, char **cmd, char **env);
void	ft_check_redirection(t_msh *msh);

						// LIB //
size_t	ft_strlen(const char *s);
bool	ft_strshr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *nptr);
char	*ft_strjoin(t_msh *msh, char const *s1, char const *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
void	ft_free_double(char **s);
void	ft_free_env(t_env *env);

						// BUILT //
char	*ft_getenv(t_msh *msh, char *path);
void	ft_export_pwd(t_msh *msh, char *pwd, char *path);
void	ft_export(t_msh *msh, char **cmd);
void	ft_sort_export(t_msh *msh);
void	ft_unset(t_msh *msh, char **cmd);
void	ft_echo(t_msh *msh, char **cmd);
void	ft_exit(t_msh *msh, int stin);
void	ft_pwd(t_msh *msh);
void	ft_env(t_msh *msh);
void	ft_cd(t_msh *msh, char **cmd);

						// INIT //
char	**ft_split_space(char const *s);
void	ft_init_struct(t_msh *msh, char **env);
void	ft_env_add_back(t_env **env, t_env *new);
void	ft_loc_add_back(t_loc **loc, t_loc *new);
void	ft_free_token(t_msh *msh, t_token *token);
t_env	*ft_env_new(t_msh *msh, char *name, char *value, bool egal);
t_loc	*ft_loc_new(void *content);
t_loc	*ft_loc_last(t_loc *loc);
t_token	*ft_fill_token(t_msh *msh);
t_redir	*redi_less(char *str);

#endif
