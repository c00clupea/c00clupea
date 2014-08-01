#include "util.h"
#include <limits.h>
#include <stdio.h>

int main( int argc, const char* argv[] )
{
	int t = 0;

	t = c00_get_hash_str("Hallo Welt",10);

	fprintf(STDERR,"%d",t);


}
