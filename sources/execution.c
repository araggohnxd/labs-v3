#include "monitoring.h"

static void	child_process_routine(t_protocol *node, int *pipe_fd, int log_fd)
{
	close(log_fd);
	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT);
	if (node->protocol == HTTP)
		if (execlp("curl", "curl", node->address, "-sIX", node->method, NULL) < 0)
			exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
	if (node->protocol == PING)
		if (execlp("ping", "ping", "-W1", "-c1", node->address, NULL) < 0)
			exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
	if (node->protocol == DNS)
		if (execlp("dig", "dig", node->dns_server, node->address, "+noall", "+stats", "+answer", NULL) < 0)
			exit(fprintf(stderr, "monitoring: execlp: %s\n", strerror(errno)));
}

static void	parent_process_routine(t_protocol *node, int *pipe_fd, int log_fd)
{
	char *line;
	char *output = strdup("");

	close(pipe_fd[WRITE]);
	while (TRUE)
	{
		line = ft_gnl(pipe_fd[READ]);
		if (!line)
			break;
		output = ft_strjoin_free_null(&output, &line);
		ft_memfree((void *) &line);
	}
	parse_output(node, output, log_fd);
	ft_memfree((void *) &output);
	close(pipe_fd[READ]);
	wait(NULL);
	sleep(node->interval);
}

static void	protocol_handler(t_protocol *node, int log_fd)
{
	pid_t pid;
	int pipe_fd[2];

	while (g_loop_condition)
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

	signal(SIGINT, sigint);
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
