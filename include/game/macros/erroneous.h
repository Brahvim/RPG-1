#pragma once

#include "game/macros/ops.h"

#define ERRONEOUS1()		printf("`%s()` called with erroneous parameters.\n", __func__)
#define ERRONEOUS2(p_err)	printf("`%s()` called with erroneous parameters. %s\n", __func__, p_err)
