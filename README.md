# minishell

this is the sructure of our shell wich will be our only global variable:  
`` sh
typedef struct s_minishell <br />  
{  
	int				stdin; //fd input <br/> 
	int				stdout; //fd output  
	char			**env; //2D envirement array  
	int				status; /* the status */   
	int				env_changed;  
	void			*temp;  
	int				**fds;  
	int				fd_write; //fd to write to   
	int				fd_read; //fd to read from  
	char			**builtin_names; //the names of our funcs  
	void			(*builtin_funcs[7])(void); // array of our funcs  
	pid_t			*pids;  
	t_env_list		*env_list;  
	struct s_cmd	*cmd_list;  
	struct s_cmd	*cmd_list_head;  
}  			t_minishell;  
``
the declaration of the variable (in the header) will be like this:<br/>
`` sh
t_minishell g_shell;  
``
the envirement strcture will be like this:  
`` sh
typedef struct s_env_list  
{
	char				*key; //the identifier of the env variable  
	char				*val; //the value -- key:val  
	int					equal;  
	struct s_env_list	*next; //the next env variable  
}				t_env_list;  
``
