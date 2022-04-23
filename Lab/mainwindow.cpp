#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() // Шифр
{
        QString opentext;
        QString cph;
        int key;
        opentext = ui->textedit->text();
        key = ui->keyline->text().toInt();
        if (opentext.isEmpty() || ui->keyline->text().isEmpty())
        {
            QMessageBox::warning(this,"Ошибка", "Поле открытого текста пусто или ключ");
        }
        else
        {
            int count = 0;
            int key_temp = key;
            while (key_temp)
            {
                key_temp /= 10;
                count++;
            }
            int lenght = opentext.length();
                int line;
            div_t div_1 = div(lenght,count);
                if (div_1.rem > 0)
                    line = div_1.quot + 1;
                else
                    line = div_1.quot;
            QString** matrix = new QString * [count]; // Создание матрицы для шифра
            for (int i = 0; i < count; i++)
                matrix[i] = new QString[count];
            int* arr = new int [count]; //  Ключ в массив
            int count_matrix = count - 1; // счетчик для заполнения матрицы
            while (key)
            {
                arr[count_matrix] = key % 10;
                key /= 10;
                count_matrix--;

            }
            count_matrix = 0; // счетчик для заполнения матрицы
            for (int i = 0; i < line; i++) // заполнение матрицы
            {
                for (int j = 0; j < count; j++)
                {
                    if (count_matrix >= lenght) // Если вдруг отсутствует символ
                    {
                        matrix[i][j] = "-"; // заменяем на -
                    }
                    else
                    {
                        matrix[i][j] = opentext[count_matrix];
                    }
                    count_matrix++;
                }
            }
            count_matrix = 0;
            while (count_matrix < count)
            {
                for (int i = 0; i <= 9; i++) // прогоняем каждую цифру
                {
                    for (int j = 0; j < count; j++)
                    {
                        if (i == arr[j])
                        {
                            for (int a = 0; a < count; a++)
                            {
                                cph = cph + matrix[a][j];
                            }
                            count_matrix++;
                        }
                    }
                }
            }
            ui -> textedit_2 -> setText(cph);
    }
        }



void MainWindow::on_pushButton_2_clicked() // Дешифр
{
        QString closetext;
        QString cph;
        int key;
        closetext = ui->textedit_2->text();
        key = ui->keyline->text().toInt();
        if (closetext.isEmpty() || ui->keyline->text().isEmpty())
        {
            QMessageBox::warning(this,"Ошибка", "Поле закрытого текста пусто или ключ");
        }
        else
        {
            int count = 0;
            int key_temp = key;
            while (key_temp)
            {
                key_temp /= 10;
                count++;
            }
            int line;
            int length = closetext.length();
            div_t div_1 = div(length,count); // Проверка длины
                if (div_1.rem > 0)
                    line = div_1.quot + 1;
                else
                    line = div_1.quot;
            QString** matrix = new QString * [count]; // Создание матрицы для шифра
            for (int i = 0; i < count; i++)
                matrix[i] = new QString[count];
            int* arr = new int [count]; //  Ключ в массив
            int* arr_2 = new int[count];



            int count_matrix = 0; // счетчик для заполнения матрицы
            while (key)
            {
                arr[count_matrix] = key % 10;
                key /= 10;
                count_matrix++;

            }
            int temp;
            for (int i = 0; i < (count / 2); i++) {
                    temp = arr[i];
                    arr[i] = arr[count - 1 - i];
                    arr[count - 1 - i] = temp;
                }

            for (int i = 0; i < count; i++)
            {
                arr_2[i] = arr[i];
            }

            for (int i = 0; i < line - 1; i++) // Сортировка доп.массива методом пузырька
            {
                for (int j = 0; j < count - i - 1; j++)
                {
                    if (arr_2[j] > arr_2[j + 1])
                    {
                        swap(arr_2[j], arr_2[j + 1]);
                    }
                }
            }

            for (int i = 0; i < count; i++) // заполнение матрицы
                {
                    for (int j = 0; j < count; j++)
                    {
                        if (arr[i] == arr_2[j])
                            for (int a = 0; a < line; a++)
                                matrix[a][i] = closetext[line * j + a];
                    }
                }

            for (int i = 0; i < line; i++) // заполнение QString
            {
                for (int j = 0; j < count; j++)
                {
                    cph += matrix[i][j];
                }
            }
            ui -> textedit -> setText(cph);
        }

}

