#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Состояние игры (базовые переменные)
int hp = 100;
int resources = 50; // Нужна ли эта переменная? ведь мы ее не используем
int score = 0; // Деньги + счёт
int turn = 1;

void printHUD() {
    std::cout << "\n================ [ХОД: " << turn << " | СЧЕТ: " << score << "] ================\n";
    std::cout << "❤️ Здоровье: " << hp << "/100 |  Ресурсы: " << score << "\n";
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

// [РАЗРАБОТЧИК 3: МОДУЛЬ "БРОСКА МОНЕТЫ" (ISSUE #3)]
void CoinFlip() {
    std::cout << "\n=== РУЛЕТКА ФОРТУНЫ: ПОДБРОС МОНЕТКИ ===\n";
    std::cout << "[Монетка] Угадай сторону: Орел(1) или Решка (2). Введите выбор: ";
    int choice;
    int fast;
    if (not(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cout << "[Монетка] Неверный выбор! Ход пропущен.\n";
        return;
    }
    int coin = (rand() % 2) + 1; // 1 — Орел, 2 — Решка
    std::cout << "[Монетка] Выпал: " << (coin == 1 ? "Орел" : "Решка") << "!\n";

    if (choice == coin) {
        score += 10;
        fast = 10;
        std::cout << "[Монетка] Победа!\n";
    } else {
        score -= 10;
        fast = -10;
        if (score < 0) score = 0;
        std::cout << "[Монетка] Проигрыш!\n";
    }
    std::cout << "[Монетка] Счет: " << (fast >= 0 ? "+" : "") << fast
            << "  (итого: " << score << ")\n";
}



int main() {
    srand(time(NULL));
    int choice = 0;
    
    std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: БИТВА ЗА РЕКОРД <<<\n";
    
    while (hp > 0) {
        printHUD();
        std::cout << "1. Рискованная операция (Высокая награда / Высокий риск)\n";
        std::cout << "2. Бросить кость\n";
        std::cout << "3. Подбросить монетку\n";
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
                CoinFlip();
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
