#pragma once
#include "Point.h"

////////////////////////////////////////////////////////////////////////////////
//
/// ���������� ������ �������
/**
*/
////////////////////////////////////////////////////////////////////////////////
class LineSegment
{
private:
	Point m_begPoint;  /// < ��������� ����� �������
	Point m_endPoint;  /// < �������� ����� �������

public:
	/// �����������
	LineSegment(const Point& begPoint = { 0.0, 0.0}, const Point& endPoint = { 1.0, 1.0});
	/// ���������� ���������� �� ����� �� �������
	double DistanceToPoint(const Point&) const;
	/// ����� ��������� ������ �����
	const Point& GetBeg() const;
	/// ����� ��������� ������ �����
	const Point& GetEnd() const;
	/// ���������� �������� ����� �� �������
	Point ClosestPoint(const Point& point) const;
};