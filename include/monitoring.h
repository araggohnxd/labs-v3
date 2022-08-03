#ifndef MONITORING_H
# define MONITORING_H

# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define PURPLE "\e[1;35m"
# define CYAN "\e[1;36m"
# define RESET "\e[0m"

# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <time.h>

typedef enum e_pipe_end {
	READ,
	WRITE
}	t_pipe_end;

typedef enum e_protocol_type {
	ERROR,
	HTTP,
	PING,
	DNS
}	t_protocol_type;

typedef enum e_info_index {
	INDEX_NAME,
	INDEX_PROTOCOL,
	INDEX_ADDRESS,
	INDEX_INTERVAL,
	HTTP_INDEX_METHOD = 3,
	DNS_INDEX_SERVER,
	HTTP_INDEX_CODE = 4,
	HTTP_INDEX_INTERVAL
}	t_info_index;

typedef struct s_protocol {
	t_protocol_type	protocol;
	char *name;
	char *address;
	char *method;
	char *dns_server;
	long code;
	int interval;
}	t_protocol;

/* parsing */
t_list	*parse_config_file(int fd);
void	parse_output(t_protocol *node, char *output, int log_fd);
void	http_output_parsing(t_protocol *node, char *output, char *time, int stdout_backup);
void	ping_output_parsing(t_protocol *node, char *output, char *time, int stdout_backup);
void	dns_output_parsing(t_protocol *node, char *output, char *time, int stdout_backup);

/* simplify */
int	simplify_log_file(void);

/* protocol node */
t_protocol	*create_protocol_node(t_protocol_type protocol, char **split);
void	free_protocol_node(void *node);

/* execution */
int	exec_protocol(t_list *configs);

/* utils */
t_bool	is_numeric_str(char *str);
size_t	get_split_size(char **split);
t_protocol_type	get_protocol_type(char *str);
void nullify_newline(char *str);

#endif /* MONITORING_H */
