#include "monitoring.h"

void	dns_handler(t_protocol *node, int log_fd)
{
	pid_t pid;
	int pipe_fd[2];
	char *dns_server;

	dns_server = ft_strjoin("@", node->dns_server);
	while (TRUE)
	{
		if (pipe(pipe_fd) < 0)
			exit(fprintf(stderr, "monitoring: pipe: %s\n", strerror(errno)));
		pid = fork();
		if (pid < 0)
			exit(fprintf(stderr, "monitoring: fork: %s\n", strerror(errno)));
		else if (pid == 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			// dup2(pipe_fd[1], STDOUT);
			if (execlp("dig", "dig", dns_server, node->address, NULL) < 0)
				exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		wait(NULL);
		sleep(node->interval);
	}
	close(log_fd);
}

void	ping_handler(t_protocol *node, int log_fd)
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
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			// dup2(pipe_fd[1], STDOUT);
			if (execlp("ping", "ping", "-c", "1", node->address, NULL) < 0)
				exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		wait(NULL);
		sleep(node->interval);
	}
	close(log_fd);
}

void	http_handler(t_protocol *node, int log_fd)
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
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			// dup2(pipe_fd[1], STDOUT);
			if (execlp("curl", "curl", node->address, "-IX", node->method, NULL) < 0)
				exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		wait(NULL);
		sleep(node->interval);
	}
	close(log_fd);
}

int	exec_protocol(t_list *configs)
{
	t_protocol *protocol_node;
	pid_t *pid;
	int log_fd;
	size_t index;
	size_t config_amount = ft_lstsize(configs);

	if ((log_fd = open("monitoring.log", O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
		return (fprintf(stderr, "monitoring: monitoring.log: %s\n", strerror(errno)));
	pid = (pid_t *) calloc(config_amount, sizeof(pid_t));
	for (index = 0; index < config_amount; index++)
	{
		protocol_node = (t_protocol *) configs->content;
		pid[index] = fork();
		if (pid[index] < 0)
			return (fprintf(stderr, "monitoring: fork: %s\n", strerror(errno)));
		else if (pid[index] == 0)
		{
			if (protocol_node->protocol == HTTP)
				http_handler(protocol_node, log_fd);
			else if (protocol_node->protocol == PING)
				ping_handler(protocol_node, log_fd);
			else if (protocol_node->protocol == DNS)
				dns_handler(protocol_node, log_fd);
		}
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
