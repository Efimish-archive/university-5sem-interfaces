// В рамках работы необходимо создать консольную программу,
// обрабатывающую аргументы командной строки.
// Программа считывает данные с файла.
// Каждая строка файла содержит описание объекта, например:
//
// Point(3.4, 5.5)
// Line(Point(1.2, 3.4), Point(5, 6))
// Circle(Point(5, 6), 7)
//
// Линия задается двумя точками (началом и концом),
// окружность - центром (точкой) и радиусом.
//
// Необходимо считать эту информацию в любой
// стандартный контейнер (список, вектор, ...)
// и выполнить с ним указанную в аргументе командной строки операцию.
//
// Программа должна поддерживать аргумент -f или --file,
// следом за которым идет путь к обрабатываемому файлу,
// а также -o или --oper, задающим операцию над списком фигур.
// Типы операций следующие:
// print (печатает полученный в результате список на экране),
// count (выводит количество объектов).
//
// Некоторые строки в файле могут содержать некорректное описание объектов.

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <memory>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

struct Shape
{
  virtual ~Shape() {}
  virtual string toString() const = 0;
};

struct Point : Shape
{
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  string toString() const override
  {
    return "Point(" + to_string(x) + ", " + to_string(y) + ")";
  }
};

struct Line : Shape
{
  Point p1, p2;
  Line(Point p1, Point p2) : p1(p1), p2(p2) {}
  string toString() const override
  {
    return "Line(" + p1.toString() + ", " + p2.toString() + ")";
  }
};

struct Circle : Shape
{
  Point center;
  double radius;
  Circle(Point center, double radius) : center(center), radius(radius) {}
  string toString() const override
  {
    return "Circle(" + center.toString() + ", " + to_string(radius) + ")";
  }
};

unique_ptr<Shape> parseShape(const string &line)
{
  static const regex point_regex(
      R"(^Point\(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*\)$)");
  static const regex line_regex(
      R"(^Line\(\s*Point\(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*\)\s*,\s*Point\(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*\)\s*\)$)");
  static const regex circle_regex(
      R"(^Circle\(\s*Point\(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*\)\s*,\s*([-+]?\d*\.?\d+)\s*\)$)");

  smatch match;

  if (regex_match(line, match, point_regex))
  {
    double x = stod(match[1]);
    double y = stod(match[2]);
    return make_unique<Point>(x, y);
  }
  else if (regex_match(line, match, line_regex))
  {
    double x1 = stod(match[1]);
    double y1 = stod(match[2]);
    double x2 = stod(match[3]);
    double y2 = stod(match[4]);
    return make_unique<Line>(Point(x1, y1), Point(x2, y2));
  }
  else if (regex_match(line, match, circle_regex))
  {
    double cx = stod(match[1]);
    double cy = stod(match[2]);
    double r = stod(match[3]);
    return make_unique<Circle>(Point(cx, cy), r);
  }

  return nullptr;
}

int main(int argc, char *argv[])
{
  string filename, print;
  bool count = false;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "show this help message")
    ("file,f", po::value<string>(&filename)->required(), "input file path")
    ("print,p", po::value<string>(&print), "type of object to print (Point | Line | Circle)")
    ("count,c", po::bool_switch(&count), "count objects");

  po::variables_map vm;

  try
  {
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help"))
    {
      cout << desc << endl;
      return 0;
    }

    po::notify(vm);
  }
  catch (const po::error &ex)
  {
    cerr << ex.what() << endl
         << endl
         << desc << endl;
    return 1;
  }

  if (print != "Point" && print != "Line" && print != "Circle")
  {
    cerr << "Invalid print object type: '" << print << "'. Allowed values: Point, Line, Circle" << endl;
    return 1;
  }

  ifstream file(filename);
  if (!file)
  {
    cerr << "Cannot open file: " << filename << endl;
    return 1;
  }

  vector<unique_ptr<Shape>> shapes;
  string line;

  while (getline(file, line))
  {
    if (unique_ptr<Shape> shape = parseShape(line))
    {
      shapes.push_back(std::move(shape));
    }
    else
    {
      cerr << "Invalid line skipped: " << line << endl;
    }
  }

  if (print == "Point")
  {
    for (const unique_ptr<Shape> &s : shapes)
    {
      if (auto circle = dynamic_cast<Circle *>(s.get()))
      {
        cout << s->toString() << endl;
      }
    }
  }
  else if (print == "Line")
  {
    for (const unique_ptr<Shape> &s : shapes)
    {
      if (auto line = dynamic_cast<Line *>(s.get()))
      {
        cout << s->toString() << endl;
      }
    }
  }
  else if (print == "Circle")
  {
    for (const unique_ptr<Shape> &s : shapes)
    {
      if (auto point = dynamic_cast<Point *>(s.get()))
      {
        cout << s->toString() << endl;
      }
    }
  }

  if (count)
  {
    cout << "Count: " << shapes.size() << endl;
  }

  return 0;
}
