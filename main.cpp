#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

// struct that represents a point
struct Point {
  double x, y;

  Point()
  { set(0,0); }

  Point(const double xPos, const double yPos)
  { set(xPos, yPos); }

  void set(const double xPos, const double yPos)
  { x = xPos;
    y = yPos; }
};

// calculates the distance between two points
static const double distance(const Point p1, const Point p2)
{ return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)); }

// calculates the angle between two vectors
const double vectorAngle(const Point p1, const Point p2,
                          const Point p3, const Point p4)
{ const double dx1 = p2.x - p1.x;
  const double dy1 = p2.y - p1.y;
  const double dx2 = p4.x - p3.x;
  const double dy2 = p4.y - p3.y;
  const double m1 = sqrt(dx1 * dx1 + dy1 * dy1);
  const double m2 = sqrt(dx2 * dx2 + dy2 * dy2);
  const double temp = (dx1 * dx2 + dy1 * dy2) / (m1 * m2);
  // cout << "temp = " << temp << endl;
  const double angle = acos(temp) * (180 / acos(-1));
  return (dy1 < dy2) ? angle + 180 : angle; }

// checks to see if two lines collide
// the inter parameter returns the point of intersection
const bool collision(const Point p1, const Point p2,
                     const Point p3, const Point p4, Point & inter,
                     const double tolerance = 0.001)
{ const double tmp = (p1.x - p2.x)*(p3.y - p4.y) - (p1.y - p2.y)*(p3.x - p4.x);
  if (tmp == 0)
    return false;
  const double uA = ((p4.x-p3.x)*(p1.y-p3.y) - (p4.y-p3.y)*(p1.x-p3.x))
                  / ((p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y));

  const double uB = ((p2.x-p1.x)*(p1.y-p3.y) - (p2.y-p1.y)*(p1.x-p3.x))
                  / ((p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y));

  // intercept
  inter.set(p1.x + (uA * (p2.x - p1.x)), p1.y + (uA * (p2.y - p1.y)));
  return (uA >= 0 && uA <= 1 && uB >= 0 + tolerance && uB <= 1-tolerance); }

// calculates the angle between a line and the origin
double originAngle(Point p1, Point p2)
{ double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  double angl = atan(dy / dx) * (180 / acos(-1));
  if (dx < 0)
    angl += 180;
  else if
    (dy < 0) angl += 360;
  // cout << "angle = " << angl << endl;
  return angl; }

// calculates the angle between two lines
double lineAngle(Point p1, Point p2, Point p3, Point p4)
{ double angl1 = originAngle(p1, p2);
  double angl2 = originAngle(p3, p4);
  double angl  = angl1 - angl2;
  return (angl < 0)? 360 + angl : angl; }

void print(Point p1, Point p2, Point p3, Point p4)
{ cout << "\n--------------------------------------------------\n";
  cout << "line1 originAngle = " << originAngle(p1, p2) << endl;
  cout << "line2 originAngle = " << originAngle(p3, p4) << endl;
  cout << "lineAngle         = " << lineAngle(p1, p2, p3, p4) << endl;
  cout << "vectorAngle       = " << vectorAngle(p1, p2, p3, p4) << endl;
  Point inter;
  cout << "collision         = " << collision(p1, p2, p3, p4, inter) << endl;
  cout << "intersection      = (" << inter.x << "," << inter.y << ")\n"; }

// function that reads in a file and calculates the angle between each
// of the two lines in each row
void testFileAngles(string fileName)
{ ifstream fin(fileName.c_str());
  if(fin.fail())
  { cout<<"error opening "<<fileName<<endl;
    exit(-1); }
  int x1, y1, x2, y2, x3, y3, x4, y4;
  while(true)
  { fin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    if(fin.fail()) break;
    print(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4)); }
  fin.close(); }

int main(int argc, char * argv[])
{ if(argc != 2)
  { cout<<"Usage: "<<argv[0]<<" <file-name>\n";
    return 0; }
  testFileAngles(argv[1]);
  return 0; }
