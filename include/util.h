#pragma once


#define CLAMP(val, min, max) (((val) > (max))? (max): (((val) < (min))? (min): (val)))
