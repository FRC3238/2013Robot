#ifndef MAPPER_H
#define MAPPER_H

class mapper {
public:
  mapper(double x1,double x2,double y1,double y2);

  double Map(double inNum);

  // This stuff is for using the mapper as a liner calculator.
  void setValues(double x1,double x2,double y1,double y2);
  double getSlope(void);
  double getMinX(void);
  double getMaxX(void);
  double getIntercept(void);

private:
  double minX;
  double maxX;
  double slope;
  double intercept;
};

#endif

