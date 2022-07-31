#include "monitoring.h"

void	free_protocol_node(void *node)
{
	t_protocol *aux;

	aux = (t_protocol *) node;
	ft_memfree((void *) &aux->name);
	ft_memfree((void *) &aux->address);
	ft_memfree((void *) &aux->method);
	ft_memfree((void *) &aux->dns_server);
	ft_memfree((void *) &aux);
}

t_protocol	*create_protocol_node(t_protocol_type protocol, char **split)
{
	t_protocol *node;

	node = (t_protocol *) calloc(1, sizeof(t_protocol));
	if (!node)
		return (NULL);
	node->protocol = protocol;
	node->name = strdup(split[INDEX_NAME]);
	node->address = strdup(split[INDEX_ADDRESS]);
	if (protocol == HTTP)
	{
		node->method = strdup(split[HTTP_INDEX_METHOD]);
		node->interval = atoi(split[HTTP_INDEX_INTERVAL]);
		node->code = atoi(split[HTTP_INDEX_CODE]);
	}
	if (protocol == DNS)
		node->dns_server = strdup(split[DNS_INDEX_SERVER]);
	if (protocol == PING || protocol == DNS)
		node->interval = atoi(split[INDEX_INTERVAL]);
	return (node);
}
