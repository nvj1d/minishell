# minishell

### the structre of variables:  
this is the sructure of our shell wich will be our only global variable:  
```c
typedef struct s_minishell  
{  
	int				stdin; //fd input 
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
```
the declaration of the variable (in the header) will be like this:  
```c
t_minishell g_shell;  
```	
the envirement strcture will be like this:  
```c 
typedef struct s_env_list  
{
	char				*key; //the identifier of the env variable  
	char				*val; //the value -- key:val  
	int					equal;  
	struct s_env_list	*next; //the next env variable  
}				t_env_list;  
```
and this is the structure of our command:  
```c
typedef struct s_cmd
{
	char			**args; //the arguments of the command
	int				pipe_in;
	int				pipe_out;
	t_redir			*redir_in;
	t_redir			*redir_out;
	struct s_cmd	*next; // the next one 
}				t_cmd;
```

### in the main :  

