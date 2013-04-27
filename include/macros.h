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

#define THROWLOCATIONINFO(X, I) \
{ \
	ostringstream oss; \
	oss << I << ": [" << __FILE__ << "][" << __LINE__ << "][" << __func__ << "]"; \
	X e(oss.str().c_str()); \
	throw(e); \
}
