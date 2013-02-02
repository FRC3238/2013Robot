#ifndef MULTIMAPPER_H
#define MULTIMAPPER_H


class mapItem {

public :
  mapItem(double inX, double inY);
  ~mapItem(void);

  void setValues(void);
  bool linkIn(mapItem* itemPtr);
  double Map(double inVal);
  double doMap(double inVal);
  void outputItem(void);

  double x;
  double y;
  double slope;
  double intercept;
  mapItem* lessItem;
  mapItem* greaterItem;
};


class MultiMapper {

public:
  MultiMapper();
  ~MultiMapper();

  void addPoint(double x, double y);
  void clearMap(void);
  double Map(double inVal);
  void outputList(void);

private :

  mapItem* itemList;
};


#endif


