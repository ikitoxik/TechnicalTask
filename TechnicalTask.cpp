#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include "Point.h"
#include "LineSegment.h"
#include "Utils.h"


int main()
{
  std::string filename;

  /// Ввод имени файла
  std::cout << "Enter the name of input file:\n";
  std::cin >> filename;

  /// Проверка на расширение в имени файла
  if (!has_suffix(filename, ".txt"))
  {
    filename += ".txt";
  }

  std::string line; /// Строка, считываемая из файла
  std::ifstream input(filename);
  std::vector<Point> lineSegment; /// Вектор для хранения узлов линии
  Point lastPoint; /// Точка для сравнения одинаковых решений

  /// Попытка открыть файл для чтения и считывание узлов линии
  if (input.is_open())
  {
    while (std::getline(input, line))
    {
      if (line == "Nodes:" || line == " " || line == "")
        continue;
        lineSegment.push_back(StrToPnt(line));
    }
  }
  else
  {
    std::cout << "Error. Can't open file.";
    return 0;
  }

  /// Ввод точки для проекции
  double t_x = 0, t_y = 0, t_z = 0;
  std::cout << "Enter target point: ";
  std::cin >> t_x >> t_y >> t_z;
  Point targetPoint{ t_x, t_y, t_z };

  /// Вывод на экран считанных данных
  std::cout << "Nodes:" << std::endl;
  for (auto i = lineSegment.begin(); i != lineSegment.end(); i++)
  {
    std::cout << (*i).GetX() << " " << (*i).GetY() << " "<< (*i).GetZ() << std::endl;
  }
  std::cout << "Target point:" << std::endl;
  std::cout << "x: " << targetPoint.GetX() << " y: " << targetPoint.GetY() << " z: " << targetPoint.GetZ() << std::endl;

  double distance = 0;                /// Расстояние от точки до отрезка
  double min = LONG_MAX;              /// Минимальное расстояние
  int count = 1, answers_count = 0;   /// Счетчики сегментов и ответов
  std::vector<std::string> result;    /// Вектор ответов

  constexpr double eps = 0.00001;     /// Константа для учета погрешности
  /// Поиск решений
  for (auto i = lineSegment.begin(); i != lineSegment.end() - 1; i++)
  {
    LineSegment segment{ *i, *(i + 1) };
    distance = segment.DistanceToPoint(targetPoint);
    if (fabs(distance - min) < eps)
    {
      Point pnt = segment.ClosestPoint(targetPoint);

      if (!lineSegment.empty())
      {
        if (lastPoint == pnt)
          result.push_back("or");
      }

      lastPoint = pnt;
      std::string answer = "segment " + std::to_string(count) + " point " + PointToString(pnt);
      result.push_back(answer);
      min = distance;
      ++answers_count;
    }
    else if (distance < min)
    {
      Point pnt = segment.ClosestPoint(targetPoint);
      
      lastPoint = pnt;
      std::string answer = "segment " + std::to_string(count) + " point " + PointToString(pnt);
      result.clear();
      result.push_back(answer);
      min = distance;
      answers_count = 1;
    }
    ++count;
  }

  /// Вывод ответа в консоль
  std::cout << "Number of found solutions: " << answers_count << std::endl;
  for (auto i = result.begin(); i != result.end(); i++)
  {
    std::cout << *i << std::endl;
  }

  input.close();
}
