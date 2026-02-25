#ifndef HEAPSORTER_H
#define HEAPSORTER_H

#include <vector>
#include <algorithm>
#include <QString>
#include <QStringList>
#include <QtGlobal> // для QT_VERSION

class HeapSorter {
public:
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l] > arr[largest])
            largest = l;

        if (r < n && arr[r] > arr[largest])
            largest = r;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    static std::vector<std::vector<int>> getSortingSteps(std::vector<int> arr) {
        std::vector<std::vector<int>> steps;
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        steps.push_back(arr);

        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
            steps.push_back(arr);
        }

        return steps;
    }

    static QString processRequest(const QString& request) {
        // Формат: sort&<step>&1 2 3 ...
        QStringList parts = request.split("&");
        if (parts.size() < 3 || parts[0] != "sort") {
            return "Error: Invalid format";
        }

        bool stepOk;
        int stepIndex = parts[1].toInt(&stepOk);
        if (!stepOk) return "Error: Invalid step number";

        // --- НАЧАЛО ИСПРАВЛЕНИЯ ---
        // Проверяем версию Qt: если меньше 6.0.0 (это Docker), используем старый стиль.
        // Если 6.0.0 и выше (ваш Windows), используем новый стиль.
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QStringList numbersStr = parts[2].split(" ", QString::SkipEmptyParts);
#else
        QStringList numbersStr = parts[2].split(" ", Qt::SkipEmptyParts);
#endif
        // --- КОНЕЦ ИСПРАВЛЕНИЯ ---

        std::vector<int> arr;
        for (const QString& num : numbersStr) {
            arr.push_back(num.toInt());
        }

        std::vector<std::vector<int>> history = getSortingSteps(arr);

        // Если запрошенный шаг больше количества шагов, возвращаем последний (отсортированный)
        // Если шаг <= 0, возвращаем первый доступный
        if (history.empty()) return "";

        // Корректировка индекса шага для удобства (пользователь вводит 1, мы берем 0 индекс массива истории)
        int actualIndex = stepIndex - 1;

        if (actualIndex < 0) actualIndex = 0;
        if (actualIndex >= (int)history.size()) actualIndex = (int)history.size() - 1;

        std::vector<int> resultArr = history[actualIndex];

        QStringList resList;
        for (int n : resultArr) {
            resList << QString::number(n);
        }

        return resList.join(" ");
    }
};

#endif // HEAPSORTER_H
