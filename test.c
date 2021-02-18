/* test.c
 * vim:set noet sts=0 sw=0 ts=4 tw=80:
 * test driver file to run & verify the implementation */

#include "crc.h"
#include <stdio.h>
#include <assert.h>

#define TEST_BEGIN       puts("\n== BEGIN TESTS ==")
#define TEST_END         puts("\n== all tests passed ==\n")
#define TEST(test, diag) (diag? assert((test) && diag): assert(test), putchar('.'))

extern struct crc_spec spec;

int main()
{
	byte *buf;
	byte check[] = "123456789";
	byte lorem[] = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
	TEST_BEGIN;

	// Testing lookup
	TEST(lookup(check, 9) == spec.check, "crc implementation is incorrect");

	// Testing arbitrary strings, use online crc calculator *with params* to verify
	// must remove \0 from strings unless they are expected to be part of the data
	TEST(lookup(lorem, sizeof(lorem) - 1) == 0xa3, NULL);

	// Testing helpers
	TEST(buf = chksum(check, 9, NULL), "chksum doesn't allocate buf");
	TEST(buf[9] == spec.check, "chksum doesn't append the correct crc");
	TEST(verify(buf, 10), "verify doesn't verify correctly");
	free(buf), buf = NULL;

	TEST_END;
	return 0;
}
