#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
#else
	#error Engine does not support non-windwos platforms
#endif

#define BIT(x) (1 << x)
