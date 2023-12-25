#pragma once

#if LINKY_PROFILE
#endif

#if LINKY_PROFILE
#else
	#define LINKY_PROFZONE(name, colour)
	#define LINKY_THREAD(name)
	#define LINKY_FRAME
	#define LINKY_FRAME_BEGIN
	#define LINKY_FRAME_END
#endif