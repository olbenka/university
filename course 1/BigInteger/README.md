[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7284972&assignment_repo_type=AssignmentRepo)
# BigInteger
Реализуйте класс для представления длинных целых чисел (знаковых).

## Требования к реализации
* Название класса: `BigInteger`
* Заголовочный файл: `biginteger.h`
* Файл реализации: `biginteger.cpp`

Для класса BigInteger реализовать:
* Конструктор по умолчанию (инициализирует число нулём).
* Конструкторы от числовых типов.
* Явный конструктор от `std::string`.
* Конструктор копирования.
* Конструктор перемещения.
* Операторы:
  * присваивания копированием,
  * присваивания перемещением,
  * сравнения.
* Операции:
  * арифметические операции: сложение, вычитание, умножение, деление, унарный минус, унарный плюс, инкременты и декременты.
  * битовые операции: и, или, исключающее или, не, битовые сдвиги.
* Внешнюю функцию `std::string to_string(BigInteger const&)`.

Требования:
* Разряды числа должны представляться как минимум 32-битными числами, все биты в их представлении должны использоваться.
* Пользоваться сторонними библиотеками при выполнении задания запрещено (исключение `std::string` при реализации to_string, `std::numeric_limits`).

## Дополнительная литература
* Кнут Д.Э. Искусство программирования. Том 2. Получисленные алгоритмы. Глава 4. Секция 4.3.
* ["Modern Computer Arithmetic"](https://members.loria.fr/PZimmermann/mca/mca-0.5.pdf)
* ["Multiple-Length Division Revisited: A Tour of the Minefield"](https://surface.syr.edu/cgi/viewcontent.cgi?article=1162&context=eecs_techreports) 

