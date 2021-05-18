// gcc -o test test.c hermes.a -framework Foundation -framework AppKit -framework Security
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hermes.h"
int main()
{
	if (hermes_start_with_config_file("config.json", "dynamic-config.json") != 0) {
		return -1;
	}
	if (hermes_set_dns_config() != 0) {
		return -1;
	}
	sleep(3);
	if (hermes_route_add_with_default_gateway() != 0) {
		return -1;
	}
	char *process_traffic_bytes, *router_traffic_bytes;
	while (1) {
		//process_traffic
		process_traffic_bytes = hermes_process_traffic();
		printf("hermes_process_traffic: %s\n", process_traffic_bytes);
		free(process_traffic_bytes);
		//router_traffic
		router_traffic_bytes = hermes_router_traffic();
		printf("hermes_router_traffic: %s\n", router_traffic_bytes);
		free(router_traffic_bytes);
		sleep(1);
	}
	if (hermes_stop() != 0) {
		return -1;
	}
	if (hermes_restore_dns_config() != 0) {
		return -1;
	}
	return 0;
}