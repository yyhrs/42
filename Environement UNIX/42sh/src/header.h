/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:28 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/18 17:47:39 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define BUFF_SIZE 100
# define HASH_SIZE 4096

/*
** AINSI escape code
*/
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define END "\033[0m"

# define UL_ON "\033[4m"
# define UL_OFF "\033[24m"
# define CURSOR_BACK "\033[D"
# define CURSOR_NEXT "\033[C"
# define CURSOR_DOWN "\033[B"
# define CURSOR_UP "\033[A"

/*
** Predifined text
*/

# define SH_NAME "\033[1;35m[42SH]\033[0m "

/*
** Touch define
*/

# define HOMEND (input[0] == 0x1B \
				&& input[1] == 0x5B && (input[2] == 0x48 || input[2] == 0x46) \
				&& input[3] == '\0')

/*
**CHAR
*/
# define CHAR_S(c) (c == '"' || c == '\'' || c == '`')
# define CHAR_END(c) (!(c) || c == ' ' || c == '\\')

/*
** 								STRCUTURE DEFINITION
**
**
**	s_parse:
**			Used in parser function. Split the line. Erease space, tab, and all
**		extra.
**
**	s_data:
**			Used for make a path tab, in function path_control. It used with an
**		hash system from HOTRACE.
**
**	t_handler:
**			Used for builtin, stock the address of builtin function.
**
**	s_builtin_cmd:
**			Used for builtin tab, where name of builtin and he's function are
**		stocked.
**
**	s_seq:
**			Used for make a list of all command present in a same line. If there
**		are no path to a function, maybe it's a builtin.
**
**	s_cmd:
**			Used for history.
**
**	s_input:
**			Used in read and prompt function.
**
**	s_control:
**			Used to know if the syntax of sequence is correct. (Word after a
**		pipe, etc).
**
*/

typedef struct		s_list
{
	char			*key;
	char			*data;
	struct s_list	*next;
}					t_list;

typedef struct		s_parse
{
	char			*word;
	struct s_parse	*next;
}					t_parse;

typedef struct		s_data
{
	char			*cmd;
	char			*path;
	struct s_data	*right;
}					t_data;

typedef void		(*t_handler)();

typedef struct		s_builtin_cmd
{
	char			*name;
	t_handler		handler;
}					t_builtin_cmd;

typedef struct		s_seq
{
	char			*cmd;
	char			*path;
	t_handler		func;
	char			*args;
	char			*extra;
	char			**exec_tab;
	char 			*file;
	int				fd[2];
	int				two[2];
	struct s_seq	*next;
	struct s_seq	*prev;
}					t_seq;

typedef struct		s_cmd
{
	char			*origin;
	char			*clean;
	t_seq			*seq;
	int				id;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_input
{
	char			*result;
	char			*save;
	int				cursor_pos;
	int				cursor_max;
}					t_input;

typedef struct		s_comp
{
	char			*choice;
	int				id;
	struct s_comp	*next;
	struct s_comp	*prev;
}					t_comp;

/*
** Builtin dir
*/

t_handler			ft_isfunc(char *cmd);
void				do_exit(t_seq *seq);
void				ft_cd(t_seq *seq);
void				ft_echo(t_seq *seq);
void				ft_read(t_seq *seq);
t_list				**ft_add_data(char *s);
void				ft_set(t_seq *seq);
void				ft_unset(t_seq *seq);

/*
** Cleaner dir
*/

void				ft_cleaner(t_data **path, t_cmd *cmd, int value);

/*
** Completion dir
*/

void				ft_completion(char *input, t_input *final);
void				ft_print_choice(t_comp *list, int i);
void				ft_free_list_comp(t_comp *list);

/*
** Cpy_cut_paste dir
*/

char				*ft_CCP_seq(t_input *final);

/*
** Cursor_motion dir
*/

char				*ft_check_key_LR(t_input *final, int value);
char				*print_word(t_input *final, char *input);
void				ft_clear_line(t_input *final);
void				ft_place_cursor(t_input *final);
void				ft_prev_word(t_input *final);
void				ft_next_word(t_input *final);
void				ft_next_line(t_input *final);
void				ft_prev_line(t_input *final);
int					ft_get_line_num(int value);

/*
** Error dir
*/

void				ft_error_malloc(void *value, char *msg);

/*
** Exec fir
*/

void				ft_launch(int do_fork, t_seq *seq);
void				ft_pipe(t_seq *seq);
int					ft_gotredirection(t_seq *cmd, char *str);
void				ft_redirection(t_seq *cmd);
void				ft_exec(t_seq *seq);

/*
** History dir
*/

int					ft_current_id(int more);
char				*ft_get_current_line(t_cmd *line);
char				*ft_get_env(char *s);

/*
** Lexer dir
*/

t_seq				*ft_recursive_lexer(char **tab, t_seq *seq, int tour);
t_seq				*ft_lexer(char *s);
t_seq				*ft_init_seq(void);

/*
** Memlib dir
*/

void				*ft_malloc(int s);
void				ft_free(void *var);
void				ft_free_data_hash(t_data **var);

/*
** Parser dir
*/

char				*ft_parse_clean(char *buffer);
t_parse				*ft_add_word(char *s, t_parse *final);
char				*ft_get_var(char *s);

/*
** Path_control dir
*/

void				ft_init_path(void);
int					ft_hash(char *key);
t_data				**ft_save_path_data(t_data **tab);
void				ft_set_node(char *cmd, char *path, t_data **tab);
char				*ft_cmdpath(char *cmd);

/*
** Program_main dir
*/

char				*ft_get_input(t_cmd *line);
int					ft_get_id(int more);
void				ft_add_elem(t_cmd *line);
char				*ft_read_input(char *buffer, int fd);

/*
** Prompt dir
*/

int					ft_prompt_len(int size);
void				ft_prompt(void);

/*
** Syntax dir
*/

int					ft_first_control_syntax(char *input);

/*
** Termods dir
*/

int					ft_restore(void);
int					ft_non_canonical(void);
int					ft_putchar_term(int c);
void				ft_signal(void);

/*
** Touch_control dir
*/

int					ft_key_up_or_down(char *buf);
int					ft_key_left_or_rigth(char *buf);
char				*ft_check_key(char *input, t_input *final, t_cmd *line);

/*
** UI dir
*/

void				ft_ui_central(void);

#endif /* !HEADER_H */
