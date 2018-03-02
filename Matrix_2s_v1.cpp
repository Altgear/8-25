#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <valarray>
#include <fstream>


const std::string result = "result.txt"; //программа создаёт файл с результатом действий с матрицами

class matrix_t {
public:

    float ** data;
    unsigned int rows;
    unsigned int collumns;

    matrix_t add(matrix_t const & other) {

        matrix_t new_mat(rows, collumns); //выделение памяти >> constr/destr+

        for ( unsigned int i = 0; i < new_mat.rows; i++ ) {
            for ( unsigned int j = 0; j < new_mat.collumns; j++ ) {
                new_mat.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return new_mat;
    }

    matrix_t sub(const matrix_t & other) {
        matrix_t new_mat(rows, collumns); //выделение памяти >> constr/destr+

        for ( unsigned int i = 0; i < rows; i++ ) {
            for ( unsigned int j = 0; j < collumns; j++ ) {
                new_mat.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return new_mat;
    }

    matrix_t mul(matrix_t & other) {
        matrix_t new_mat(rows, other.collumns); //выделение памяти >> constr/destr
        auto common_row_and_col = collumns; //!!!!

        for ( unsigned int i = 0; i < rows; i++ ) {
            for ( unsigned int j = 0; j < other.collumns; j++ ) {
                float sum = 0.0f;
                for ( unsigned int k = 0; k < common_row_and_col; k++ ) {
                    sum += data[i][k] * other.data[k][j];
                }
                new_mat.data[i][j] = sum;
            }
        }
        return new_mat;

    }

    matrix_t trans() {
        matrix_t new_mat(collumns, rows);
        for ( unsigned int i = 0; i < collumns; i++ ) {
            for ( unsigned int j = 0; j < rows; j++ ) {
                new_mat.data[i][j] = data[j][i];
            }
        }
        return new_mat;

    }

    /*
        bool rev() {
            //bool m_reverse(float **  wide_matrix, float ** result_matrix, unsigned int rows_n_columns)
        
        for (unsigned int i = 0; i < rows; i++)
        {

            for (unsigned int j = 0; j < collumns; j++)
            {
                if (i == j)
                {
                    if (data[j][i] != 0.0)
                    {
                        if (wide_matrix[j][i] != 1.0)
                        {
                            float buff = wide_matrix[j][i];
                            for (unsigned int k = 0; k < rows_n_columns * 2; k++)
                            {

                                wide_matrix[j][k] /= buff;
                                if (wide_matrix[j][k] == -0.0) { wide_matrix[j][k] = 0; }
                            }
                        }
                    }
                    else
                    {
                        bool found = false;
                        for (unsigned int k = 0; k < rows_n_columns && (!(found)); k++)
                        {
                            if (j != k && wide_matrix[k][i] != 0.0)
                            {
                                found = true;
                                for (unsigned int l = 0; l < rows_n_columns * 2; l++)
                                {
                                    wide_matrix[j][l] += (wide_matrix[k][l] / wide_matrix[k][i]);
                                }
                            }

                        }
                        if (!(found)) { return false; }
                    }
                }
                else
                {
                    if (wide_matrix[j][i] != 0.0)
                    {
                        bool found = false;
                        for (unsigned int k = 0; k < rows_n_columns && (!(found)); k++)
                        {
                            if (j != k && wide_matrix[k][i] != 0.0)
                            {
                                found = true;
                                float buff = wide_matrix[j][i];
                                for (unsigned int l = 0; l < rows_n_columns * 2; l++)
                                {

                                    wide_matrix[j][l] -= wide_matrix[k][l] * (buff / wide_matrix[k][i]);

                                }

                            }
                        }
                        if (!(found)) { return false; }
                    }
                }
            }
        }
        for (unsigned int i = 0; i < rows_n_columns; ++i)
        {
            for (unsigned int j = 0; j < rows_n_columns; ++j)
            {
                result_matrix[i][j] = wide_matrix[i][j + 3];
            }
        }
        return true;
        }
     */

    std::ifstream & read(std::ifstream & stream) {
        if ( data != nullptr && rows && collumns ) {
            destroy_data(); //!!!
        }
        unsigned char coma;
        if ( stream >> rows && stream >> coma && coma == ',' && stream >> collumns ) {
            bool success = true;
            data = new float *[rows];
            for ( unsigned int i = 0; i < rows && success; i++ ) {
                data[i] = new float[collumns];
                for ( unsigned int j = 0; j < collumns; ++j ) {
                    if ( !( stream >> data[i][j] ) ) {
                        success = false;
                        stream.setstate(std::ios::failbit); //???
                        break;
                    }
                }
            }
        } else {
            stream.setstate(std::ios::failbit);
            std::cout << "An error has occured while reading input data";
            exit(EXIT_FAILURE);
        }
        return stream;
    }

    std::ofstream & write(std::ofstream & stream) {//config mian
        for ( unsigned int i = 0; i < rows; i++ ) {
            for ( unsigned int j = 0; j < collumns; j++ ) {
                stream.width(5);
                stream << data[i][j]; //HERE
            }
            stream << std::endl;
        }
    }// через fout_write()

    /*  matrix_t(std::ifstream & stream) {//конструктор1
          unsigned char coma;
          if ( stream >> rows && stream >> coma && coma == ',' && stream >> collumns ) {
              filler();
              read(stream);
          } else {
              stream.setstate(std::ios::failbit);
              std::cout << "An error has occured while reading input data";
              exit(EXIT_FAILURE);
          }
      }*/
    //to delte

    matrix_t(unsigned int rows, unsigned int collumns) {//конструктор2
        this->rows = rows;
        this->collumns = collumns;
        filler();
    }

    matrix_t(const matrix_t & other) {//констр копир-я
        *this = other; //перегруж-я опер-я присв-я
    }

    matrix_t() {
        this->rows = 0;
        this->collumns = 0;
        data = nullptr;
    }

    void filler() {
        float filler = 0.0f; //seperate func
        data = new float *[rows];
        for ( unsigned int i = 0; i < rows; ++i ) {
            data[i] = new float[collumns];
            for ( unsigned int j = 0; j < collumns; ++j ) {
                data[i][j] = filler;
            }
        }
    }

    matrix_t & operator=(const matrix_t & other ) {// перегрузка оператора присв-я
        if ( this != &other ) {
            if ( data != nullptr && rows && collumns ) {
                destroy_data(); //!!!
            }
            rows = other.rows;
            collumns = other.collumns;
            data = new float *[rows];
            for ( unsigned int i = 0; i < rows; ++i ) {
                data[i] = new float[collumns];
                for ( unsigned int j = 0; j < collumns; ++j ) {
                    data[i][j] = other.data[i][j];
                }

            }
            return *this;
        }
    }

    void destroy_data() {
        for ( unsigned int i = 0; i < rows; ++i ) {
            delete[] data[i];
        }
        delete[] data;
    }

    void fout_write() {
        std::ofstream fout(result);

        if ( fout.is_open() ) {
            write(fout);
        }
        fout.close();
    }

    ~matrix_t() {
        rows = 0;
        collumns = 0;
        destroy_data();
        //data = nullptr;//???
    }

};

void fstr_print(std::ifstream & fin) {
    while ( !( fin.eof() ) ) {
        float buff;
        if ( fin >> buff ) {
            std::cout.width(5);
            std::cout << buff;
        }
        if ( fin.peek() == '\n' ) std::cout << "\n";
    }
}

int main() {

    unsigned char operator_char;
    std::string adress;
    std::cin>>adress;
    std::ifstream fin;
    fin.open(adress);
    matrix_t matrix_1;

    if ( fin.is_open() )
        matrix_1.read(fin);
    if ( fin ) {
        fin.close();
        if ( std::cin >> operator_char ) {
            std::cin.get();
        } else {
            std::cout << "An error has occured while reading input data";
            exit(EXIT_FAILURE);
        }
    } else {
        fin.close();
        std::cout << "An error has occured while reading input data";
        exit(EXIT_FAILURE);
    }
    switch ( operator_char ) {
        case '+':
        case '-':
        {

            adress = "";
            std::cin>>adress;
            fin.open(adress);
            matrix_t matrix_2;
            if ( fin.is_open() )
                matrix_2.read(fin);
            if ( fin &&
                 ( matrix_1.rows == matrix_2.rows
                 && matrix_1.collumns == matrix_2.collumns ) ) {
                matrix_t res_matrix;
                if ( operator_char == '+' )
                    res_matrix = matrix_1.add(matrix_2); //new obj
                else if ( operator_char == '-' )
                    res_matrix = matrix_1.sub(matrix_2); // new obj
                fin.close();
                res_matrix.fout_write();
                fin.open(result);
                fstr_print(fin);
                fin.close();

            } else {
                fin.close();
                std::cout << "An error has occured while reading input data";
                exit(EXIT_FAILURE);
            }

            break;
        }

        case '*':
        {
            adress = "";
            std::cin>>adress;
            fin.open(adress);
            matrix_t matrix_2;
            matrix_2.read(fin);
            if ( fin &&
                 ( matrix_1.collumns == matrix_2.rows ) ) {
                matrix_t res_matrix;
                res_matrix = matrix_1.mul(matrix_2);
                fin.close();
                res_matrix.fout_write();
                fin.open(result);
                fstr_print(fin);
                fin.close();

            } else {

                std::cout << "An error has occured while reading input data";
                exit(EXIT_FAILURE);
            }

            break;
        }
        case 'T':
        {
            if ( matrix_1.rows == matrix_1.collumns ) {
                matrix_t res_matrix;
                res_matrix = matrix_1.trans();
                fin.close();
                res_matrix.fout_write();
                fin.open(result);
                fstr_print(fin);
                fin.close();
            } else {
                std::cout << "An error has occured while reading input data";
                exit(EXIT_FAILURE);
            }

            break;
        }
            /* case 'R':
              {
                  if ( matrix_1.rows == matrix_1.collumns ) {
                    
                      matrix_t wide_matrix( matrix_1.rows, matrix_1.collumns * 2 );
                      for ( unsigned int i = 0; i < matrix_1.rows; ++i ) {
                          for ( unsigned int j = 0; j < matrix_1.collumns * 2; ++j ) {
                              if ( j < 3 ) {
                                  wide_matrix[i][j] = matrix_1[i][j];
                              } else {
                                  if ( i + 3 == j ) {
                                      wide_matrix[i][j] = 1.0f;
                                  }
                              }
                          }
                      }
                      if ( m_reverse (wide_matrix, result_matrix, rows_1) ) { //here
                          print_mat (result_matrix, rows_1, columns_1);
                      } else {
                          std::cout << "det=0 -> reverse matrix doesn't exist ";
                          exit (EXIT_FAILURE);
                      }
                  
                  } else {
                      std::cout << "An error has occured while reading input data";
                      exit (EXIT_FAILURE);
                  }
                  break;
              }*/

        default:
        {
            std::cout << "An error has occured while reading input data";
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
