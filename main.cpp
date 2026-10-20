#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

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

// [РАЗРАБОТЧИК 2: МОДУЛЬ "БРОСОК КОСТИ" (ISSUE #2)]
void rollDice() {
    const int roll = rand() % 20 + 1;
    int delta = 0;

    std::cout << "\n[Кости] Ты бросаешь D20... выпало: " << roll << "\n";

    if (roll == 20) {
        delta = 100;
        std::cout << "[Кости] КРИТИЧЕСКИЙ УСПЕХ! Джекпот!\n";
    } else if (roll >= 15) {
        delta = 50;
        std::cout << "[Кости] Отличный бросок.\n";
    } else if (roll >= 10) {
        delta = 20;
        std::cout << "[Кости] Неплохо.\n";
    } else if (roll >= 5) {
        delta = -10;
        std::cout << "[Кости] Неудача.\n";
    } else if (roll > 1) {
        delta = -30;
        std::cout << "[Кости] Провал!\n";
    } else {  // roll == 1
        delta = -50;
        std::cout << "[Кости] КРИТИЧЕСКИЙ ПРОВАЛ! Проклятие!\n";
    }

    score += delta;
    if (score < 0) score = 0;

    std::cout << "[Кости] Счет: " << (delta >= 0 ? "+" : "") << delta
              << "  (итого: " << score << ")\n";
}

int main() {
    srand(time(NULL));
    int choice = 0;
    
    std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: БИТВА ЗА РЕКОРД <<<\n";
    
    while (hp > 0) {
        printHUD();
        std::cout << "1. Рискованная операция (Высокая награда / Высокий риск)\n";
        std::cout << "2. База / Лагерь (Лечение и обмен ресурсов)\n";
        std::cout << "3. Особое событие / Рулетка удачи\n";
        std::cout << "0. Сдаться и зафиксировать счет\n";
        std::cout << "Выберите действие > ";
        
        if (!(std::cin >> choice)) break;
        
        switch (choice) {
            case 1:
                // [РАЗРАБОТЧИК 1: ПОДКЛЮЧИТ ФУНКЦИЮ РИСКА (ISSUE #1)]
                std::cout << "\n[!] Модуль риска еще в разработке (Issue #1).\n";
                break;
            
            case 2:
                rollDice();
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
