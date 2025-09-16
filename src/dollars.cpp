#include <iostream>
#include <limits>

using namespace std;

int main() {
  cout << "Здравствуйте! Пожалуйста, введите, сколько у вас долларов ($)." << endl;
  double dollars;

  while (true) {
    cin >> dollars;

    if (cin.fail()) {
      cout << "Ошибка! Вы ввели не число." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    cout << "Отлично! Это значит, что в рублях у вас: " << dollars * 70 << endl;
    return 0;
  }
}
