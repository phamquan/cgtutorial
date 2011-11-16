#pragma once

#include "HomoPoint.h"

namespace QTMath {
	int round(double x) {
		return int(x+0.5);
	}
	int round(float x) {
		return int(x+0.5);
	}
}