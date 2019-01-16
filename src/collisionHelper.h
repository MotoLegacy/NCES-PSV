#ifndef _COLLISON_HELPER_
#define _COLLISON_HELPER_

struct rect {
  double x;
  double y;
  double w;
  double h;
  double hv;
  double vv;
};

bool checkCollision(rect a, rect b);

#endif