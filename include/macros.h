#pragma once

// helping macros

#define DELETENULL(X) \
	if (X != NULL) { \
		delete X; \
		X = NULL; \
	}
#define THROW(X) \
	X e; \
throw(e)

#define THROWINFO(X, I) \
	X e(I); \
throw(e)

