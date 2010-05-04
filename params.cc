#include <math.h>

#include "params.hh"

double kMaxEmptyAngle           = 2.0 * M_PI / 180.0;
double kMaxEmptyDistance        = 0.1;
double kMinRegionLength         = 0.2;
int    kMinPointsInRegion       = 8;
int    kMinPointsInSegment      = 5;
double kConfidence              = 95.0;
double kAlphaILF(void)          { return 1000.0 - 10 * kConfidence; }
bool   kCheckResidual           = false;
double kMaxAngEBE               = 0.0;
double kMinDistBetweenEndpoints = 0.0;
double kMinOdomDistChange       = 0.0;
double kMinOdomAngChange        = 0.0;
long   kMinMillisBetweenScans   = 50;