#include "monitoring.h"

static void	http_simplify(char *output)
{
	char *header = strdup(strchr(output, '['));
	char *health = strdup(strstr(output, "Status") + 8);
	char *response = strstr(output, "HTTP/");

	nullify_newline(header);
	nullify_newline(health);
	if (response)
	{
		response = strdup(response + 9);
		nullify_newline(response);
	}
	dprintf(STDOUT, "%s%s%s\n", CYAN, header, RESET);
	dprintf(STDOUT, "%sProtocol:%s HTTP\n", PURPLE, RESET);
	if (strncmp(health, "Healthy", 7) == 0)
		dprintf(STDOUT, "%sStatus:%s %s%s%s\n", PURPLE, RESET, GREEN, health, RESET);
	else
		dprintf(STDOUT, "%sStatus:%s %s%s%s\n", PURPLE, RESET, RED, health, RESET);
	dprintf(STDOUT, "%sResponse:%s %s\n\n", PURPLE, RESET, response);
	free(header);
	free(health);
	free(response);
}

static void	ping_simplify(char *output)
{
	char *header = strdup(strchr(output, '['));
	char *health = strdup(strstr(output, "Status") + 8);
	char *response = strstr(output, "packets");

	nullify_newline(header);
	nullify_newline(health);
	if (response)
	{
		response = strdup(response - 2);
		nullify_newline(response);
	}
	dprintf(STDOUT, "%s%s%s\n", CYAN, header, RESET);
	dprintf(STDOUT, "%sProtocol:%s PING\n", PURPLE, RESET);
	if (strncmp(health, "Healthy", 7) == 0)
		dprintf(STDOUT, "%sStatus:%s %s%s%s\n", PURPLE, RESET, GREEN, health, RESET);
	else
	{
		dprintf(STDOUT, "%sStatus:%s %s%s%s\n", PURPLE, RESET, RED, health, RESET);
		dprintf(STDOUT, "%sResponse:%s %s\n", PURPLE, RESET, response);
	}
	dprintf(STDOUT, "\n");
	free(header);
	free(health);
	free(response);
}

static void	dns_simplify(char *output)
{
	char *header = strdup(strchr(output, '['));
	char *health = strdup(strstr(output, "Status") + 8);
	char *response = strdup(strstr(output, "Response") + 10);
	char *simplified = strdup("");
	size_t index = 0;
	char **split;

	nullify_newline(header);
	nullify_newline(health);
	dprintf(STDOUT, "%s%s%s\n", CYAN, header, RESET);
	dprintf(STDOUT, "%sProtocol:%s DNS\n", PURPLE, RESET);
	if (strncmp(health, "Healthy", 7) == 0)
	{
		split = ft_split(response, '\n');
		while (strrchr(split[index], '\t'))
			simplified = ft_strjoin_free(simplified, strdup(strrchr(split[index++], '\t')));
		dprintf(STDOUT, "%sStatus:%s %s%s%s\n", PURPLE, RESET, GREEN, health, RESET);
		dprintf(STDOUT, "%sResponse:%s %s\n", PURPLE, RESET, simplified);
		ft_free_matrix((void *) &split);
	}
	else
		dprintf(STDOUT, "%sStatus:%s %s%s%s\n", PURPLE, RESET, RED, health, RESET);
	dprintf(STDOUT, "\n");
	free(header);
	free(health);
	free(response);
	free(simplified);
}

static void	parse_simplified_output(char *output)
{
	char *protocol = strdup(strstr(output, "Protocol") + 10);

	nullify_newline(protocol);
	if (strcmp(protocol, "HTTP") == 0)
		http_simplify(output);
	else if (strcmp(protocol, "PING") == 0)
		ping_simplify(output);
	else if (strcmp(protocol, "DNS") == 0)
		dns_simplify(output);
	free(protocol);
}

int	simplify_log_file(void)
{
	int log_fd;
	char *line;
	char *output = strdup("");

	log_fd = open("monitoring.log", O_RDONLY);
	if (log_fd < 0)
	{
		dprintf(STDERR, "monitoring: monitoring.log: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	while (TRUE)
	{
		line = ft_gnl(log_fd);
		if (!line)
			break ;
		output = ft_strjoin_free_null(&output, &line);
		if (strchr(output, '@'))
		{
			if (*output == '[')
				parse_simplified_output(output);
			ft_memfree((void *) &output);
			output = strdup("");
		}
	}
	ft_memfree((void *) &output);
	close(log_fd);
	return (EXIT_SUCCESS);
}
