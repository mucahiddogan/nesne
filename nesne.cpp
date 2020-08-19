#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<cmath> //pow vs fonksiyonu
#include<algorithm> //swap fonksiyonu için
using namespace std;


//Matrix Class tanımlamaları
template <class T>
class Matrix{
    protected:
        int ROW;
        int COL;
        T value;
        T ** matrix;
    public:
        //~Matrix();
        Matrix();
        Matrix(int ,int);
        Matrix(int ROW, int COL, T value);
        // Matrix(int ROW, int COL, T value);
        Matrix<T> operator+(const Matrix&);
        Matrix<T> operator-(const Matrix&);
        Matrix<T> operator*(const Matrix&);
        Matrix<T> operator*(const T &num);
        Matrix<T> operator+(const T &num);
        Matrix<T> operator-(const T &num);
        Matrix<T> operator/(const T &num);
        Matrix<T> operator^(const T &num);


        void printMatrix();
        void fileprintMatrix();
        void resizeMatrix(int ROW,int COL);
        void Trans();
        void emul(const Matrix&);
        void det();
        void inv();
        Matrix(const Matrix&); 
};

// Table class tanımlamaları, inherit from matrix 
//satranç tahtası
template <class T>
class Table : public Matrix<T>{
    protected:
        string *ROWS;
        string *COLS;
    public:
        Table();
        Table(int ROW,int COL,T value);
        // Table(int ROW,int COL,T value);
        void printMatrix();
        T itemAt(int r,int c);
        T itemAt(string s);
        T itemAt(string rs,string cs);
        void setROWNames(string s[],int n);
        void setCOLNames(string s[],int n);
};

//matrix oluşturma 
template <class T>
Matrix<T>::Matrix(int r, int c){
    ROW = r;
    COL = c;
    matrix = new int*[ROW];
    for (int i=0; i<ROW; i++){
        matrix[i] = new int[COL];
      }
    for (int i=0; i<ROW; i++){
        for (int j=0; j<COL; j++){
          matrix[i][j] = 0;
        }
    }
}

//construck matris
template <class T>
Matrix<T>::Matrix(const Matrix& m){ 
    ROW = m.ROW;
    COL = m.COL;
    matrix = new int*[ROW];
    for (int i=0; i<ROW; i++){
        matrix [i] = new int[COL];
        }
    for (int i=0; i<ROW; i++){
        for (int j=0; j<COL; j++){
          matrix [i][j] = m.matrix [i][j];
        }
    }
}

// construct matris ile alınan değerlerin matrix e ataması
template <class T>
Matrix<T>::Matrix(int ROW, int COL, T value) {
    matrix = new int * [ROW];
    this -> ROW = ROW;
    this -> COL = COL;
    this -> value = value;

    if (value != 'e' && value != 'r' && value != (int)value) {
        cout << "wrong value" << endl;
        return;
    } else if (value == 'e') {
        for (int i = 0; i < ROW; i++) {
          matrix[i] = new int[COL];
        }
        for (int i = 0; i < ROW; i++) {
          for (int j = 0; j < COL; j++) {
            if (i == j) {
              matrix[i][j] = 1;
            } else
              matrix[i][j] = 0;
          }
        }
    } else if(value == 'r'){
        for (int i = 0; i < ROW; i++) {
        matrix[i] = new int[COL];
      }
        for (int i = 0; i < ROW; i++) {
          for (int j = 0; j < COL; j++) {
              matrix[i][j] = rand()%256 ;
          }
        }
    }
    // if(value == (int)value)
    else {
        for (int i = 0; i < ROW; i++){
            matrix[i] = new int[COL];
        }
        for (int i = 0; i < ROW; i++){
            for (int j = 0; j < COL; j++){
            matrix[i][j] = {value};
            }
        }
    }
}

// matrix operator işlemleri
template <class T>
Matrix<T> Matrix<T>::operator/(const T &num){   
    Matrix  newMatrix(ROW,COL);
    for(int i=0;i<ROW;i++){
       for(int j=0;j<COL;j++){
            newMatrix.matrix[i][j]=matrix[i][j] / num;
       }
    }
    return newMatrix;
}

template <class T>
Matrix<T>  Matrix<T>::operator-(const T &num){  
    Matrix newMatrix(ROW,COL);
    for(int i=0;i<ROW;i++)
       for(int j=0;j<COL;j++)
            newMatrix.matrix[i][j]=matrix[i][j]- num;
    return newMatrix;
}

template <class T>
Matrix<T>  Matrix<T>::operator+(const T &num){ 
    Matrix newMatrix(ROW,COL);
    for(int i=0;i<ROW;i++)
       for(int j=0;j<COL;j++)
            newMatrix.matrix[i][j]=matrix[i][j]+ num;
    return newMatrix;
}

template <class T>
Matrix<T>  Matrix<T>::operator*(const T &num){   
    Matrix newMatrix(ROW,COL);
    for(int i=0;i<ROW;i++)
       for(int j=0;j<COL;j++)
            newMatrix.matrix[i][j]=matrix[i][j]*num;
    return newMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator^(const T &num){
    Matrix newMatrix(ROW,COL);
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            newMatrix.matrix[i][j] = pow(matrix[i][j],num);
        }
    }
    return newMatrix;
}

//matrix operator 2 matrix arasında işlemler
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& m){
    if (ROW != m.ROW || COL != m.COL){
		cout << "Matrix sizes do not match." << endl;
		return (*this);
	}
	Matrix newMatrix(ROW,COL);
	for (int i=0; i<ROW; i++){
		for (int j=0; j<COL; j++){
			newMatrix.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
		}
	}

	  matrix = new int * [ROW];
        for (int i = 0; i < ROW; i++){
            matrix[i] = new int[COL];
        }
        for (int i = 0; i < ROW; i++){
            for (int j = 0; j < COL; j++){
                matrix[i][j] = newMatrix.matrix[i][j] ;
            }
        }
    return newMatrix;
    }

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& m){
    cout << m.ROW << endl;
    cout << ROW << endl;
    if (ROW != m.ROW || COL != m.COL){
        cout << "Matrix size is overwaited." << endl;
        return (*this);
    }

    Matrix newMatrix(ROW,COL);
    for (int i=0; i<ROW; i++){
        for (int j=0; j<COL; j++){
            newMatrix.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
        }
    }

        matrix = new int * [ROW];
        for (int i = 0; i < ROW; i++){
            matrix[i] = new int[COL];
        }
        for (int i = 0; i < ROW; i++){
            for (int j = 0; j < COL; j++){
                matrix[i][j] = newMatrix.matrix[i][j] ;
            }
        }
    return newMatrix;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix& m){
    if (COL != m.ROW ){
        cout << "Matrix doesn't match"<< endl ;
        return (*this);
    }
        Matrix newMatrix(ROW,m.COL);
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COL;j++){
                newMatrix.matrix[i][j]=0;
                for(int k=0;k<COL;k++){
                    newMatrix.matrix[i][j]= newMatrix.matrix[i][j]+matrix[i][k]*m.matrix[k][j];
                }
            }
        }

        matrix = new int * [ROW];
        for (int i = 0; i < ROW; i++) {
            matrix[i] = new int[COL];
        }
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                matrix[i][j] = newMatrix.matrix[i][j];
            }
        }
    return newMatrix;
}

//print matrix fonksiyonu
template <class T>
void Matrix<T>::printMatrix(){
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      cout << matrix[i][j];
      cout << " ";
    }
    cout << endl;
  }
}

// Transpoz matrix fonksiyonu
template <class T>
void Matrix<T>::Trans(){
    int temp;
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
    temp = ROW;
    ROW = COL;
    COL = temp;
}

// Eleman düzeyinde çarpma fonksiyonu
template <class T>
void Matrix<T>::emul(const Matrix& second){
    // cout<<second.ROW<<endl;
    // Matrix third;
    // third = second;
    if(second.ROW < ROW){
        cout<<"Second matrix's ROW mustn't be bigger than first matrixs"<<endl;
        // third.resizeMatrix(ROW,COL);
        // // for(int i=second.ROW;i<=ROW;i++){
        // //     for(int j=second.COL;j<=second.COL;j++){
        // //         second.matrix[i][j] = 0;
        // //     }
        // // }
        // for(int i=second.ROW;i<=ROW;i++){
        //     for(int j=second.COL;j<=second.COL;j++){
        //         cout<<third.matrix[i][j];
        //     }
        // }
    }else{
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COL;j++){
                matrix[i][j] = matrix[i][j] * second.matrix[i][j];
            }
        }
    }
}

// matrix determinantı fonksiyonu (3x3 ve azı için çalışıyor)
template <class T>
void Matrix<T>::det() {   
    int det = 0;
    if (ROW == 2)
        cout<<"determinant is: "<<((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]))<<endl;
    else {
        cout<<"matrix is bigger than 2x2"<<endl;
    }
}

template <class T>
void Matrix<T>::inv(){
    int det = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
    int detbolum = 1/det;
    swap(matrix[0][0],matrix[1][1]);
    matrix[0][1] = -matrix[0][1];
    matrix[1][0] = -matrix[1][0];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            matrix[i][j] = detbolum * matrix[i][j];
        }
    }
}

// matrix resize işlemi 
template <class T>
void Matrix<T>::resizeMatrix(int ROW,int COL){
    int ** newmatrix;
    newmatrix = new int * [ROW];
    for (int i = 0; i < ROW; i++) {
      newmatrix[i] = new int[COL];
    }
    if(this->ROW<=ROW && this->COL<=COL){
        for(int i=0;i<this->ROW;i++){
            for(int j=0;j<this->COL;j++){
                newmatrix[i][j]=matrix[i][j];
            }
        }
        matrix = new int * [ROW];
        for (int i = 0; i < ROW; i++) {
            matrix[i] = new int[COL];
        }


        for (int i = 0; i < this->ROW; i++) {
            for (int j = 0; j < this->COL; j++) {
                matrix[i][j] = newmatrix[i][j] ;
            }
        }
        this -> ROW = ROW;
        this -> COL = COL;
    }
    else if(this->ROW<=ROW && this->COL>=COL){
        for(int i=0;i<this->ROW;i++){
            for(int j=0;j<COL;j++){
                newmatrix[i][j]=matrix[i][j];
            }
        }
        matrix = new int * [ROW];
        for (int i = 0; i < ROW; i++) {
            matrix[i] = new int[COL];
        }
        for (int i = 0; i < this->ROW; i++) {
            for (int j = 0; j < COL; j++) {
                matrix[i][j] = newmatrix[i][j] ;
            }
        }
        this -> ROW = ROW;
        this -> COL = COL;
    }
    else if(this->ROW>=ROW && this->COL<=COL){
        for(int i=0;i<ROW;i++){
            for(int j=0;j<this->COL;j++){
                newmatrix[i][j]=matrix[i][j];
            }
        }
        matrix = new int * [ROW];
        for (int i = 0; i < ROW; i++) {
            matrix[i] = new int[COL];
        }
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < this->COL; j++) {
                matrix[i][j] = newmatrix[i][j] ;
            }
        }
        this -> ROW = ROW;
        this -> COL = COL;
    }
    else {
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COL;j++){
                newmatrix[i][j]=matrix[i][j];
            }
        }
        matrix = new int * [ROW];
        for (int i = 0; i < ROW; i++) {
            matrix[i] = new int[COL];
        }
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                matrix[i][j] = newmatrix[i][j];
            }
        }
        this -> ROW = ROW;
        this -> COL = COL;
    }
}

// matrix dosyaya yazdırma
template <class T>
void Matrix<T>::fileprintMatrix(){
    ofstream file;
    file.open ("matrix.txt",ios::app);

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            file << matrix[i][j];
            file << " ";
        }
        file << endl;
    }
    file.close();
    cout << "Yazma islemi tamamlandi"<<endl;
    system("PAUSE");
}

// Table Class inherit almış template classının matrisinde ilk elemanların
//a dan z ye veya 1 den sonsuza olduğunu belirten const
template <class T>
Table<T>::Table():Matrix<T>(10,10){
    ROWS = new string [10];
    for(int i=0;i<10;i++){
        ROWS[i] = string (1,'0' + i);
    }
    COLS = new string [10];
    for(int i=0;i<10;i++){
        COLS[i] = string (1,'A' + i);
    }   
}

//değer ataması inheritance i
template <class T>
Table<T>::Table(int r,int c, T d):Matrix<T>(r,c,d){
    ROWS = new string [r];
    for(int i=0;i<r;i++){
        ROWS[i] = string (1,'0' + i);
    }
    COLS = new string [c];
    for(int i=0;i<c;i++){
        COLS[i] = string (1,'A' + i);
    }   
}

//Table class satranç tahtası print matrix 
template <class T>
void Table<T>::printMatrix(){
    cout<<" ";
    for(int i=0;i<this->COL;i++){
        cout<<"  "<<COLS[i];
    }
    cout<<endl;
    for(int i=0;i<this->ROW;i++){
        cout<<ROWS[i]<<"  ";
        for(int j=0;j<this->COL;j++){
            cout<<this->matrix[i][j]<<"  ";
        }
        cout<<endl;
    }
}

// itemat fonksiyonları istediğimiz yerdeki değeri döndürür
template <typename T>
T Table<T>::itemAt(int r,int c){
    cout<<this->matrix[r][c];
    return this->matrix[r][c];
}

template <typename T>
T Table<T>::itemAt(string s){
    cout<<this->matrix[s[1] - 49][s[0] - 65];
    return this->matrix[s[1] - 49][s[0] - 65];
}

template <typename T>
T Table<T>::itemAt(string rs, string cs){
    cout<<this->matrix[rs[0] - 49][cs[0] - 65];
    return this->matrix[rs[0] - 49][cs[0] - 65];
}

// setcolnames matris değerlerini yeniden elle adlandırır
template <typename T>
void Table<T>::setCOLNames(string s[],int n){
    for (int i=0;i<n;i++){
        COLS[i] = s[i];
    }
}

template <typename T>
void Table<T>::setROWNames(string s[], int n){
    for (int i=0;i<n;i++){
        ROWS[i] = s[i];
    }
}

int main(int argc, const char * argv[]){
    srand(time(0));
    // Matrix<int> m1(10, 10, 0);
    // Matrix<int> m2(5, 2, 2);
    // Matrix<int> m3(5, 3, 9);
    // Matrix<int> m4(7, 8, 'e');
    // Matrix<int> m5(15,15,'r');
    // 
    // m3.printMatrix();
    // m3.fileprintMatrix();
    // m3.Trans();
    // m3.emul(m2);
    // m3.printMatrix();
    
    
    Matrix<int> m3(2,2,'r');
    // Matrix<int> m2(3,3,2);
    // m3 = m3 * m2 ;
    m3.printMatrix();
    m3.inv();
    m3.printMatrix();

    // Table<int> t1(5,5,5);
    // // t1.printMatrix();
    // // t1.itemAt("A2");
    // // t1.itemAt("1", "A");
    // string s[] = {"satir1","satir2","satir3","satir4"};
    // t1.setCOLNames(s,3);
    // t1.setROWNames(s,4);
    // t1.printMatrix();
    return 0;
}
