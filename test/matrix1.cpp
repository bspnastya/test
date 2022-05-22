//
//  matrix1.cpp
//  mymatrix1
//
//  Created by nastya on 22.05.2022.
//

#include "matrix1.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include <typeinfo>
Matrix::Matrix(): row(0), column(0) {}
Matrix::Matrix(int row, int column) : row(row), column(column)
{
   matrix.resize(row, vector<double>(column));
}
Matrix::Matrix(const Matrix &B)
{
    this->column = B.cols();
    this->row = B.rows();
    this->matrix = B.matrix;
    
}
double Matrix::getelem(int i,int j){
    return this->matrix[i][j];
}
Matrix::Matrix(initializer_list<initializer_list<double>> listlist) {
    row= (int)(listlist.begin())->size(); /* pointer correction here */
    column = (int)listlist.size();
    matrix.resize(row, vector<double>(column));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matrix[i][j] = ((listlist.begin()+i)->begin())[j]; /* again minor correction */
        }
    }
    
}

void Matrix::print() const
{
    cout << "Matrix: " << endl;
    for (unsigned i = 0; i < row; i++) {
        for (unsigned j = 0; j < column; j++) {
            cout << "[" << matrix[i][j] << "] ";
        }
        cout << endl;
    }}
Matrix fromBinFile(Matrix &a, const char *fileName){
  ifstream fin(fileName, ios::binary);
     if (fin.fail())  throw "Возникли проблемы с открытием файла\n";
     double *y = new double[a.rows()*a.cols()+a.rows()*2];
    fin.read((char*)(y), sizeof(double)*(a.rows()*a.cols()+a.rows()*2-2)) ;
    fin.close();
        int inc=0;
    double *k= new double[a.rows()*a.cols()+a.rows()*2-2];
    for (int i = 0; i < a.rows()*a.cols()+a.rows()*2-2;i++) {
       if ((y[i]!=0)&(y[i]!=2.42092e-322)) {
           k[inc++]=y[i];
        }
    }
    int width = a.cols();
    int height = a.rows();
 for (int i = 0; i < height; i++) {
       for (int j = 0; j < width; j++)
        {
      a.matrix[i][j] = k[i * width + j];;
        }
}
  return a;
}
Matrix fromTxtFile(Matrix &a,const char *fileName){
    ifstream file_A(fileName);
  if (file_A.fail())  throw "Возникли проблемы с открытием файла\n";
    a.column = 0;
    a.row = 0;
    string line_A;
    int idx = 0;
    double element_A;
    double *vector_A = nullptr;
    if (file_A.is_open() && file_A.good())
    {
        while (getline(file_A, line_A))
        {
            a.row += 1;
            stringstream stream_A(line_A);
            a.column = 0;
            while (1)
            {
                stream_A >> element_A;
                if (!stream_A)
                    break;
                a.column += 1;
                double *tempArr = new double[idx + 1];
                copy(vector_A, vector_A + idx, tempArr);
                tempArr[idx] = element_A;
                vector_A = tempArr;
                idx += 1;
            }
        }
    }
    else
    {
        cout << " Ошибка откытия файла! \n";
    }
    
    int j;
    idx = 0;
    a.matrix.resize(a.row);
    
    for (unsigned i = 0; i < a.matrix.size(); i++) {
        a.matrix[i].resize(a.column);
    }
    for (int i = 0; i < a.row; i++)
    {
        for (j = 0; j < a.column; j++)
        {
            a.matrix[i][j] = vector_A[idx];
           
            idx++;
        }
    }
  
    delete [] vector_A; // Tying up loose ends
    return a;

}
void Matrix::EnterMatrix() //ввод матрицы
{
    double element;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
        {
            cin >> element;
            matrix[i][j] = element;
        }
}
Matrix tofile(Matrix &a,int n){
    switch(n){
    case 1:{
    ofstream file;
        file.open("matrixNew.txt");
        if (file.fail())  throw "Возникли проблемы с открытием файла,куда была бы записана матрица\n";
        for (int i = 0; i < a.rows(); i++)
        {
            for (int j = 0; j < a.cols(); j++)
            {
                file<<a.matrix[i][j]<<" ";
                
                
            }
            file<<endl;
        }
        file.close();
        break;
    }
    case 2:{ofstream out;
    out.open("m.bin",ios::binary );
    for (int i = 0; i < a.rows(); i++)
        {
            for (int j = 0; j < a.cols()+a.rows()*2; j++)
         {
            out.write(reinterpret_cast<char *>(&a.matrix[i][j]), sizeof(double)*(a.cols()+a.rows()*2)*a.rows() );
        }
        }
    out.close();
 
        break;
    }
        
    }
    return a;
}


void downTriangleMatrix::EnterDownTriangleMatrix(){
    int element;
    if (rows()!=cols()) throw "Матрица должна быть квадратной\n";
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < cols(); j++)
        {
            if (i>=j){
                cout<<"Введите элемент:\n";
                cin>>element;
                matrix[i][j]=element;
                
            }
            else { matrix[i][j]=0;}
        }
    }
}
void upTriangleMatrix::EnterUpTriangleMatrix(){
    int element;
    if (rows()!=cols()) throw "Матрица должна быть квадратной\n";
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < cols(); j++)
        {
            if (i<=j){
                cout<<"Введите элемент:\n";
                cin>>element;
                matrix[i][j]=element;
                
            }
            else { matrix[i][j]=0;}
        }
    }
}

Matrix transpose(const Matrix &a)
{
    Matrix neww(a.column,a.row);
    //cout<<"Транспонированная матрица:"<<endl;
    for (unsigned i = 0; i < a.column; i++)
    {
        for (unsigned j = 0; j < a.row; j++) {
            neww.matrix[i][j] = a.matrix[j][i];
        }
    }
    return neww;
}
double lcm(double x,double y)//это вспомогательная функция для подсчета коэффициента при использовании метода гаусса при приведении к диагональному виду
{
  double t;
    t=x/y;
    return x;
}


double determinant(Matrix& a){
    if (a.column!=a.row) throw "Матрица должна быть квадратной";
double d1,d2;
   for(int i=0;i<a.row-1;i++)
           {
               for(int j=i+1;j<a.row;j++)
               {
               double  l=lcm(a.matrix[i][i],a.matrix[j][i]);                if(l!=0&&(a.matrix[i][i]!=0&&a.matrix[j][i]!=0))
                 {
                   l=(a.matrix[i][i]*a.matrix[j][i])/l;
                   d1=l/a.matrix[i][i];
                   d2=l/a.matrix[j][i];
                   a.matrix[j][i]=0;
                   for(int k=i+1;k<a.row;k++)
                   {
                     a.matrix[j][k]=(d2*a.matrix[j][k])-(d1*a.matrix[i][k]);
                   }
                 }
               }
            }
   cout <<"В качестве промежуточного подсчета посмотрите на приведение к треугольному виду:\n"<<a;
    cout<<"Определитель матрицы:"<<endl;
    double det=1;
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < a.column; j++)
        {
            if(i==j) det=det*a.matrix[i][j];
            else det=det+0;
        }
    }

  
    return det;
}

Matrix inverse(Matrix &a) {
    if (a.row!=a.column) throw "Матрица необратима\n";
    Matrix B(a.row,2*a.row);
    int n=a.row;
    for(int i=0;i<n;i++)
        {
            for(int j=0;j<2*n;j++)
            {
                if(j>=n)
                {
                    if(i+n==j)
                        B.matrix[i][j]=1;
                    else
                        B.matrix[i][j]=0;
                }
                else
                    B.matrix[i][j]=a.matrix[i][j];
            }
        }
    cout << "Расширенная матрица,дополненная единичной:" << endl;
     for(int i=0;i<n;i++)
     {
         for(int j=0;j<2*n;j++)
         {
             cout << B.matrix[i][j] << " ";
         }
         cout << endl;
     }
    int m=0;
    int k=1;
    int i;
    int j;
    for(m=0;m!=n;m++)
       {
       cout << "Шаг-" << k <<endl;
       k++;
       for(i=m;i<n;i++)
       {
           for(j=2*n-1;j>=m;j--)
           {
               if(B.matrix[i][m]<0.000001)
               {
                   cout << "Матрица необратима" << endl;
                   exit(1);
               }
               else
                   B.matrix[i][j]=B.matrix[i][j]/B.matrix[i][m];
           }
       }
       for(i=0;i<n;i++)
       {
           for(j=0;j<2*n;j++)
           {
               cout << B.matrix[i][j] << " ";
           }
           cout << endl;
       }
       cout << "Шаг-" << k <<endl;
       k++;
       for(i=n-1;i>m;i--)
       {
           for(j=m;j<2*n;j++)
           {
               B.matrix[i][j]=B.matrix[i][j]-B.matrix[m][j];
           }
       }
       for(i=0;i<n;i++)
       {
           for(j=0;j<2*n;j++)
           {
               cout << B.matrix[i][j] << " ";
           }
           cout << endl;
       }
       }
       for(m=0;m!=n-1;m++)
       {
       cout << "Шаг-" << k <<endl;
       k++;
       for(i=m;i<n-1;i++)
       {
           for(j=2*n-1;j!=m;j--)
           {
               B.matrix[m][j]=B.matrix[m][j]-B.matrix[m][i+1]*B.matrix[i+1][j];
           }
       }
       for(i=0;i<n;i++)
       {
           for(j=0;j<2*n;j++)
           {
               cout << B.matrix[i][j] << " ";
           }
           cout << endl;
       }
       }    cout << "Обратная матрица:" << endl;
   for(i=0;i<n;i++)
     {
         for(j=n;j<2*n;j++)
         {
             cout << B.matrix[i][j] << " ";
         }
         
         cout << endl;
     }
     Matrix kk(n,n);
     vector<double> v;
     for(i=0;i<n;i++)
     {
         for(j=n;j<2*n;j++)
         {
          v.push_back(B.getelem(i,j));
         }
        
     }  int q=v.size();
     for( int i=0;i<n;i++){
         for (int j=0;j<n;j++){
         kk.matrix[i][j]=v[v.size()-q];
        q--;
         }
     }
     
     return kk;
    }

double scalarVectors(const Matrix& a,const Matrix& b){
    if ((a.column!=1)&(a.row!=1)) throw "Вы ввели не вектор\n";
    if ((b.column!=1)&(b.row!=1)) throw "Вы ввели не вектор\n";
    if ((a.column!=b.column)&(b.row!=a.column)) throw "Нельзя скалярно перемножить векторы разных размерностей\n";
    cout<<"Скалярное произведение векторов:"<<endl;
    double res=0;
    if ((a.column==b.column)&(a.row==1)){
    for (int i = 0; i < a.column; i++)
    {
                res = res+a.matrix[0][i] * b.matrix[0][i];
    }
    }
    else if((a.row==b.row)&(a.column==1)){
        {
        for (int i = 0; i < a.row; i++)
        {
                    res = res+a.matrix[i][0] * b.matrix[i][0];
        }
        }
    }
     else {
        for (int i = 0; i < a.row; i++)
        {
            for (int j = 0; j < b.row; j++)
            {
                    res = res+a.matrix[i][j] * b.matrix[j][i];
                
            }
        }}
    return res;
     }
double Trace(const Matrix&a){
    if (a.column!=a.row) throw "Матрица должна быть квадратной\n";
    cout<<"След матрицы:"<<endl;
    double trace=0;
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < a.column; j++)
        {
            if(i==j) trace=trace+a.matrix[i][j];
            else trace=trace+0;
        }
    }
        return trace;
}
double matrixNorm(const Matrix& a){
    //cout<<"Норма матрицы:"<<endl;
    double norm=0;
    for (int j=0; j<a.row;j++){
        for (int i=0;i<a.column;i++){
            norm =norm+ a.matrix[j][i]*a.matrix[j][i];
    }
    }
        norm=sqrt(norm);
    return norm;
}

double normOfvec(const Matrix& a){
    if ((a.column!=1)&(a.row!=1)) throw "Введен не вектор";
    int z;
    cout<<"Вид нормы: \n 1) Евклидова \n 2) Максимальная \n";
    cin>>z;
    cout<<"Норма вектора:"<<endl;
    double norm=0;    switch(z){
        case 1:{
        for (int j=0; j<a.row;j++){
            for (int i=0;i<a.column;i++){
                norm =norm+ a.matrix[j][i]*a.matrix[j][i];
        }
        }
            norm=sqrt(norm);
            break;
        }
        case 2:{
            norm=a.matrix[0][0];
                for (int j=0; j<a.row;j++){
                    for (int i=0;i<a.column;i++){
                        if (a.matrix[j][i]>norm)
                            norm=a.matrix[j][i];
                    }
                }
                    break;
        }
    }
    return norm;
}
Matrix hadamara(const Matrix& a,const Matrix &b){
    if ((a.column!=b.column)|(a.row!=b.row)) throw "Матрицы должны быть одной размерности\n";
    cout<<"Произведение Адамара"<<endl;
    Matrix result(a.row,b.column);
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < b.column; j++)
        {
                result.matrix[i][j] = a.matrix[i][j] * b.matrix[i][j];
            
        }
    }
    return result;
    
}
Matrix operator*(const Matrix& a,double scalar){
    cout<<"Умножение матрицы на число:"<<endl;

    Matrix result(a.row,a.column);
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < a.column; j++)
        {
            result.matrix[i][j] = a.matrix[i][j] * scalar;
        }
    }
    return result;
}


Matrix operator*(const Matrix& a, const Matrix& b) // ф-ция для перемножения матриц
{
 
   //cout << "Произведение матриц равно:" << endl;
    if (a.column!=b.row) throw "Количество столбцов 1 матрицы должно быть равно количеству строк 2 матрицы\n";
    Matrix result(a.row, b.column);
   for (int i = 0; i < a.row; i++)
   {
       for (int j = 0; j < b.column; j++)
       {
           result.matrix[i][j] = 0;
           for (int t = 0; t < b.row; t++)
           {
               result.matrix[i][j] += a.matrix[i][t] * b.matrix[t][j];
           }
       }
   }
   return result;
}
Matrix operator-(const Matrix& a, const Matrix& b) // ф-ция для перемножения матриц
{
    if ((a.column!=b.column)|(a.row!=b.row)) throw "Матрицы должны быть одной размерности\n";
    //cout << "Разность матриц равна:" << endl;
   Matrix result(a.row, b.column);
   for (int i = 0; i < a.row; i++)
   {
       for (int j = 0; j < b.column; j++)
       {
               result.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
           
       }
   }
   return result;
}
Matrix operator+(const Matrix& a, const Matrix& b) //ф-ция для сложения матриц
{ if ((a.column!=b.column)|(a.row!=b.row)) throw "Матрицы должны быть одной размерности\n";
    cout << "Сумма матриц равна:" << endl;
   Matrix result(a.row, a.column);
   for (int i = 0; i < a.row; i++)
   {
       for (int j = 0; j < a.column; j++)
       {
           result.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
       }
   }
   return result;
}

ostream& operator<<(ostream& out, const Matrix& m) //ф-ция для вывода матрицы
{
   for (int i = 0; i < m.row; i++)
   {
       for (int j = 0; j < m.column; j++)
           out << m.matrix[i][j] << " ";
       out << endl;
   }
   return out;
}

void singleMatrix::EnterSingleMatrix(){
    if (rows()!=cols()) throw "Матрица должна быть квадратной\n";
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < cols(); j++)
        {
            if (i==j){matrix[i][j]=1;}
            else { matrix[i][j]=0;}
        }
    }
}
void diagonalMatrix::EnterDiagonalMatrix(){
    int element;
    if (rows()!=cols()) throw "Матрица должна быть квадратной\n";
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < cols(); j++)
        {
            if (i==j){
                cout<<"Введите элемент на диагонали:\n";
                cin>>element;
                matrix[i][j]=element;
                
            }
            else { matrix[i][j]=0;}
        }
    }
}
Matrix Pca::centering(const Matrix &a){
    Matrix result(rows(), cols());
    for (int i = 0; i<cols(); i++)
 {
double sred = 0;
for (int j = 0; j<rows(); j++)
sred += a.matrix[j][i];
sred =sred/rows();
for (int j = 0; j<rows(); j++)
result.matrix[j][i] = a.matrix[j][i]-sred;
 }
 result.print();
 return result;
}
Matrix Pca::scaling(const Matrix &a){
    Matrix result1(rows(), cols());
    Matrix result(rows(), cols());
    Pca a1(rows(),cols());
    a1=a1.centering(a);

    for (int i = 0; i<cols(); i++) {
vector <double> v;
for (int j = 0; j < rows(); j++){
    v.push_back(a.matrix[j][i]);}
double sum = accumulate(v.begin(), v.end(), 0.0);
double m = sum / v.size();
double accum = 0.0;
for_each (std::begin(v), std::end(v), [&](const double d) {
    accum += (d - m) * (d - m);
});
double stdev = sqrt(accum / (v.size()-1));
cout<<stdev<<endl;
for (int j=0;j<rows();j++)
result1.matrix[j][i] = (a1.matrix[j][i])/stdev;
 }
result1.print();
 return result1;
}
tuple<Matrix,Matrix,Matrix> Pca::Nipals( Matrix &A,int pc){
    Pca d(rows(),cols());
    double epsilon=0.00000001;
    d=d.centering(A);
    d=d.scaling(d);
    Matrix e;
    Matrix y;
    e=d;
    auto rows=A.rows();
    auto cols=A.cols();
   Matrix t(static_cast<int>(rows), 1), p, t_old;
    vector<Matrix> T, P;
    for (size_t k = 0; k < pc; ++k) {
            for (size_t i = 0; i < pc; ++i) {
                t.matrix[i][0] = e.getelem(i, k);
            }
         do {
                p = transpose(transpose(t)*(e));
                double abss = (transpose(t)*(t)).matrix[0][0];
                for (size_t i = 0; i < pc; ++i) {
                    p.matrix[i][0] /= abss;
                }
                abss = matrixNorm(p);
                for (size_t i = 0; i < cols; ++i) {
                    p.matrix[i][0]  /= abss;
                }
                t_old = t;
                t = e*(p);
                abss = (transpose(p)*p).getelem(0, 0);
                for (size_t i = 0; i < rows; ++i) {
                    t.matrix[i][0] /= abss;
                }
        y=t_old-t;
        } while (matrixNorm(y) > epsilon);
        T.push_back(t);
        P.push_back(p);
        e = e - t*(transpose(p));
    }
    Matrix result_T(static_cast<int>(rows), static_cast<int>(T.size())),
                           result_P(static_cast<int>(P[0].rows()), static_cast<int>(P.size())),
                           result_E(static_cast<int>(rows), static_cast<int>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < T.size(); ++j) {
            result_T.matrix[i][j] = T[j].getelem(i, 0);
            if (i < (P[0].rows())) {
                result_P.matrix[i][j] = P[j].getelem(i, 0);
            }
        }
    }
  cout<<"scores Matrix T: "<<endl;
  result_T.print();
  cout<<"loadings Matrix P:"<<endl;
  result_P.print();
  cout<<"matrix of residuals:"<<endl;
  e.print();
  
    return {result_T, result_P, e};
}
Matrix Pca::leverage( Matrix &a,int pc){
    Pca nip(a.rows(),a.cols());
    auto res = nip.Nipals(a,pc);
    vector<double> v;
    Matrix h0(rows(),1) ;
    Matrix T_new=get<0>(res);
    Matrix t(1,pc) ;
    T_new.print();
     for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < pc; ++j) {
            t.matrix[0][j]=T_new.getelem(i,j);
     }
Matrix TT=(transpose(T_new)*T_new);
Matrix TTi=inverse(TT);
Matrix hi0=transpose(t);
Matrix hi01=t*TTi;
Matrix hi=hi01*hi0;
v.push_back(hi.matrix[0][0]);
    }
double sum = 0;
int i=0;
for (vector<double>::iterator it = v.begin(); it != v.end(); ++it) {
    sum += *it;
   h0.matrix[i][0]=sum/(i+1);
    i++;
}
h0.print();
  return h0;
}
 Matrix Pca::deviation( Matrix &a,int pc){
    Pca nip(a.rows(),a.cols());
    auto res = nip.Nipals(a,pc);
    Matrix vi(rows(),1) ;
    Matrix T_new=get<2>(res);
    for (int i=0;i<rows();i++){
        double dev=0;
        for (int j=0;j<pc;j++){
        dev+=T_new.matrix[i][j]*T_new.matrix[i][j];
        }
        vi.matrix[i][0] = dev;
        
    }
    cout<<"deviation of this matrix:\n";
    vi.print();
    return vi;
     }
double Pca::fullvar(Matrix &a,int pc){
    double res1=0;
    Pca nip(a.rows(),a.cols());
    auto res = nip.Nipals(a,pc);
    Matrix vi(rows(),1) ;
    Matrix E_new=get<2>(res);
    Matrix temp=deviation(E_new,pc);
    for (int i=0;i<rows();i++){
        res1+=temp.matrix[i][0];
    }
    cout<<"\nfullvar:\n"<<res1/(rows()*cols());
    return res1/(rows()*cols());
}
double Pca::expvar(Matrix &a,int pc){
    double res1;
    Pca nip(a.rows(),a.cols());
    auto res = nip.Nipals(a,pc);
    Matrix vi(rows(),1) ;
    Matrix E_new=get<2>(res);
    Matrix E=centering(E_new);
    E=scaling(E_new);
    res1=1-fullvar(E_new,pc)/fullvar(E,pc);
    cout<<"\nexpvar:\n"<<res1<<endl;
    return res1;
}
void simMatrix::EnterSimMatrix(){
    int element;
    if (rows()!=cols()) throw "Матрица должна быть квадратной\n";
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < cols(); j++)
        {
            if (i==j){
                cout<<"Введите элемент:\n";
                cin>>element;
                matrix[i][j]=element;
                
            }
            else if (i<j){
                cout<<"Введите элемент:\n";
                cin>>element;
                matrix[i][j]=element;}
            else matrix[i][j]=0;
        }
    }
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < cols(); j++){
            if (i!=j){matrix[j][i]=matrix[i][j];}
        }
    
    }
}
double angleBtwVecs(const Matrix& a, const Matrix& b){
    if ((a.column!=1)&(a.row!=1)) throw "Введен не вектор";
    if ((b.column!=1)&(b.row!=1)) throw "Введен не вектор";
    if (max(a.row,a.column)!=max(b.row,b.column)) throw "Векторы разных размерностей";
    double angle;
    double chisl=scalarVectors(a,b);
    double znam1=normOfvec(a);
    double znam2=normOfvec(b);
    angle=chisl/(znam1*znam2);
    cout<<"Угол между векторами:\n";
    return (acos(angle)*180)/(atan(1.0)*4);
}
double rank1(Matrix& b){
double d1,d2;
   for(int i=0;i<b.row-1;i++)
           {
               for(int j=i+1;j<b.row;j++)
               {
               double  l=lcm(b.matrix[i][i],b.matrix[j][i]);
               if(l!=0&&(b.matrix[i][i]!=0&&b.matrix[j][i]!=0))
                 {
                   l=(b.matrix[i][i]*b.matrix[j][i])/l;
                   d1=l/b.matrix[i][i];
                   d2=l/b.matrix[j][i];
                b.matrix[j][i]=0;
                   for(int k=i+1;k<b.row;k++)
                   {
                     b.matrix[j][k]=(d2*b.matrix[j][k])-(d1*b.matrix[i][k]);
                   }
                 }
               }
            }
    cout<<"Матрица в треугольном виде:\n"<<b<<endl;
    cout<<"Ранг матрицы:";
    double Rank=b.row;
    int flag=0;
    for (int i=0;i<b.row;i++){
        flag = 0;
        for (int j=0;j<b.column;j++){
            if (b.matrix[i][j]==0) {
                flag++;
                }
        }
            if (flag==b.column) --Rank;
    }

    return Rank;
}

