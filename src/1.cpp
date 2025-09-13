#include <iostream>
#include <string>
#include <regex>

using namespace std;

struct Date {
  int dd;
  int mm;
  int yyyy;
};

struct Patient {
  string passport;    // ss ss-nnnnnn
  string name;        // any string
  Date birth_date;    // yyyy-mm-dd
  string phone;       // +X(XXX) XXX-XX-XX or X(XXX) XXX-XXXX
  double temperature; // XX.XX
};

string trim(string s) {
  s.erase(0, s.find_first_not_of(" \n\r\t"));
  s.erase(s.find_last_not_of(" \n\r\t") + 1);
  return s;
}

string input(string text = "") {
  string s;
  cout << text;
  getline(cin, s);
  return trim(s);
}

const regex passport_regex(R"(^\d{2} \d{2}-\d{6}$)");

string input_passport() {
  while (true) {
    string passport = input("Введите серию и номер паспорта (ss ss-nnnnnn): ");
    if (!regex_match(passport, passport_regex)) {
      cout << "Ошибка. Введите заново в формате 'ss ss-nnnnnn'." << endl;
      continue;
    }
    return passport;
  }
}

string input_name() {
  while (true) {
    string name = input("Введите имя: ");
    if (name.length() < 2) {
      cout << "Ошибка. Имя не может быть короче двух символов." << endl;
      continue;
    }
    return name;
  }
}

const regex date_regex(R"(^\d{4}-\d{2}-\d{2}$)");

Date input_date() {
  while (true) {
    string date_string = input("Введите дату рождения (yyyy-mm-dd): ");
    if (!regex_match(date_string, date_regex)) {
      cout << "Ошибка. Введите заново в формате 'yyyy-mm-dd'." << endl;
      continue;
    }

    Date date;
    date.yyyy = stoi(date_string.substr(0, 4));
    date.mm = stoi(date_string.substr(5, 2));
    date.dd = stoi(date_string.substr(8, 2));

    if (!(
      1900 <= date.yyyy && date.yyyy <= 2025
      && 1 <= date.mm   && date.mm   <= 12
      && 1 <= date.dd   && date.dd   <= 31
    )) {
      cout << "Ошибка. Дата должна быть в диапазоне от 1900-01-01 до 2025-12-31." << endl;
      continue;
    }

    return date;
  }
}

const regex phone_regex(R"(^\+?\d\(\d{3}\) \d{3}-\d{2}-?\d{2}$)");

string input_phone() {
  while (true) {
    string phone = input("Введите телефон ([+]x(xxx) xxx-xx[-]xx): ");
    if (!regex_match(phone, phone_regex)) {
      cout << "Ошибка. Введите заново в формате '[+]x(xxx) xxx-xx[-]xx'." << endl;
      continue;
    }
    return phone;
  }
}

const regex temperature_regex(R"(^\d{2}\.\d{2}$)");

double input_temperature() {
  while (true) {
    string temperature_string = input("Введите температуру (xx.xx): ");
    if (!regex_match(temperature_string, temperature_regex)) {
      cout << "Ошибка. Введите заново в формате 'xx.xx'." << endl;
      continue;
    }

    double temperature = stod(temperature_string);
    if (!(35 <= temperature && temperature <= 42)) {
      cout << "Ошибка. Температура должна быть 35 до 42. Иначе вы бы умерли." << endl;
      continue;
    }
    return temperature;
  }
}

int main() {
  cout << "Здравствуйте, пациент! Пожалуйста, заполните данные." << endl;
  string passport = input_passport();
  string name = input_name();
  Date date = input_date();
  string phone = input_phone();
  double temperature = input_temperature();

  cout << "Отлично! Вот ваши данные:" << endl;
  cout << "Паспорт: " << passport << endl;
  cout << "Имя: " << name << endl;
  cout << "Дата рождения: " << date.yyyy << "-" << date.mm << "-" << date.dd << endl;
  cout << "Телефон: " << phone << endl;
  cout << "Температура: " << temperature << endl;
  return 0;
}
