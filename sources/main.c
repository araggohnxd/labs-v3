#include "monitoring.h"

int g_loop_condition = 1;

void sigint(int ignore)
{
	(void) ignore;
	g_loop_condition = 0;
}

int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		dprintf(STDERR, "monitoring: too many arguments\nusage: ./monitoring [--simplify]\n");
		exit (EXIT_FAILURE);
	}
	if (argc == 2)
	{
		if (strcmp(argv[1], "--simplify") == 0)
			return (simplify_log_file());
		else
		{
			dprintf(STDERR, "monitoring: %s: invalid option\nusage: ./monitoring [--simplify]\n", argv[1]);
			exit (EXIT_FAILURE);
		}
	}

	int config_fd;
	t_list *parsed_configs;

	config_fd = open("monitoring.db", O_RDONLY);
	if (config_fd < 0)
	{
		dprintf(STDERR, "monitoring: monitoring.db: %s\n", strerror(errno));
		exit (EXIT_FAILURE);
	}
	parsed_configs = parse_config_file(config_fd);
	close(config_fd);
	if (parsed_configs)
		exec_protocol(parsed_configs);
	ft_lstclear(&parsed_configs, free_protocol_node);
	return (EXIT_SUCCESS);
}
