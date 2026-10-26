#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

// Состояние игры (базовые переменные)
int hp = 100;
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

// [РАЗРАБОТЧИК 1: МОДУЛЬ "КОЛЕСО ФОРТУНЫ" (ISSUE #1)]
void spinWheel() {
    std::cout << "\n[Колесо] Нажми Enter, чтобы вращать! ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    int value = 0;
    for (int i = 0; i < 13; i++) {
        value = rand() % 201 - 100;
        std::cout << "\rКолесо: *вращается*... " << std::setw(4) << value << std::flush;
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
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
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
        std::cout << "1. Вращать колесо\n";
        std::cout << "2. Бросить кость\n";
        std::cout << "3. Подбросить монетку\n";
        std::cout << "0. Сдаться и зафиксировать счет\n";
        std::cout << "Выберите действие > ";
        
        if (!(std::cin >> choice)) break;
        
        switch (choice) {
            case 1:
                // [РАЗРАБОТЧИК 1: ПОДКЛЮЧИТ ФУНКЦИЮ РИСКА (ISSUE #1)]
                spinWheel();
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
