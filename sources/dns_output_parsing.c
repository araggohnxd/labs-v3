#include "monitoring.h"

void	dns_simplified_output(t_protocol *node, char *output, char *time, int stdout_backup)
{
	size_t index = 0;
	size_t address_len = strlen(node->address);
	char *simplified = strdup("");
	char **split = ft_split(output, '\n');

	dup2(stdout_backup, STDOUT);
	close(stdout_backup);
	while (split[index] && strncmp(split[index], node->address, address_len) == 0)
		simplified = ft_strjoin_free(simplified, strdup(strrchr(split[index++], '\t')));
	if (*simplified)
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s — %s ]%s\n%sProtocol:%s DNS\n%sStatus:%s %sHealthy%s\n%sResponse:%s%s\n\n",
			CYAN, time, node->name, node->address, (node->dns_server + 1), RESET,
			PURPLE, RESET, PURPLE, RESET, GREEN, RESET, PURPLE, RESET, simplified);
	else
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s — %s ]%s\n%sProtocol:%s DNS\n%sStatus:%s %sUnhealthy%s\n\n",
			CYAN, time, node->name, node->address, (node->dns_server + 1), RESET,
			PURPLE, RESET, PURPLE, RESET, RED, RESET);
	ft_free_matrix((void *) &split);
	free(simplified);
}

void	dns_output_parsing(t_protocol *node, char *output, char *time, int stdout_backup)
{
	char *healthy = strstr(output, node->address);

	if (healthy)
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — %s ]\nProtocol: DNS\nStatus: Healthy\nResponse:\n%s",
			time, node->name, node->address, (node->dns_server + 1), output);
	else
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — %s ]\nProtocol: DNS\nStatus: Unealthy\nResponse:\n%s",
			time, node->name, node->address, (node->dns_server + 1), output);
	dns_simplified_output(node, output, time, stdout_backup);
}
