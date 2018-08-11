#ifndef MYMATH_H
#define MYMATH_H

#define PI 3.14159265359f

#define RADTODEG ( rad ) { return rad * 180.0f / PI; }
#define DEGTORAD ( deg ) { return deg * PI / 180.0f; }

#define MYMIN( a, b ) (a < b ? a : b)
#define MYMAX( a, b ) (a < b ? b : a)

#endif // !MYMATH_H


