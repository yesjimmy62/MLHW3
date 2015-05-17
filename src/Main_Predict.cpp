#include "General.h"

int main()
{
    char dir_path[100] = "output_files/";
    char dir_path2[100];


    // <^> (a) read the BasicSetting.txt file
    strcpy(dir_path2, dir_path);
    ifstream fin(strcat(dir_path2, "BasicSetting.txt"));
    
    int num_layer;
    string line;
    getline(fin, line); //number of layers:
    fin>>num_layer;
    getline(fin, line);
    getline(fin, line); //layer size:
    int layer_size[num_layer];
    for (int i=0; i<num_layer; i++)
        fin>>layer_size[i];
    getline(fin, line);
    
    int num_memory;
    getline(fin, line); //number of memory:
    fin>>num_memory;
    getline(fin, line);

    int memory_layer[num_memory];
    getline(fin, line); //memory layer
    for (int i=0; i<num_memory; i++)
        fin>>memory_layer[i];

    fin.close();

    cout<<"number of layers:"<<num_layer<<endl;
    cout<<"layer_size:"<<endl;
    for (int i=0; i<num_layer; i++)
        cout<<layer_size[i]<<"  ";
    cout<<endl;
    cout<<"number of memory:"<<num_memory<<endl;



    // <^> (b) read the NormalParameters.txt file
    strcpy(dir_path2, dir_path);
    fin.open(strcat(dir_path2, "NormalParameters.txt"));

    MatrixXd *weight;
    MatrixXd *bias;
    int num_weight = num_layer - 1;
    weight = new MatrixXd [num_weight];
    bias = new MatrixXd [num_weight];
    for (int i=0; i<num_weight; i++)
    {
        weight[i] = MatrixXd::Constant(layer_size[i+1], layer_size[i], 0);
        bias[i] = MatrixXd::Constant(layer_size[i+1], 1, 0);
    }

    for (int i=0; i<num_weight; i++)
    {
        // <^> bias
        getline(fin, line); //bias:

        for (int j=0; j< layer_size[i+1]; j++)
            fin>>bias[i](j, 0);

        // <^> weight
        getline(fin, line);
        getline(fin, line); //weight:
        for (int j=0; j < layer_size[i+1]; j++)
            for (int k=0; k < layer_size[i]; k++)
                fin>>weight[i](j, k);

        getline(fin, line);
    }
    
    fin.close();
    cout<<"Hello!"<<endl;

    // <^> (c) read the MemoryParameters.txt file
    strcpy(dir_path2, dir_path);
    fin.open(strcat(dir_path2, "MemoryParameters.txt"));

    MatrixXd *m_weight;
    MatrixXd *m_bias;
    m_weight = new MatrixXd [num_memory];
    m_bias = new MatrixXd [num_memory];
    for (int i=0; i<num_memory; i++)
    {
        int index = memory_layer[i];
        m_weight[i] = MatrixXd::Constant(layer_size[index], layer_size[index], 0);
        m_bias[i] = MatrixXd::Constant(layer_size[index], 1, 0);
    }

    for (int i=0; i<num_memory; i++)
    {
        // <^> bias
        getline(fin, line); //bias:
        int index = memory_layer[i];
        for (int j=0; j< layer_size[index]; j++)
            fin>>m_bias[i](j, 0);

        // <^> weight
        getline(fin, line);
        getline(fin, line); //weight:
        for (int j=0; j < layer_size[index]; j++)
            for (int k=0; k < layer_size[index]; k++)
                fin>>m_weight[i](j, k);

        getline(fin, line);
    }
    
    fin.close();


    cout<<"m_bias:"<<endl<<m_bias[0]<<endl;

    cout<<"bias:"<<endl<<bias[num_weight-1]<<endl;
    // <^> initialization of RNN

    RNN RNNobject(num_layer, layer_size, num_memory, memory_layer);

    RNNobject.Set_Parameters(bias, weight, m_bias,  m_weight);


    MatrixXd *data=NULL;
    data = Load_Data("input_files/input.txt", data);
    int num_data = 10; //todo.....
    RNNobject.Predicting(num_data, data);

}

