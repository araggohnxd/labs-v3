#include "monitoring.h"

void	http_simplified_output(t_protocol *node, char *time, char *status_str, t_bool healthy, int stdout_backup)
{
	size_t i;

	if (status_str)
	{
		for (i = 0; status_str[i] != '\n'; i++);
		status_str[i] = '\0';
	}
	dup2(stdout_backup, STDOUT);
	close(stdout_backup);
	if (healthy)
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s — Method %s ]%s\n%sProtocol:%s HTTP\n%sStatus:%s %sHealthy%s\n%sResponse: %s%s\n\n",
			CYAN, time, node->name, node->address, node->method, RESET,
			PURPLE, RESET, PURPLE, RESET, GREEN, RESET, PURPLE, RESET, status_str);
	else
		dprintf(STDOUT, "%s[ %s ][ \"%s\": %s — Method %s ]%s\n%sProtocol:%s HTTP\n%sStatus:%s %sUnhealthy, expected %ld%s\n%sResponse: %s%s\n\n",
			CYAN, time, node->name, node->address, node->method, RESET,
			PURPLE, RESET, PURPLE, RESET, RED, node->code, RESET, PURPLE, RESET, status_str);
}

void	http_output_parsing(t_protocol *node, char *output, char *time, int stdout_backup)
{
	t_bool healthy = FALSE;
	char *status_str = strstr(output, "HTTP");
	int status_code;

	if (status_str)
	{
		status_str += 9;
		status_code = atoi(status_str);
		healthy = status_code == node->code;
	}
	else
		output = "(null)\n\n";
	time[strlen(time) - 1] = '\0';
	if (healthy)
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — Method %s ]\nProtocol: HTTP\nStatus: Healthy\nResponse:\n%s",
			time, node->name, node->address, node->method, output);
	else
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — Method %s ]\nProtocol: HTTP\nStatus: Unealthy, expected %ld\nResponse:\n%s",
			time, node->name, node->address, node->method, node->code, output);
	http_simplified_output(node, time, status_str, healthy, stdout_backup);
}
