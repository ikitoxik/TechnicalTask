#include "LineSegment.h"
#include <cmath>

//------------------------------------------------------------------------------
/**
    онструктор
   \param begPoint начальна€ точка отрезка
   \param endPoint конечна€ точка отрезка
*/
//--- 
LineSegment::LineSegment(const Point& begPoint, const Point& endPoint)
  : m_begPoint(begPoint)
  , m_endPoint(endPoint)
{
}

//------------------------------------------------------------------------------
/**
   ћетод получени€ начальной точки отрезка
*/
//--- 
const Point& LineSegment::GetBeg() const
{
  return m_begPoint;
}

//------------------------------------------------------------------------------
/**
   ћетод получени€ конечной точки отрезка
*/
//--- 
const Point& LineSegment::GetEnd() const
{
  return m_endPoint;
}

//------------------------------------------------------------------------------
 /**
    ¬ычисление рассто€ни€ от отрезка до точки
    \param point переданна€ точка
    \return рассто€ние от отрезка до переданной точки
 */
 //---  
double LineSegment::DistanceToPoint(const Point& point) const
{
  Point pnt = this->ClosestPoint(point);
  return std::hypot(std::hypot(point.GetX() - pnt.GetX(), point.GetY() - pnt.GetY()), point.GetZ() - pnt.GetZ());
}

//------------------------------------------------------------------------------
 /**
    ¬ычисление проекции точки на отрезок
    \param point переданна€ точка
    \return точка на отрезке
 */
 //---  
Point LineSegment::ClosestPoint(const Point& point) const
{
  // paramL - коэффициент параметрического уравнени€ пр€мой при координате x
  auto paramL = m_endPoint.GetX() - m_begPoint.GetX();
  // paramM - коэффициент параметрического уравнени€ пр€мой при координате y
  auto paramM = m_endPoint.GetY() - m_begPoint.GetY();
  // paramK - коэффициент параметрического уравнени€ пр€мой при координате z
  auto paramK = m_endPoint.GetZ() - m_begPoint.GetZ();
  // (x1,y1,z1) - begPoint, (x2,y2,z2) - endPoint, (x0,y0,z0) - point, (x,y,z) принадлежит заданному отрезку
  // »з параметрического уравнени€ пр€мой: x = x1 + t(x2 - x1), y = y1 + t(y2 - y1), z = z1 + t(z2 - z1)
  // ¬екторы ортогональны, если их скал€рное произведение равно 0
  // {x0 - x, y0 - y, z0 - z} * {x2 - x1, y2 - y1, z2 - z1} = 0
  // {x0 - x1 - t(x2 - x1), y0 - y1 - t(y2 - y1), z0 - z1 - t(z2 - z1)} * {x2 - x1, y2 - y1, z2 - z1} = 0
  // t = [(x0-x1)(x2-x1)+(y0-y1)(y2-y1)+(z0-z1)(z2-z1)] / [(x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1)]
  double t = -1;
  double length_squared = paramL * paramL + paramM * paramM + paramK * paramK;
  // ѕроверка, что не будет делени€ на 0
  if (length_squared != 0.0)
    t = ((point.GetX() - m_begPoint.GetX()) * paramL + (point.GetY() - m_begPoint.GetY()) 
      * paramM + (point.GetZ() - m_begPoint.GetZ()) * paramK ) / length_squared;
  double x;
  double y;
  double z;
  // нормаль на пр€мую падает вне отрезка, point левее begPoint
  if (t < 0)
  {
    x = m_begPoint.GetX();
    y = m_begPoint.GetY();
    z = m_begPoint.GetZ();
  }
  // нормаль на пр€мую падает вне отрезка, point правее endPoint
  else if (t > 1)
  {
    x = m_endPoint.GetX();
    y = m_endPoint.GetY();
    z = m_endPoint.GetZ();
  }
  else
  {
    x = m_begPoint.GetX() + t * paramL;
    y = m_begPoint.GetY() + t * paramM;
    z = m_begPoint.GetZ() + t * paramK;
  }
  return Point{ x, y, z };
}