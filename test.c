#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hermes.h"
// gcc -o test test.c hermes.a -framework Foundation -framework AppKit -framework Security
int main()
{
	if (startWithConfigFile("config.json", "dynamic-config.json") != 0) {
		return -1;
	}
	if (setDnsConfig() != 0) {
		return -1;
	}
	sleep(3);
	if (routeAddWithDefaultGateway() != 0) {
		return -1;
	}
	char *processTrafficBytes, *routerTrafficBytes;
	while (1) {
		//processTraffic
		processTrafficBytes = processTraffic();
		printf("processTraffic: %s\n", processTrafficBytes);
		free(processTrafficBytes);
		//routerTraffic
		routerTrafficBytes = routerTraffic();
		printf("routerTraffic: %s\n", routerTrafficBytes);
		free(routerTrafficBytes);
		sleep(1);
	}
	if (stop() != 0) {
		return -1;
	}
	if (restoreDnsConfig() != 0) {
		return -1;
	}
	return 0;
}