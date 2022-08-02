#include "monitoring.h"

static void	exit_error(char **split, t_list *list, int fd, const char *error_msg, t_info_index error_id)
{
	if (error_msg)
	{
		fprintf(stderr, "monitoring: ");
		fprintf(stderr, error_msg, split[error_id]);
		fprintf(stderr, "\n");
	}
	ft_free_matrix((void *) &split);
	ft_lstclear(&list, free_protocol_node);
	close(fd);
	exit(EXIT_FAILURE);
}

static t_bool	validate_method(char *method)
{
	return(strcmp(method, "GET") == 0
		|| strcmp(method, "HEAD") == 0
		|| strcmp(method, "POST") == 0
		|| strcmp(method, "PUT") == 0
		|| strcmp(method, "DELETE") == 0
		|| strcmp(method, "CONNECT") == 0
		|| strcmp(method, "OPTIONS") == 0
		|| strcmp(method, "TRACE") == 0
		|| strcmp(method, "PATCH") == 0);
}

static t_bool	validate_config(t_protocol_type protocol, char **split)
{
	const size_t split_size = get_split_size(split);

	if ((protocol == HTTP && split_size != 6)
	|| (protocol == PING && split_size != 4)
	|| (protocol == DNS && split_size != 5))
		return (!fprintf(stderr, "monitoring: invalid amount of columns in %s config\n", split[INDEX_PROTOCOL]));
	if ((protocol == HTTP && !is_numeric_str(split[HTTP_INDEX_INTERVAL]))
	|| ((protocol == PING || protocol == DNS) && !is_numeric_str(split[INDEX_INTERVAL])))
		return (!fprintf(stderr, "monitoring: %s interval should contain numbers only\n", split[INDEX_PROTOCOL]));
	if (protocol == HTTP && !is_numeric_str(split[HTTP_INDEX_CODE]))
		return (!fprintf(stderr, "monitoring: HTTP code should contain numbers only\n"));
	if (protocol == HTTP && !validate_method(split[HTTP_INDEX_METHOD]))
		return (!fprintf(stderr, "monitoring: %s is not a valid HTTP method\n", split[HTTP_INDEX_METHOD]));
	return (TRUE);
}

t_list	*parse_config_file(int fd)
{
	char *line;
	char **split;
	t_list *parsed_configs = NULL;
	t_protocol_type protocol = ERROR;

	while (TRUE)
	{
		line = ft_gnl(fd);
		if (!line)
			break;
		line = ft_strtrim_free(&line, "\n");
		if (*line == '\0' || *line == '#')
		{
			ft_memfree((void *) &line);
			continue;
		}
		split = ft_split(line, '\t');
		ft_memfree((void *) &line);
		protocol = get_protocol_type(split[INDEX_PROTOCOL]);
		if (!protocol)
			exit_error(split, parsed_configs, fd, "%s is not a valid protocol", INDEX_PROTOCOL);
		if (!validate_config(protocol, split))
			exit_error(split, parsed_configs, fd, NULL, 0);
		if (!parsed_configs)
			parsed_configs = ft_lstnew(create_protocol_node(protocol, split));
		else
			ft_lstadd_back(&parsed_configs, ft_lstnew(create_protocol_node(protocol, split)));
		ft_free_matrix((void *) &split);
	}
	return (parsed_configs);
}
