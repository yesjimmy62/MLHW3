#include "General.h"


//MatrixXd *real_answer=NULL;

//MatrixXd *data=NULL;

int main()
{
    cout<<"HAHA! START RNN!"<<endl;

    int num_layer = 3; //include input layer, hidden layer, and output layer

    int layer_size[num_layer];
    layer_size[0] = 3;
    layer_size[1] = 12;
    layer_size[2] = 10;

    int num_memory = 1;
    int memory_layer[num_memory];
    memory_layer[0] = num_layer - 1;

    RNN RNNobject(num_layer, layer_size, num_memory, memory_layer);

    RNNobject.Print_LayerInfo();


    MatrixXd *data=NULL;
    MatrixXd *real_answer=NULL;

    data = Load_Data("input_files/input.txt", data);
    real_answer = Load_Data("input_files/output.txt", real_answer);


    cout<<"data->rows():"<<data[0].rows()<<endl;
    cout<<"real_answer->rows():"<<real_answer[0].rows()<<endl;

    int num_epoch = 50;
    int num_data = 10; //QQQQQQQQQQQQQQQQQQQQQ

    cout<<"num_data:"<<num_data<<endl;
    
    RNNobject.Training(num_data, data, real_answer, num_epoch);

    return 0;
}
