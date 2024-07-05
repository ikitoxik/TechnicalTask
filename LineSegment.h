#pragma once
#include "Point.h"

////////////////////////////////////////////////////////////////////////////////
//
/// Объявление класса отрезка
/**
*/
////////////////////////////////////////////////////////////////////////////////
class LineSegment
{
private:
	Point m_begPoint;  /// < начальная точка отрезка
	Point m_endPoint;  /// < конечная точка отрезка

public:
	/// Конструктор
	LineSegment(const Point& begPoint = { 0.0, 0.0}, const Point& endPoint = { 1.0, 1.0});
	/// Вычисление расстояния от точки до отрезка
	double DistanceToPoint(const Point&) const;
	/// Метод получения первой точки
	const Point& GetBeg() const;
	/// Метод получения второй точки
	const Point& GetEnd() const;
	/// Вычисление проекции точки на отрезок
	Point ClosestPoint(const Point& point) const;
};