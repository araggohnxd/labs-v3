#include "monitoring.h"

void	parse_output(t_protocol *node, char *output, int log_fd)
{
	time_t now = time(NULL);
	char *time = ctime(&now);
	int stdout_backup = dup(STDOUT);

	time[strlen(time) - 1] = '\0';
	dup2(log_fd, STDOUT);
	if (node->protocol == HTTP)
		http_output_parsing(node, output, time, stdout_backup);
	if (node->protocol == PING)
		ping_output_parsing(node, output, time, stdout_backup);
	if (node->protocol == DNS)
		dns_output_parsing(node, output, time, stdout_backup);
}
