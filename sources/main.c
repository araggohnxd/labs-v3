#include "monitoring.h"

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
