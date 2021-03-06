/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Copyright (c) 2013, Cyril Hrubis <chrubis@suse.cz>
 *
 * Created by:  salwan.searty REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 *
 * Testing invalid signals with sigismember().
 * After invalid signal set sigismember() should return -1 and set
 * errno to indicate the error.
 * Test steps:
 * 1)  Initialize a full signal set.
 * 2)  Check for invalid signal from the full signal set.
 * 3)  Verify that -1 is returned and errno is set to indicate the error.
 */
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdint.h>
#include "posixtest.h"

static const int sigs[] = {-1, -10000, INT32_MIN, INT32_MIN + 1};

int main(void)
{
	sigset_t signalset;
	int i, ret, err = 0;

	if (sigfillset(&signalset) == -1) {
		perror("sigemptyset failed -- test aborted");
		return PTS_UNRESOLVED;
	}

	for (i = 0; i < sizeof(sigs) / sizeof(int); i++) {
		ret = sigismember(&signalset, sigs[i]);

		if (ret != -1 || errno != EINVAL) {
			err++;
			printf("Failed sigaddset(..., %i) ret=%i errno=%i\n",
			       sigs[i], ret, errno);
		}
	}

	if (err) {
		printf("Test FAILED\n");
		return PTS_FAIL;
	} else {
		printf("Test PASSED\n");
		return PTS_PASS;
	}
}
