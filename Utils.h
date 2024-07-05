#pragma once

//------------------------------------------------------------------------------
/**
    Проверка имения файла на наличие расширения
*/
//--- 
bool has_suffix(const std::string& str, const std::string& suffix)
{
  return str.size() >= suffix.size() &&
    str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}


//------------------------------------------------------------------------------
/**
    Преобразование текстовой строки в точку
*/
//--- 
Point StrToPnt(const std::string& str)
{
  std::string str_x, str_y, str_z;
  bool second = false, third = false;
  for (int i = 0; i < str.size(); i++)
  {
    if (str[i] == ' ')
    {
      if (!second)
      {
        second = true;
        continue;
      }
      else
      {
        second = false;
        third = true;
        continue;
      }
    }

    if (!second && !third)
    {
      str_x += str[i];
    }
    else if (second && !third)
    {
      str_y += str[i];
    }
    else
    {
      str_z += str[i];
    }
  }
  double x, y, z;
  x = std::stod(str_x);
  y = std::stod(str_y);
  z = std::stod(str_z);

  return Point{ x, y, z };
}

//------------------------------------------------------------------------------
/**
    Удаление из строки незначащих нулей
*/
//--- 
std::string& RemoveZero(std::string& str)
{
  if (str[str.size() - 1] == '0')
    for (size_t i = str.size() - 1; str[i] == '0' || str[i] == '.'; i--)
    {
      if (str[i] == '.')
      {
        str.erase(i, 1);
        return str;
      }
      str.erase(i, 1);
    }
  return str;
}

//------------------------------------------------------------------------------
/**
    Преобразование точки в строку
*/
//--- 
std::string PointToString(const Point& pnt)
{
  std::string x_str, y_str, z_str;

  x_str = std::to_string(pnt.GetX());
  y_str = std::to_string(pnt.GetY());
  z_str = std::to_string(pnt.GetZ());

  return RemoveZero(x_str) + " " + RemoveZero(y_str) + " " + RemoveZero(z_str);
}