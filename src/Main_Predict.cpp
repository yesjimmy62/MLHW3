#include "General.h"

int main(int argc, char* argv[])
{
    char dir_path[100] = "output_files/";
    char dir_path2[100];
    char header[100];
    char bline[5]="_";

    // user setting
    //strcpy(header, "1_"); 
    strcpy(header, argv[1]);
    strcat(header, bline);
    cout<<"header:"<<header<<endl;


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
    
    /*
    cout<<"number of layers:"<<num_layer<<endl;
    cout<<"layer_size:"<<endl;
    for (int i=0; i<num_layer; i++)
        cout<<layer_size[i]<<"  ";
    cout<<endl;
    cout<<"number of memory:"<<num_memory<<endl;
    */

    // <^> (b) read the NormalParameters.txt file
    strcpy(dir_path2, dir_path);
    strcat(dir_path2, header);
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
    // <^> (c) read the MemoryParameters.txt file
    strcpy(dir_path2, dir_path);
    strcat(dir_path2, header);
    fin.open(strcat(dir_path2, "MemoryParameters.txt"));

    MatrixXd *m_weight;
    MatrixXd *m_bias;
    MatrixXd *m_z_init;
    m_weight = new MatrixXd [num_memory];
    m_bias = new MatrixXd [num_memory];
    m_z_init = new MatrixXd [num_memory];
    for (int i=0; i<num_memory; i++)
    {
        int index = memory_layer[i];
        m_z_init[i] = MatrixXd::Constant(layer_size[index], 1, 0);
        m_weight[i] = MatrixXd::Constant(layer_size[index], layer_size[index], 0);
        m_bias[i] = MatrixXd::Constant(layer_size[index], 1, 0);
    }

    for (int i=0; i<num_memory; i++)
    {
        int index = memory_layer[i];

        // <^> m_z_init
        getline(fin, line); //m_z_init:
        for (int j=0; j< layer_size[index]; j++)
            fin>>m_z_init[i](j, 0);


        // <^> bias
        getline(fin, line);
        getline(fin, line); //bias:
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


    // <^> initialization of RNN, set its  weight and bias

    RNN RNNobject(num_layer, layer_size, num_memory, memory_layer);

    RNNobject.Set_Parameters(bias, weight, m_z_init,  m_bias,  m_weight);


    // <^> load testing data
    MatrixXd *data=NULL;
    MatrixXd *options=NULL;
    int num_data=0, num_data2=0;
    int Blank_Pos[100000]; //QQ........

    //Hw3 
    data = Load_Data_Hw3("input_files/TEST_INPUT.TXT", data, Blank_Pos, &num_data);
    options = Load_Data("input_files/TEST_INPUT_ANS_300C.TXT", options, &num_data2);

    if (num_data != num_data2 && options != NULL)
    {
        cout<<"the number of data is not equal to the number of options"<<endl;
        exit(0);
    }

    RNNobject.Predicting_Hw3Data(num_data, data, Blank_Pos, options);

    return 0;

}

