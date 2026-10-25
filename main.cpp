#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

// Состояние игры (базовые переменные)
int hp = 100;
int resources = 50; // Деньги / Мана / Патроны / Крышки
int score = 0; // Очки выживания (цель — рекорд)
int turn = 1;

void printHUD() {
    std::cout << "\n================ [ХОД: " << turn << " | СЧЕТ: " << score << "] ================\n";
    std::cout << "❤️ Здоровье: " << hp << "/100 |  Ресурсы: " << resources << "\n";
    std::cout << "--------------------------------------------------------\n";
}

// -------------------------------------------------------------
// [МЕСТО ДЛЯ ФУНКЦИЙ РАЗРАБОТЧИКОВ ИЗ PULL REQUEST'ОВ]
// -------------------------------------------------------------

// [РАЗРАБОТЧИК 1: МОДУЛЬ "КОЛЕСО ФОРТУНЫ" (ISSUE #1)]
void spinWheel() {
    std::cout << "\n[Колесо] Нажми Enter, чтобы вращать! ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    int value = 0;
    for (int i = 0; i < 13; i++) {
        value = rand() % 201 - 100;
        std::cout << "\rКолесо: *вращается*... " << std::setw(4) << value;
        std::this_thread::sleep_for(std::chrono::milliseconds(50 * i));
    }

    const char *quote = "\n";
    if (value >= -100 && value <= -81)      quote = "Фаталити!\n";
    else if (value >= -80 && value <= -41)  quote = "Благодарю за пожертвование!)\n";
    else if (value >= -40 && value <= -1)   quote = "Хотел как лучше, а получилось как всегда...\n";
    else if (value == 0)                    quote = "Признайся, ты просто тратишь моё время?";
    else if (value >= 1 && value <= 40)     quote = "Нууу, это лучше, чем ничего.\n";
    else if (value >= 41 && value <= 80)    quote = "Как ты это сделал?!\n";
    else if (value >= 81 && value <= 100)   quote = "Ты жульничаешь, но я не могу это доказать.\n";

    std::cout << "\n[Колесо]: " << quote << std::endl;

    score += value;
}

int main() {
    srand(time(NULL));
    int choice = 0;
    
    std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: БИТВА ЗА РЕКОРД <<<\n";
    
    while (hp > 0) {
        printHUD();
        std::cout << "1. Вращать колесо\n";
        std::cout << "2. База / Лагерь (Лечение и обмен ресурсов)\n";
        std::cout << "3. Особое событие / Рулетка удачи\n";
        std::cout << "0. Сдаться и зафиксировать счет\n";
        std::cout << "Выберите действие > ";
        
        if (!(std::cin >> choice)) break;
        
        switch (choice) {
            case 1:
                // [РАЗРАБОТЧИК 1: ПОДКЛЮЧИТ ФУНКЦИЮ РИСКА (ISSUE #1)]
		spinWheel();
                break;
            
            case 2:
                // [РАЗРАБОТЧИК 2: ПОДКЛЮЧИТ МОДУЛЬ ОТХИЛА (ISSUE #2)]
                std::cout << "\n[!] Модуль лагеря еще в разработке (Issue #2).\n";
                break;
            
            case 3:
                // [РАЗРАБОТЧИК 3: ПОДКЛЮЧИТ РУЛЕТКУ/БОССА (ISSUE #3)]
                std::cout << "\n[!] Модуль событий еще в разработке (Issue #3).\n";
                break;
            
            case 0:
                hp = 0;
                break;
            
            default:
                std::cout << "\nНеизвестная команда!\n";
                break;
        }
        
        // Каждый успешный ход дает очки выживания
        if (hp > 0) {
            turn++;
            score += 10;
        }
    }
    
    std::cout << "\n💀 ИГРА ОКОНЧЕНА. Ваш итоговый рекорд: " << score << " очков!\n";
    return 0;
}
