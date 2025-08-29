#pragma once

#include "game/macros/ops.h"

// `ERRONEOUS()` recursive macros.

#define ERRONEOUS1(...)\
printf("`%s()` called with erroneous parameters.\n", __func__)

#define ERRONEOUS2(p_value, ...)\
printf("`%s()` called with erroneous parameters. %s\n", __func__, p_err)
