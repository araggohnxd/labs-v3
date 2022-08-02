#include "monitoring.h"

void	ping_simplified_output(t_protocol *node, char *time, char *packets, t_bool healthy, int stdout_backup)
{
	dup2(stdout_backup, STDOUT);
	close(stdout_backup);
	if (healthy)
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s ]%s\n%sProtocol:%s PING\n%sStatus:%s %sHealthy%s\n\n",
			CYAN, time, node->name, node->address,
			RESET, PURPLE, RESET, PURPLE, RESET, GREEN, RESET);
	else
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s ]%s\n%sProtocol:%s PING\n%sStatus:%s %sUnealthy%s\n%sResponse:%s %s\n\n",
			CYAN, time, node->name, node->address,
			RESET, PURPLE, RESET, PURPLE, RESET, RED, RESET, PURPLE, RESET, packets);
}

void	ping_output_parsing(t_protocol *node, char *output, char *time, int stdout_backup)
{
	t_bool healthy = FALSE;
	char *newline = strstr(output, "---");
	char *packets = strstr(output, "packets");
	char *received = NULL;
	size_t i;

	if (packets)
	{
		packets -= 2;
		received = strstr(packets, "received") - 2;
		if (atoi(packets) == atoi(received))
			healthy = TRUE;
		for (i = 0; packets[i] != '\n'; i++);
		packets[i] = '\0';
		*(newline - 1) = ' ';
	}
	else
		output = NULL;
	if (healthy)
		dprintf(STDOUT, "[ %s ][ \"%s\": %s ]\nProtocol: PING\nStatus: Healthy\nResponse:\n%s\n\n",
			time, node->name, node->address, output);
	else
		dprintf(STDOUT, "[ %s ][ \"%s\": %s ]\nProtocol: PING\nStatus: Unealthy\nResponse:\n%s\n\n",
			time, node->name, node->address, output);
	ping_simplified_output(node, time, packets, healthy, stdout_backup);
}
