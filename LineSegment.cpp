#include "LineSegment.h"
#include <cmath>

//------------------------------------------------------------------------------
/**
   �����������
   \param begPoint ��������� ����� �������
   \param endPoint �������� ����� �������
*/
//--- 
LineSegment::LineSegment(const Point& begPoint, const Point& endPoint)
  : m_begPoint(begPoint)
  , m_endPoint(endPoint)
{
}

//------------------------------------------------------------------------------
/**
   ����� ��������� ��������� ����� �������
*/
//--- 
const Point& LineSegment::GetBeg() const
{
  return m_begPoint;
}

//------------------------------------------------------------------------------
/**
   ����� ��������� �������� ����� �������
*/
//--- 
const Point& LineSegment::GetEnd() const
{
  return m_endPoint;
}

//------------------------------------------------------------------------------
 /**
    ���������� ���������� �� ������� �� �����
    \param point ���������� �����
    \return ���������� �� ������� �� ���������� �����
 */
 //---  
double LineSegment::DistanceToPoint(const Point& point) const
{
  Point pnt = this->ClosestPoint(point);
  return std::hypot(std::hypot(point.GetX() - pnt.GetX(), point.GetY() - pnt.GetY()), point.GetZ() - pnt.GetZ());
}

//------------------------------------------------------------------------------
 /**
    ���������� �������� ����� �� �������
    \param point ���������� �����
    \return ����� �� �������
 */
 //---  
Point LineSegment::ClosestPoint(const Point& point) const
{
  // paramL - ����������� ���������������� ��������� ������ ��� ���������� x
  auto paramL = m_endPoint.GetX() - m_begPoint.GetX();
  // paramM - ����������� ���������������� ��������� ������ ��� ���������� y
  auto paramM = m_endPoint.GetY() - m_begPoint.GetY();
  // paramK - ����������� ���������������� ��������� ������ ��� ���������� z
  auto paramK = m_endPoint.GetZ() - m_begPoint.GetZ();
  // (x1,y1,z1) - begPoint, (x2,y2,z2) - endPoint, (x0,y0,z0) - point, (x,y,z) ����������� ��������� �������
  // �� ���������������� ��������� ������: x = x1 + t(x2 - x1), y = y1 + t(y2 - y1), z = z1 + t(z2 - z1)
  // ������� ������������, ���� �� ��������� ������������ ����� 0
  // {x0 - x, y0 - y, z0 - z} * {x2 - x1, y2 - y1, z2 - z1} = 0
  // {x0 - x1 - t(x2 - x1), y0 - y1 - t(y2 - y1), z0 - z1 - t(z2 - z1)} * {x2 - x1, y2 - y1, z2 - z1} = 0
  // t = [(x0-x1)(x2-x1)+(y0-y1)(y2-y1)+(z0-z1)(z2-z1)] / [(x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1)]
  double t = -1;
  double length_squared = paramL * paramL + paramM * paramM + paramK * paramK;
  // ��������, ��� �� ����� ������� �� 0
  if (length_squared != 0.0)
    t = ((point.GetX() - m_begPoint.GetX()) * paramL + (point.GetY() - m_begPoint.GetY()) 
      * paramM + (point.GetZ() - m_begPoint.GetZ()) * paramK ) / length_squared;
  double x;
  double y;
  double z;
  // ������� �� ������ ������ ��� �������, point ����� begPoint
  if (t < 0)
  {
    x = m_begPoint.GetX();
    y = m_begPoint.GetY();
    z = m_begPoint.GetZ();
  }
  // ������� �� ������ ������ ��� �������, point ������ endPoint
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