#ifndef MONITORING_H
# define MONITORING_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef enum e_status {
	FAILED,
	SUCCESS
}	t_status;

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
	char *interval;
	char *method;
	char *code;
	char *dns_server;
}	t_protocol;

/* config file parsing */
t_list			*parse_config_file(int fd);

/* protocol node */
t_protocol		*create_protocol_node(t_protocol_type protocol, char **split);
void			free_protocol_node(void *node);

/* utils */
t_bool			is_numeric_str(char *str);
size_t			get_split_size(char **split);
t_protocol_type	get_protocol_type(char *str);


#endif /* MONITORING_H */
