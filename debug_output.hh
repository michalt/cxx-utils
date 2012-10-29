#ifndef DEBUG_OUTPUT_HH
#define DEBUG_OUTPUT_HH

#include <iostream>

#ifdef DEBUG_OUTPUT
#define DEBUG_LOCATION "(" << __FILE__ << ":" << __LINE__ << "):"
#define DMSG(msg) std::cerr << DEBUG_LOCATION << " " << msg << std::endl;
#define DOUT(x) std::cerr << DEBUG_LOCATION << " " << x;
#else
#define DMSG(msg) (void)0
#define DOUT(x) (void)0
#endif


#endif /* DEBUG_OUTPUT_HH */
