#include <QtTest>
#include <QDebug>
#include <vector>
#include <QString>
#include "heapsorter.h"

class TestSolver : public QObject
{
    Q_OBJECT
private slots:
    void testLogic();
};

void TestSolver::testLogic()
{
    // Структура для тест-кейсов
    struct TestCase {
        QString input;
    };

    // 10 различных наборов данных
    std::vector<QString> inputs = {
        "1 2 3",
        "3 2 1",
        "5 1 4 2 3",
        "10 20 30 40 50",
        "50 40 30 20 10",
        "0 0 0 0",
        "-1 -5 -2 -3",
        "100 5 2 1",
        "1 100 2 50",
        "4 7 2 9 1"
    };

    for(const auto& nums : inputs) {
        // Запрашиваем 1-й шаг
        // В Qt 6 используем arg() немного иначе, но старый стиль тоже часто работает.
        // Для надежности упростим сборку строки:
        QString request = "sort&1&" + nums;

        QString result = HeapSorter::processRequest(request);

        qDebug() << "Input:" << nums << "Step 1 Result:" << result;

        QVERIFY(!result.isEmpty());
        QVERIFY(!result.contains("Error"));

        // ИСПРАВЛЕНИЕ ДЛЯ QT 6: Qt::SkipEmptyParts вместо QString::SkipEmptyParts
        int inputCount = nums.split(" ", Qt::SkipEmptyParts).size();
        int outputCount = result.split(" ", Qt::SkipEmptyParts).size();

        QCOMPARE(inputCount, outputCount);
    }
}

QTEST_MAIN(TestSolver)
#include "tst_solver.moc"
