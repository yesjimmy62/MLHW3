#include "General.h"


//MatrixXd *real_answer=NULL;

//MatrixXd *data=NULL;

int main()
{
    cout<<"HAHA! START RNN!"<<endl;

    int num_layer = 3; //include input layer, hidden layer, and output layer

    int layer_size[num_layer];
    
    
    layer_size[0] = 200;
    layer_size[1] = 100;
    layer_size[2] = 200;
    

    /*
    //toy data
    layer_size[0] = 3;
    layer_size[1] = 50;
    layer_size[2] = 10;
    */

    int num_memory = 1;
    int memory_layer[num_memory];
    memory_layer[0] = 1;

    RNN RNNobject(num_layer, layer_size, num_memory, memory_layer);

    RNNobject.Print_LayerInfo();


    MatrixXd *data=NULL;
    MatrixXd *real_answer=NULL;

    //chose your data
    
    int YourData = 1; //0: toy data, 1:HW3 data
    int num_data;

    if (YourData == 0)
    {
        // toy files
        data = Load_Data("input_files/input.txt", data, &num_data);
        real_answer = Load_Data("input_files/output.txt", real_answer, &num_data);
    }
    else if (YourData == 1)
    {

        // our real homework data
        //data = Load_Data("input_files/hw3_real_input.txt", data, &num_data);
        data = Load_Data("input_files/TRAIN_INPUT.TXT", data, &num_data);
        real_answer = HW3_MakingAnswers(data, real_answer, num_data);
        //real_answer = Load_Data("input_files/output.txt", real_answer);
    }
    else
    {
        cout<<"No such data type (wrong variable: YourData)"<<endl;
        exit(0);
    }

    cout<<"data info:"<<endl;
    cout<<"data->rows():"<<data[0].rows()<<endl;
    for (int i=0; i<num_data;i++)
    {
        cout<<"real_answer["<<i<<"].min_Coeff():"<<real_answer[i].minCoeff()<<endl;
        cout<<"real_answer["<<i<<"].max_Coeff():"<<real_answer[i].maxCoeff()<<endl;
    }
    

    int num_epoch = 20;
    double learning_rate = 0.001;
    //double learning_rate = 0.1;

    cout<<"num_data:"<<num_data<<endl;
    RNNobject.Training(num_data, data, real_answer, num_epoch, learning_rate);

    return 0;
}
