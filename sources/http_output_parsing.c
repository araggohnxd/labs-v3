#include "monitoring.h"

static void	http_terminal_output(t_protocol *node, char *time, char *status_str, t_bool healthy, int stdout_backup)
{
	if (status_str)
		nullify_newline(status_str);
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
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — Method %s ]\nProtocol: HTTP\nStatus: Healthy\nResponse:\n%s@\n",
			time, node->name, node->address, node->method, output);
	else
		dprintf(STDOUT, "[ %s ][ \"%s\": %s — Method %s ]\nProtocol: HTTP\nStatus: Unealthy, expected %ld\nResponse:\n%s@\n",
			time, node->name, node->address, node->method, node->code, output);
	http_terminal_output(node, time, status_str, healthy, stdout_backup);
}
