#include </run/media/arunav/Data/programming/C++/Matrix/matrix.hpp>
#include <iomanip>


class vect: public matrix{
protected:
    int dims;
    matrix entry;
public:
    vect() : dims(0){}

    vect(int d) : matrix(d, d), dims(d) {
        entry.reshape(dims, 1);
        this -> identity();
    }
 
    void print_vector(){
        for(int i = 0; i < dims; i++){
            cout << entry.get_element(i, 0) <<endl;
        }
    }

    void transform(){
        entry = matrix :: operator* (entry);
        matrix :: identity();
    }

    void scale(float factor){
        matrix scl_mat(dims, dims, 0);
        scl_mat.identity();
        scl_mat = scl_mat * factor;
        this -> data = (matrix :: operator* (scl_mat)).get_data();
        //print_matrix();
    }
};

class vect2 : public vect{
public:
    vect2(int x, int y){
        matrix :: reshape(2, 2);
        matrix :: rows = 2;
        matrix :: cols = 2;
        matrix :: identity();
        vect :: dims = 2;
        vect :: entry.reshape(2, 1);
        vect :: entry.set_element(0, 0, x);
        vect :: entry.set_element(1, 0, y);
    }

    void rotate(float theta){
        matrix rot_mat(2, 2, 0);
        rot_mat.set_element(0, 0, cosf(theta));
        rot_mat.set_element(0, 1, -sinf(theta));
        rot_mat.set_element(1, 0, sinf(theta));
        rot_mat.set_element(1, 1, cosf(theta));
        this -> data = (matrix :: operator* (rot_mat)).get_data();
        //print_matrix();
    }
};

class vect3 : public vect{
public:
    vect3(int x = 0, int y = 0, int z = 0){
        matrix :: reshape(3, 3);
        matrix :: rows = 3;
        matrix :: cols = 3;
        matrix :: identity();
        vect :: dims = 3;
        vect :: entry.reshape(3, 1);
        vect :: entry.set_element(0, 0, x);
        vect :: entry.set_element(1, 0, y);
        vect :: entry.set_element(2, 0, z);
    }
    
    void rotate_x(float theta){
        matrix rot_mat(3, 3, 0);
        rot_mat.set_element(0, 0, 1);
        rot_mat.set_element(0, 1, 0);
        rot_mat.set_element(0, 2, 0);
        rot_mat.set_element(1, 0, 0);
        rot_mat.set_element(1, 1, cosf(theta));
        rot_mat.set_element(1, 2, -sinf(theta));
        rot_mat.set_element(2, 0, 0);
        rot_mat.set_element(2, 1, sinf(theta));
        rot_mat.set_element(2, 2, cosf(theta));

        this -> data = (matrix :: operator* (rot_mat)).get_data();
        //print_matrix();
    }

    void rotate_y(float theta){
        matrix rot_mat(3, 3, 0);
        rot_mat.set_element(0, 0, cosf(theta));
        rot_mat.set_element(0, 1, 0);
        rot_mat.set_element(0, 2, sinf(theta));
        rot_mat.set_element(1, 0, 0);
        rot_mat.set_element(1, 1, 1);
        rot_mat.set_element(1, 2, 0);
        rot_mat.set_element(2, 0, -sinf(theta));
        rot_mat.set_element(2, 1, 0);
        rot_mat.set_element(2, 2, cosf(theta));

        this -> data = (matrix :: operator* (rot_mat)).get_data();
        //print_matrix();
    }
    
    void rotate_z(float theta){
        matrix rot_mat(3, 3, 0);
        rot_mat.set_element(0, 0, cosf(theta));
        rot_mat.set_element(0, 1, -sinf(theta));
        rot_mat.set_element(0, 2, 0);
        rot_mat.set_element(1, 0, sinf(theta));
        rot_mat.set_element(1, 1, cosf(theta));
        rot_mat.set_element(1, 2, 0);
        rot_mat.set_element(2, 0, 0);
        rot_mat.set_element(2, 1, 0);
        rot_mat.set_element(2, 2, 1);

        this -> data = (matrix :: operator* (rot_mat)).get_data();
        //print_matrix();
    }
};

int main(){
    vect3 A(1, 1, 1);
    A.rotate_y(1.5708);
    A.scale(2);
    A.rotate_z(1.5708 / 2);
    A.transform();
    A.print_vector();
}