#include "monitoring.h"

void	child_process_routine(t_protocol *node, int *pipe_fd, int log_fd)
{
	close(log_fd);
	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT);
	ft_printf("\n\n=== Statistics regarding \"%s\" config ===\n", node->name);
	if (node->protocol == HTTP)
		if (execlp("curl", "curl", node->address, "-sIX", node->method, NULL) < 0)
			exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
	if (node->protocol == PING)
		if (execlp("ping", "ping", "-c", "1", node->address, NULL) < 0)
			exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
	if (node->protocol == DNS)
		if (execlp("dig", "dig", node->dns_server, node->address, NULL) < 0)
			exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
}

void	parent_process_routine(t_protocol *node, int *pipe_fd, int log_fd)
{
	char *line;
	char *output = NULL;

	close(pipe_fd[WRITE]);
	dup2(log_fd, STDOUT);
	while (TRUE)
	{
		line = ft_gnl(pipe_fd[READ]);
		if (!line)
			break;
		if (!output)
			output = strdup(line);
		else
			output = ft_strjoin_free(&output, &line);
		ft_memfree((void *) &line);
	}
	ft_putstr_fd(output, STDOUT);
	ft_memfree((void *) &output);
	close(pipe_fd[READ]);
	wait(NULL);
	sleep(node->interval);
}

void	protocol_handler(t_protocol *node, int log_fd)
{
	pid_t pid;
	int pipe_fd[2];

	while (TRUE)
	{
		if (pipe(pipe_fd) < 0)
			exit(fprintf(stderr, "monitoring: pipe: %s\n", strerror(errno)));
		pid = fork();
		if (pid < 0)
			exit(fprintf(stderr, "monitoring: fork: %s\n", strerror(errno)));
		else if (pid == 0)
			child_process_routine(node, pipe_fd, log_fd);
		else
			parent_process_routine(node, pipe_fd, log_fd);
	}
}

int	exec_protocol(t_list *configs)
{
	t_protocol *protocol_node;
	pid_t *pid;
	int log_fd;
	size_t index;
	size_t config_amount = ft_lstsize(configs);

	if ((log_fd = open("monitoring.log", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (fprintf(stderr, "monitoring: monitoring.log: %s\n", strerror(errno)));
	pid = (pid_t *) calloc(config_amount, sizeof(pid_t));
	for (index = 0; index < config_amount; index++)
	{
		protocol_node = (t_protocol *) configs->content;
		pid[index] = fork();
		if (pid[index] < 0)
			return (fprintf(stderr, "monitoring: fork: %s\n", strerror(errno)));
		else if (pid[index] == 0)
			protocol_handler(protocol_node, log_fd);
		configs = configs->next;
	}
	for (index = 0; index < config_amount; index++)
		waitpid(pid[index], NULL, 0);
	free(pid);
	close(log_fd);
	return (TRUE);
}

int	main(void)
{
	int config_fd;
	t_list *parsed_configs;

	config_fd = open("monitoring.db", O_RDONLY);
	if (config_fd < 0)
	{
		fprintf(stderr, "monitoring: monitoring.db: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	parsed_configs = parse_config_file(config_fd);
	close(config_fd);
	if (parsed_configs)
		exec_protocol(parsed_configs);
	ft_lstclear(&parsed_configs, free_protocol_node);
	return (EXIT_SUCCESS);
}
