//
//  main.cpp
//  test
//
//  Created by nastya on 22.05.2022.
//

#include <iostream>
#include <stdlib.h>

#include <cmath>
#include "matrix1.h"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;
int main()
{
Matrix a;
fromTxtFile(a,"data.txt");
    Pca nip(a.rows(),a.cols());
 //nip.leverage(a,1);
//nip.deviation(a,1);
//nip.expvar(a,12);
nip.Nipals(a,12);
    cout << "Выберите операцию: \n \n 1) Сложение матриц \n 2) Умножение матриц \n 3) Умножение матрицы на число \n 4) Вычитание матриц \n 5) Произведение Адамара \n 6) Создать единичную матрицу \n 7) Диагональная матрица \n 8) Верхняя треугольная матрица \n 9) Нижняя треугольная матрица \n 10) Симметричная матрица \n 11) След матрицы \n 12) Скалярно перемножить векторы \n 13) Норма вектора(евклидова или максимальная) \n 14) Норма матрицы \n 15) Определитель матрицы \n 16) Транспонировать матрицу \n 17) Обратная матрица \n 18) Угол между векторами \n 19) Ранг матрицы \n 20) Матрица из файла"  << endl;
        int n;
    cin >> n;
 
    switch (n)
    {
    case 1: // Для сложения матриц
        { try{ //Для поиска исключений
        int r1, c1, r2, c2;
        cout << "Введите количество строк матрицы 1: ";
        cin >> r1;
        cout << "Введите количество столбцов матрицы 1: ";
        cin >> c1;
        cout << "Введите элементы 1 матрицы: ";
        Matrix mat(r1, c1);
        mat.EnterMatrix();
        cout <<"Первая введенная матрица:\n"<< mat;
        cout << "Введите количество строк матрицы 2: ";
        cin >> r2;
        cout << "Введите количество столбцов матрицы 2:";
        cin >> c2;
        cout << "Введите элементы 2 матрицы: ";
        Matrix mat2(r2, c2);
        mat2.EnterMatrix();
        cout <<"Вторая введенная матрица:\n"<< mat2;
            cout << mat + mat2;}
            catch (const char* exception) // обработка исключений
            {
                std::cerr << "Ошибка: " << exception << std::endl;
            }        break;
    }
    case 2: // Умножение матриц
        { try{
        int r1, c1, r2, c2;
        cout << "Введите количество строк для 1 матрицы: ";
        cin >> r1;
        cout << "Введите количество столбцов для 1 матрицы: ";
        cin >> c1;
        cout << "Введите элементы 1 матрицы: ";
        Matrix mat(r1, c1);
        mat.EnterMatrix();
        cout <<"Введенная первая матрица:\n"<< mat;
        cout << "Введите количество строк для 2 матрицы: \n";
        cin>>r2;
        cout << "Введите количество столбцов для 2 матрицы: ";
        cin >> c2;
        cout << "Введите элементы 2 матрицы: ";
        Matrix mat2(r2, c2);
        mat2.EnterMatrix();
        cout <<"Введенная вторая матрица:\n"<< mat2;
            cout << mat * mat2;}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
        break;
    }
    case 3: // Умножение матрицы на вектор
    {
        int r1, c1;
        cout << "Введите количество строк для 1 матрицы: ";
        cin >> r1;
        cout << "Введите количество столбцов для 1 матрицы: ";
        cin >> c1;
        cout << "Введите элементы 1 матрицы: ";
        Matrix mat(r1, c1);
        mat.EnterMatrix();
        cout <<"Введенная матрица:\n"<< mat;
        double scalar;
        cout<<"Введите число:"<<endl;
        cin>>scalar;
        cout << mat * scalar;
        break;
    }
        case 4: //Выычитание матриц
        { try{
            int r1, c1, r2, c2;
            cout << "Введите количество строк матрицы 1: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы 1: ";
            cin >> c1;
            cout << "Введите элементы 1 матрицы: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первая введенная матрица:\n" <<mat;
            cout << "Введите количество строк матрицы 2: ";
            cin >> r2;
            cout << "Введите количество столбцов матрицы 2:";
            cin >> c2;
            cout << "Введите элементы 2 матрицы: ";
            Matrix mat2(r2, c2);
            mat2.EnterMatrix();
            cout <<"Вторая введенная матрица:\n" <<mat2;
            cout << mat - mat2;}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }            break;
        }
        case 5:
        { try{ //Операция Адамара
            int r1, c1, r2, c2;
            cout << "Введите количество строк матрицы 1: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы 2: ";
            cin >> c1;
            cout << "Введите элементы 1 матрицы: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первая введенная матрица:\n" <<mat;
            cout << "Введите количество строк матрицы 2: ";
            cin >> r2;
            cout << "Введите количество столбцов матрицы 2:";
            cin >> c2;
            cout << "Введите элементы 2 матрицы: ";
            Matrix mat2(r2, c2);
            mat2.EnterMatrix();
            cout <<"Вторая введенная матрица:\n" <<mat2;
            cout << hadamara(mat, mat2);}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            break;
        }
            
        case 6:
        { try{ //Создание единичной матрицы
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
            singleMatrix mat(r1, c1);
            mat.EnterSingleMatrix();
            cout<<mat;}
            catch (const char* exception) // обработка исключений типа const char*
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            break;
        }
        case 7:
        { try{ //Создание диагональной матрицы
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
            diagonalMatrix mat(r1, c1);
            mat.EnterDiagonalMatrix();
            cout<<mat;}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            break;
            
    }
        case 8:
        { try{//Создание верхнетреугольной матрицы
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
            upTriangleMatrix mat(r1, c1);
            mat.EnterUpTriangleMatrix();
            cout<<mat;}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            break;
            
            
    }
        case 9: //Создание нижнетреугольной матрицы
        { try{
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
            downTriangleMatrix mat(r1, c1);
            mat.EnterDownTriangleMatrix();
            cout<<mat;}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            break;
        }

        case 10:
        {try{ //Создание симметричной матрицы
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
            simMatrix mat(r1, c1);
            mat.EnterSimMatrix();
            cout<<mat;}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            break;
    }
        case 11:
        { try{ //След матрицы
            int r1, c1;
            cout << "Введите количество строк матрицы : ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы : ";
            cin >> c1;
            cout << "Введите элементы матрицы: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первая введенная матрица:\n" <<mat;
            cout << Trace(mat);}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            cout<<endl;
            break;
        }
        case 12:
        { try{ //Скалярное умножение векторов
            int r1, c1,r2,c2;
            cout << "Введите количество строк матрицы 1: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы 1: ";
            cin >> c1;
            cout << "Введите элементы 1 вектора: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первый введенный вектор:\n" <<mat;
            cout << "Введите количество строк матрицы 2: ";
            cin >> r2;
            cout << "Введите количество столбцов матрицы 2:";
            cin >> c2;
            cout << "Введите элементы 2 вектора: ";
            Matrix mat2(r2, c2);
            mat2.EnterMatrix();
            cout <<"Вторая введенный вектор:\n" <<mat2;
            cout << scalarVectors(mat,mat2);}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            cout<<endl;
            break;
        }
        case 13:
        { try{ //Норма вектора
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
            cout << "Введите элементы вектора: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Введенный вектор :\n" <<mat;
            cout << normOfvec(mat);}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            cout<<endl;
            break;
        }
        case 14://норма матрицы
        {
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
            cout << "Введите элементы матрицы: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Введенная матрица:\n" <<mat;
            cout << matrixNorm(mat);
            cout<<endl;
            break;
        }
        case 15:
        { try{
            int r1, c1;
            cout << "Введите количество строк матрицы 1: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы 1: ";
            cin >> c1;
            cout << "Введите элементы 1 матрицы: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первая введенная матрица:\n" <<mat;
            cout << determinant(mat);
        }
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }            cout<<endl;
            break;
        }
        case 16:
        {
            int r1, c1;
            cout << "Введите количество строк матрицы 1: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы 1: ";
            cin >> c1;
            cout << "Введите элементы 1 матрицы: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первая введенная матрица:\n" <<mat;
            cout << transpose(mat);
            cout<<endl;
            break;
        }
        case 17:
        {try{
            int r1, c1;
            cout << "Введите количество строк матрицы 1: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы 1: ";
            cin >> c1;
            cout << "Введите элементы 1 матрицы: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первая введенная матрица:\n" <<mat;
            inverse(mat);}
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }            cout<<endl;
            break;
        }
        case 18:{try{
            int r1, c1,r2,c2;
            cout << "Введите количество строк матрицы 1: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы 1: ";
            cin >> c1;
            cout << "Введите элементы 1 вектора: ";
            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout <<"Первый введенный вектор:\n" <<mat;
            cout << "Введите количество строк матрицы 2: ";
            cin >> r2;
            cout << "Введите количество столбцов матрицы 2:";
            cin >> c2;
            cout << "Введите элементы 2 вектора: ";
            Matrix mat2(r2, c2);
            mat2.EnterMatrix();
            cout <<"Вторая введенный вектор:\n" <<mat2;
            cout<<angleBtwVecs(mat,mat2);
        }
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
             cout<<"°"<<endl;
              break;
        }
        case 19://ранг матрицы
        {
            int r1, c1;
            cout << "Введите количество строк матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов матрицы: ";
            cin >> c1;
          Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout<<rank1(mat);
           
            cout<<endl;
            break;
        }
        case 20:{try{
            Matrix mat;
            fromTxtFile(mat,"scores.txt");
            cout<<endl;
            cout<<"Матрица из текстового файла 1:"<<endl;
            mat.print();
            Matrix mat1;
            fromTxtFile(mat1,"scores2.txt");
            cout<<endl;
            cout<<"Матрица из текстового файла 1:"<<endl;
            mat1.print();
            int n;
            cout<<"Введите 1 - для записи в текстовый файл, 2 - для записи в бинарный"<<endl;
            cin>>n;
            tofile(mat,n);
            if (n!=1){
            cout<<"Матрица из бинарного файла:"<<endl;
            Matrix c(mat.rows(),mat.cols());
            fromBinFile(c,"m.bin");
            c.print();}
        }
            catch (const char* exception)
                {
                    std::cerr << "Ошибка: " << exception << std::endl;
                }
            break;
        }
            return 0;
}
}

