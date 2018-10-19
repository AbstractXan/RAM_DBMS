#include <stdio.h>
#include "handle.h"

using namespace std;

int main(int argc, char **argv) {
	handle_t *myhandle = get_handle();
	myhandle->exec("dummy query");
}
