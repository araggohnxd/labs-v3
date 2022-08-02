#include "monitoring.h"

static void	dns_simplified_output(t_protocol *node, char *output, char *time, int stdout_backup)
{
	size_t index = 0;
	size_t address_len = strlen(node->address);
	char *simplified = strdup("");
	char **split = ft_split(output, '\n');

	dup2(stdout_backup, STDOUT);
	while (strncmp(split[index], node->address, address_len) == 0)
		simplified = ft_strjoin_free(simplified, strdup(strrchr(split[index++], '\t')));
	ft_free_matrix((void *) &split);
	if (*simplified)
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s — %s ]%s\n%sProtocol:%s DNS\n%sStatus:%s %sHealthy%s\n%sResponse:%s%s\n\n",
			CYAN, time, node->name, node->address, (node->dns_server + 1), RESET,
			PURPLE, RESET, PURPLE, RESET, GREEN, RESET, PURPLE, RESET, simplified);
	else
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s — %s ]%s\n%sProtocol:%s DNS\n%sStatus:%s %sUnhealthy%s\n\n",
			CYAN, time, node->name, node->address, (node->dns_server + 1), RESET,
			PURPLE, RESET, PURPLE, RESET, RED, RESET);
	free(simplified);
}

static void	dns_output_parsing(t_protocol *node, char *output, int stdout_backup)
{
	time_t now = time(NULL);
	char *time = ctime(&now);
	char *healthy = strstr(output, node->address);

	time[strlen(time) - 1] = '\0';
	if (healthy)
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — %s ]\nProtocol: DNS\nStatus: Healthy\nResponse:\n%s",
			time, node->name, node->address, (node->dns_server + 1), output);
	else
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — %s ]\nProtocol: DNS\nStatus: Unealthy\nResponse:\n%s",
			time, node->name, node->address, (node->dns_server + 1), output);
	dns_simplified_output(node, output, time, stdout_backup);
}

void	parse_output(t_protocol *node, char *output, int log_fd)
{
	int stdout_backup;

	stdout_backup = dup(STDOUT);
	dup2(log_fd, STDOUT);
	if (node->protocol == DNS)
		dns_output_parsing(node, output, stdout_backup);
}
