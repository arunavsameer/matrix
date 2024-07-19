#include <iostream>
#include <vector>
#include <thread>
#include <math.h>

using namespace std;

class matrix{
protected:
    vector <vector <float>> data;
    int rows, cols;

    float input(){
        float a; cin >> a;
        return a;
    }

    void multiply_block(matrix &A, const matrix &B, int start_row, int end_row){
        for(int i = start_row; i < end_row; i++){
            for(int j = 0; j < B.cols; j++){
                for(int r = 0; r < cols; r++){
                    A.data[i][j] += data[i][r] * B.data[r][j];
                }
            }
        }
    }
    
    void reduce_rows(int pivot_x, int pivot_y){
        for(int i = pivot_x + 1; i < rows; i++){
            float factor = data[i][pivot_y] / data[pivot_x][pivot_y];
            for(int j = 0; j < cols; j++){
                data[i][j] -= factor * data[pivot_x][j];
            }
        }
    }

public:
    void set_element(int row, int col, float value) {
        data[row][col] = value;
    }

    float get_element(int row, int col) const {
        return data[row][col];
    }

    const vector <vector <float>> get_data(){
        return data;
    }

    matrix() : rows(1), cols(1){
        data.resize(1, vector<float> (1, 0));
    }

    matrix(int r, int c, int a = 0) : rows(r), cols(c){
        data.resize(rows, vector<float> (cols, 0));
        for(int i = 0; i< rows; i++){
            for(int j = 0; j < cols; j++){
                data[i][j] = (a == 0) ? 0 : a;
            }
        }
    }

    void reshape(int x, int y){
        data.resize(x, vector<float> (y, 0));
        rows = x;
        cols = y;
    }

    void identity(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                data[i][j] = (i == j) ? 1 : 0;
            }
        }
    }    

    void input_init(){
        for(int i = 0; i< rows; i++){
            for(int j = 0; j < cols; j++){
                data[i][j] = input();
            }
        }
    }

    matrix operator * (matrix& other){
        int num_threads = 16;
        vector <thread> Threads;
        int rows_per_thread = rows / num_threads;
        int start_row = 0;
        matrix A(rows, other.cols, 0);
        for(int i = 0; i < num_threads; i++){
            int end_row = (i == num_threads - 1) ? rows : start_row + rows_per_thread;
            Threads.push_back(thread(&matrix::multiply_block,this, ref(A), ref(other), start_row, end_row));
            start_row = end_row;
        }
        for(auto &t: Threads){
            t.join();   
        }
        return A;
    }
    template <typename T>
    matrix operator *(T k){
        matrix A(rows, cols, 0);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                A.data[i][j] = data[i][j] * k;
            }
        }
        return A;
    }
    
    matrix operator + (matrix& other){
        matrix A(rows, cols, 0);
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                A.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return A;
    }

    matrix operator - (matrix& other){
        matrix A(rows, cols, 0);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                A.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return A;
    }

    float determinant(){
        if (rows != cols) {
            cerr << "Error: Determinant can only be calculated for square matrices." << endl;
            return 0;
        }
        matrix A = *this;
        float determinant = 1;
        int pivot_index = 0;
        for(pivot_index; pivot_index < (rows - 1); pivot_index++){
            if(A.data[pivot_index][pivot_index] == 0.0f){
                bool swapped = false;
                for (int i = pivot_index + 1; i < rows; i++) {
                    if (A.data[i][pivot_index] != 0.0f) {
                        swap(A.data[pivot_index], A.data[i]);
                        determinant *= -1;
                        swapped = true;
                        break;
                    }
                }
                if (!swapped) return 0.0f;
            }
            determinant *= A.data[pivot_index][pivot_index];
            A.reduce_rows(pivot_index, pivot_index);
        }
        determinant *= A.data[pivot_index][pivot_index];
        return determinant;
    }

    void print_matrix(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cout << data[i][j] <<"  ";
            }
            cout << endl;
        }
    }
};