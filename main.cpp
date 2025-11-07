// complex_calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <string>

int main() {
    double result;
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return 1;
    }

    char pendingOp = '\0';  // Отложенная операция (+ или -)
    double pendingNum = 0.0; // Число для отложенной операции

    std::string token;
    bool needReadToken = true;  // Флаг: нужно ли читать новый токен

    while (true) {
        // Читаем токен только если это необходимо
        if (needReadToken) {
            if (!(std::cin >> token)) {
                std::cerr << "Error: Unexpected end of input" << std::endl;
                return 1;
            }
        }
        else {
            needReadToken = true;  // Сброс флага для следующего прохода
        }

        if (token == "=") {
            // Применяем отложенную операцию
            if (pendingOp == '+') {
                result += pendingNum;
            }
            else if (pendingOp == '-') {
                result -= pendingNum;
            }
            std::cout << result << std::endl;
            return 0;
        }

        if (token == "+" || token == "-") {
            // Применяем предыдущую отложенную операцию
            if (pendingOp == '+') {
                result += pendingNum;
            }
            else if (pendingOp == '-') {
                result -= pendingNum;
            }

            pendingOp = token[0];

            // Считываем число после +/−
            if (!(std::cin >> pendingNum)) {
                std::cerr << "Error: Numeric operand expected after " << token << std::endl;
                return 1;
            }

            // Обрабатываем последовательные * и / для pendingNum
            while (std::cin >> token) {
                if (token != "*" && token != "/") {
                    // Это не * или / — сохраняем токен и выходим
                    needReadToken = false;  // Не читать новый токен в следующем цикле
                    break;
                }

                double operand;
                if (!(std::cin >> operand)) {
                    std::cerr << "Error: Numeric operand expected after " << token << std::endl;
                    return 1;
                }
                if (token == "/" && operand == 0) {
                    std::cerr << "Error: Division by zero" << std::endl;
                    return 1;
                }
                pendingNum = (token == "*") ? pendingNum * operand : pendingNum / operand;
            }
            continue;  // Пропускаем остаток главного цикла
        }
        else if (token == "*" || token == "/") {
            double operand;
            if (!(std::cin >> operand)) {
                std::cerr << "Error: Numeric operand expected after " << token << std::endl;
                return 1;
            }
            //if (token == "/" && operand == 0) {
                //std::cerr << "Error: Division by zero" << std::endl;
                //return 1;
            //}
            if (token == "*") {
                result *= operand;
            }
            else {
                result /= operand;
            }
        }
        else {
            std::cerr << "Error: Unknown token " << token << std::endl;
            return 1;
        }
    }

    std::cerr << "Error: Expected '=' at the end" << std::endl;
    return 1;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
