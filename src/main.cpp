#include <stdio.h>
#include <string>
#include "handle.h"

using namespace std;

int main(int argc, char **argv) {
	handle_t *myhandle = get_handle();
	while(1)
		myhandle->exec(getInput());
	delete_handle(myhandle);
}
