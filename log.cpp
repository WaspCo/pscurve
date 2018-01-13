#include <iostream>
#include <iomanip>

#include "log.h"

//log functionnality
int threshold = 3;
mystreambuf nostreambuf;
std::ostream nocout(&nostreambuf);
