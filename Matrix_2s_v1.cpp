
#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <valarray>
#include <fstream>


const std::string result = "result.txt";//программа создаёт файл с результатом действий с матрицами

class matrix_t {
public:

    float ** data;
    unsigned int rows;
    unsigned int collumns;

    void add (matrix_t & other) {
       
        matrix_t new_mat ( rows, collumns ); //выделение памяти >> constr/destr+

        for ( unsigned int i = 0; i < rows; i++ ) {
            for ( unsigned int j = 0; j < collumns; j++ ) {
                new_mat.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        std::ofstream fout ( result);
        
        if ( fout.is_open () ) {
            new_mat.write (fout);
            std::cout << "res written\n";
        }
        fout.close ();
    }

    void sub (matrix_t & other) {
         matrix_t new_mat ( rows, collumns ); //выделение памяти >> constr/destr+

        for ( unsigned int i = 0; i < rows; i++ ) {
            for ( unsigned int j = 0; j < collumns; j++ ) {
                new_mat.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        std::ofstream fout ( result);
        
        if ( fout.is_open () ) {
            new_mat.write (fout);
            std::cout << "res written\n";
        }
        fout.close ();
    }

    void mul (matrix_t & other) {
        matrix_t new_mat ( rows, collumns ); //выделение памяти >> constr/destr+
        auto common_row_and_col = collumns; //!!!!
        
        for ( unsigned int i = 0; i < rows; i++ ) {
            for ( unsigned int j = 0; j < other.collumns; j++ ) {
                float sum = 0.0f;
                for ( unsigned int k = 0; k < common_row_and_col; k++ ) {
                    sum += data[i][k] * other.data[k][j];
                }
                new_mat.data[i][j] = sum;
            }
        }/////
        
        
        std::ofstream fout ( result);
        
        if ( fout.is_open () ) {
            new_mat.write (fout);
            std::cout << "res written\n";
        }
        fout.close ();

    }

    void trans ()  {
        matrix_t new_mat ( collumns, rows );
        for ( unsigned int i = 0; i < collumns; i++ ) {
            for ( unsigned int j = 0; j < rows; j++ ) {
                new_mat.data[i][j] =data[j][i];
            }
        }
        std::ofstream fout ( result);

        if ( fout.is_open () ) {
            new_mat.write (fout);
            std::cout << "res written\n";
        }
        fout.close ();
    }
    
    bool rev (){
        
    }

    std::ifstream & read (std::ifstream & stream) {
        bool success = true;
        for ( unsigned int i = 0; i < rows && success; i++ ) {
            for ( unsigned int j = 0; j < collumns; ++j ) {
                if ( !( stream >> data[i][j] ) ) {
                    success = false;
                    stream.setstate ( std::ios::failbit ); //???
                    break;
                }
            }
        }
        return stream;
    }

    std::ofstream & write (std::ofstream & stream) {//config mian

        for ( unsigned int i = 0; i < rows; i++ ) {
            for ( unsigned int j = 0; j < collumns; j++ ) {
                stream.width ( 5 );
                stream << data[i][j];
            }
            stream << std::endl;
        }
    }

    matrix_t (std::ifstream & stream ) {
        unsigned char coma;
        if (  stream >> rows && stream >> coma && coma == ',' &&  stream >> collumns  ) {
            filler ();
            read (stream);
        } else {
            stream.setstate ( std::ios::failbit );
            std::cout << "An error has occured while reading input data";
            exit (EXIT_FAILURE);
        }
    }

    void filler () {
        float filler = 0.0f; //seperate func
        data = new float *[rows];
        for ( unsigned int i = 0; i < rows; ++i ) {
            data[i] = new float[collumns];
            for ( unsigned int j = 0; j < collumns; ++j ) {
                data[i][j] = filler;
            }
        }
    }

    matrix_t (unsigned int rows, unsigned int collumns) {
        this->rows = rows;
        this->collumns = collumns;
        filler ();


    }

    ~matrix_t () {

        for ( unsigned int i = 0; i < rows; ++i ) {
            delete[] data[i];
        }
        delete[] data;
    }
} ;

void fstr_print (std::ifstream & fin) {
    while ( !( fin.eof () ) ) {
        float buff;
        if ( fin >> buff ) {
            std::cout.width (5);
            std::cout << buff ;
        }
        if ( fin.peek () == '\n' ) std::cout << "\n";
    }
}

int main () {
    

    unsigned char operator_char;


    std::string adress;
    std::cin>>adress;
    std::ifstream fin;
    fin.open ( adress );
    if ( fin.is_open () ) std::cout << "ok\n";
    matrix_t matrix_1 (fin); 
    if ( fin )
    {
        fin.close ();
        if ( std::cin >> operator_char ) {
            std::cin.get ();
        } else {
            std::cout << "An error has occured while reading input data";
            exit (EXIT_FAILURE);
        }
    } else {
        fin.close ();
        std::cout << "An error has occured while reading input data";
        exit (EXIT_FAILURE);
    }
    switch ( operator_char ) {
        case '+' : 
        case '-' :
        {

            adress = "";
            std::cin>>adress;
            fin.open ( adress );
            matrix_t matrix_2 (fin);

            if ( fin && ( matrix_1.rows == matrix_2.rows && matrix_1.collumns == matrix_2.collumns ) ) {

                if (operator_char == '+') 
                    matrix_1.add ( matrix_2);
                else if (operator_char == '-') 
                    matrix_1.sub( matrix_2);
                fin.close ();
                fin.open ( result);
                fstr_print (fin);
                fin.close ();

            } else {
                fin.close ();
                std::cout << "An error has occured while reading input data";
                exit (EXIT_FAILURE);
            }

            break;
        }
            
            case '*':
            {
            adress = "";
            std::cin>>adress;
            fin.open ( adress );
            matrix_t matrix_2 (fin);   
                if ( fin && ( matrix_1.collumns == matrix_2.rows ) ) {
                    
                matrix_1.mul ( matrix_2);
                fin.close ();
                fin.open ( result);
                fstr_print (fin);
                fin.close ();  
                    
                } else {
                    
                    std::cout << "An error has occured while reading input data";
                    exit (EXIT_FAILURE);
                }

                break;
            }
            case 'T':
            {
                if ( matrix_1.rows == matrix_1.collumns){
                matrix_1.trans();
                fin.close ();
                fin.open ( result);
                fstr_print (fin);
                fin.close ();  
                }else {
                std::cout << "An error has occured while reading input data";
                exit (EXIT_FAILURE);
            }
                
                break;
            }
         
        default:
        {
            std::cout << "An error has occured while reading input data";
            exit (EXIT_FAILURE);
        }
    }

    return 0;
}
