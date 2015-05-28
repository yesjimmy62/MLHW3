#include "General.h"



class RNN
{
    public:
        int num_layer;
        int *layer_size;
        int num_weight; //not include memory
        int num_memory;
        int *memory_layer;
        int *memory_layer_index;
        int last_layer;
        
        //parameters
        MatrixXd *weight;
        MatrixXd *bias;

        //back propagation
        VectorXd *delta;

        //gradient descent
        MatrixXd *D_weight;
        MatrixXd *D_bias;

        Layer **layers;
        

        RNN(int numlayer, int layersize[], int nummemory, int memorylayer[])
        {
            num_layer = numlayer;
            num_weight = num_layer - 1;
            last_layer = num_weight;
            layer_size = new int [num_layer];
            for (int i=0; i<num_layer;i++)
                layer_size[i] = layersize[i];

            num_memory = nummemory;
            memory_layer = new int [num_layer];
            for (int i=0; i<num_layer; i++)
                memory_layer[i] = -1;
            for (int i=0; i<num_memory; i++)
                memory_layer[memorylayer[i]] = i; //mark the memory layer and store its index
            memory_layer_index = new int [num_memory];
            for (int i=0; i<num_memory; i++)
                memory_layer_index[i] = memorylayer[i];

            //initialize weight and bias
            weight = new MatrixXd [num_weight];
            bias = new MatrixXd [num_weight];
            srand(time(NULL));
            for (int i=0; i<num_weight; i++)
            {
                weight[i] = MatrixXd::Random(layer_size[i+1], layer_size[i]);
                bias[i] = MatrixXd::Random(layer_size[i+1], 1);
            }

            //initialize d_weight and d_bias
            D_weight = new MatrixXd [num_weight];
            D_bias = new MatrixXd [num_weight];
            for (int i=0; i<num_weight; i++)
            {
                D_weight[i] = MatrixXd::Constant(layer_size[i+1], layer_size[i], 0.);
                D_bias[i]   = MatrixXd::Constant(layer_size[i+1], 1, 0.);
            }



            //cout<<"weight[1]:"<<endl<<weight[1]<<endl;
            
            //initialize layers
            layers = new Layer* [num_layer];
            for (int i=0; i<num_layer; i++)
            {
                if (memory_layer[i] < 0)
                    layers[i] = new Sigmoid_Layer(layer_size[i]);
                else
                    layers[i] = new Sigmoid_Layer_Memory(layer_size[i]);
            }

            //initialize delta
            delta = new VectorXd [num_layer];
            for (int i=0; i<num_layer; i++)
                delta[i] = VectorXd::Constant(layer_size[i], 0.);
        }

        void Print_LayerInfo()
        {
            for (int i=0; i<num_layer; i++)
                layers[i]->Print_Info();
        }
        void ForwardPropagation(VectorXd train_input, int time)
        {
            //cout<<endl<<"train_input:"<<endl<<train_input<<endl;
            //cout<<"Time:"<<time<<endl;
            layers[0]->a[time] = train_input;
            //cout<<endl<<"layer[0]->a:"<<endl<<layers[0]->a[time]<<endl;

            for (int i=1; i<num_layer; i++)
            {
                layers[i]->Forward(layers[i-1], &weight[i-1], &bias[i-1], time);
                //cout<<endl<<"layer["<<i<<"]->a:"<<endl<<layers[i]->a[time]<<endl;
            }
        }

        void BackPropagation(VectorXd real_answer, int time)
        {
            //cout<<"BackPropagation..."<<endl;
            //cout<<"layer..:"<<layers[last_layer]->a[time]<<endl;
            //cout<<"real_answer:"<<real_answer<<endl;
#ifdef CROSS_ENTROPY
            delta[last_layer] = layers[last_layer]->a[time] - real_answer;
#endif

#ifdef SQUARE_ERROR
            delta[last_layer] = 2.*(layers[last_layer]->a[time]-real_answer).cwiseProduct(layers[last_layer]->D_z(time));
#endif

            int current_time = time;

            cout<<endl<<"time:"<<time<<endl;
            cout<<"delta[2]:"<<endl<<delta[last_layer]<<endl;
            for (int i=num_weight-1; i>=1; i--)
            {
                delta[i] = (weight[i].transpose() * delta[i+1]).cwiseProduct(layers[i]->D_z(current_time));
                cout<<"i:"<<i<<endl;
                cout<<"deta[i]"<<delta[i]<<endl;
            }
            
            for (int i=0; i<num_weight; i++)
            {
                D_weight[i] += delta[i+1] * layers[i]->a[current_time].transpose();
                D_bias[i]   += delta[i+1];
                cout<<"i:"<<i<<endl;
                cout<<"current time:"<<current_time<<endl;
                cout<<"a[current_time]:"<<endl<<layers[i]->a[current_time]<<endl;
                cout<<"D_weight[i]:"<<endl<<D_weight[i]<<endl;
            }

            current_time --;
            //assume... only 1 memory layer
            int mem = memory_layer_index[0];

            //back propagation through time
            while (current_time >= 0 && current_time >= time-MAX_BPTT_LAYERS)
            {
                ((Sigmoid_Layer_Memory*)layers[mem])->Memory_BackPropagation(&delta[mem], current_time);
                for (int i=mem-1; i>=1; i--)
                    delta[i] = (weight[i].transpose() * delta[i+1]).cwiseProduct(layers[i]->D_z(current_time));
                
                for (int i=0; i<mem; i++)
                {
                    D_weight[i] += delta[i+1] * layers[i]->a[current_time].transpose();
                    D_bias[i]   += delta[i+1];
                    cout<<endl<<"back:"<<endl;
                    cout<<"i:"<<i<<endl;
                    cout<<"current time:"<<current_time<<endl;
                    cout<<"a[current_time]:"<<endl<<layers[i]->a[current_time]<<endl;
                    cout<<"D_weight[i]:"<<endl<<D_weight[i]<<endl;
                }
                current_time --;
            }//current_time >= 0

            if (current_time == -1)
            {
                ((Sigmoid_Layer_Memory*)layers[mem])->Memory_BackPropagation(&delta[mem], current_time);
            }

        }//BackPropagation()


        void GradientDescent(double learning_rate)
        {
            cout<<endl<<"Gradient Descent:"<<endl;
            for (int i=0; i<num_weight; i++)
            {
                weight[i] -= learning_rate * D_weight[i];
                cout<<"D_weight:"<<endl<<D_weight[i]<<endl;
                bias[i]   -= learning_rate * D_bias[i];
            }
            int garbage;
            cout<<"Pause:"<<endl;
            cin>>garbage;

            // <^> memory part

            for (int i=0; i<num_memory; i++)
            {
                //layers[memory_layer_index[i]]->Memory_GradientDescent(learning_rate);
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_weight -= learning_rate *((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->D_m_weight;
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_bias   -= learning_rate * ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->D_m_bias;
#ifdef TRAIN_MEMORY_INIT
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_z_init   -= learning_rate * ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->D_m_z_init;
#endif
            }
        }

        void Reset_D_Parameter()
        {
            for (int i=0; i<num_weight; i++)
            {
                D_weight[i].setZero();
                D_bias[i]  .setZero();
            }
            for (int i=0; i<num_memory; i++)
            {
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->D_m_weight.setZero();
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->D_m_bias.setZero();
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->D_m_z_init.setZero();
            }
        }


        void CostFunction(int num_output, MatrixXd *real_answer)
        {
            double tmp0=0., tmp1=0.;
            double Cost=0;

            double Cost_square = 0;
            double square_tmp = 0;
            int num_features = real_answer->cols();
            for (int t=0; t<num_output; t++)
            {
                tmp0 = 0.;
                tmp1 = 0.;
                for (int i=0; i<num_features; i++)
                {

                    //cout<<"HERE B:"<<endl<<(*real_answer)<<endl;
                    //cout<<"HERE B:"<<endl<<(*real_answer)(1,1)<<endl;
                    //cout<<"HERE B a:"<<endl<<layers[last_layer]->a[t]<<endl;

                    tmp0 += log(1E-5 + layers[last_layer]->a[t](i)) * (*real_answer)(t, i);
                    tmp1 += log(1.00001 - layers[last_layer]->a[t](i)) * (1.-(*real_answer)(t, i));
                    square_tmp = pow(layers[last_layer]->a[t](i) - (*real_answer)(t,i), 2.);
                }
                cout<<"cost of "<<t<<"-th output:"<< -tmp0-tmp1<<"/"<<square_tmp<<endl;
                
                Cost += (-tmp0 - tmp1);
                Cost_square += square_tmp;
            }

            cout<<"Total Cost:"<<Cost<<endl;
            cout<<"Total Square Cost:"<<Cost_square<<endl;
            cout<<"Average Cost:"<<Cost/num_output<<endl;
            cout<<"Average Square Cost:"<<Cost_square/num_output<<endl<<endl;

        }
                






        void Memory_Reset()
        {
            for (int i=0; i<num_memory; i++)
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->reset_memory();
        } 


        void Training(int num_data, MatrixXd *data, MatrixXd *real_answer, int num_epoch, double learning_rate)
        {

            int num_member;
            int size_output = 10;
            int *output;
            output = new int [size_output];

            int data_dump = num_data / NUM_DATA_MINI_DUMP;

            // <^> checking parameters
            if (layer_size[last_layer] != real_answer[0].cols())
            {
                cout<<"Wrong parameter: last layer size should match the number of output"<<endl;
                exit(0);
            }

            for( int epoch=0; epoch<num_epoch; epoch++)
            {

                for (int i=0; i<num_data; i++)
                {
                    //There may be some difference between data[i].rows() and real_answer[i].rows()
                    //For example, we may produce real_answer by getting next row of data
                    //Then, real_answer[i].rows() = data[i].rows() - 1

                    //num_member = data[i].rows();
                    num_member = real_answer[i].rows();
                    
                    if (num_member > size_output)
                    {
                        delete []output;
                        output = new int [num_member+5];
                    }
 
                    // <^> reset the memory
                    Memory_Reset();
 
                    // <^> reset the D_parameter (changes)
                    Reset_D_Parameter();
 
                    // <^> forward propagation
                    for (int j=0; j<num_member; j++)
                    {
                        ForwardPropagation(data[i].row(j), j);
 
                    }
 
                    //CostFunction(num_member, &real_answer[i]);
 
                    // <^> back propagation
                    for (int j=0; j<num_member; j++)
                    {
                        BackPropagation(real_answer[i].row(j), j);
                    }
 
                    // <^> gradient descent
                    GradientDescent(learning_rate);

                    if (i % data_dump == 0)
                       Output_Parameters(double(i)/num_data+double(epoch)); 
 
 
                } //for (int i=0; i<num_data; i++)
                
                if (epoch % NUM_DATA_DUMP == 0)
                    Output_Parameters(double(1.+epoch));
            } //for (int epoch=0; epoch<num_epoch; epoch++)


            Output_Parameters(-1);
        } //void Training(...)

        void Predicting_Hw3Data(int num_data, MatrixXd *data, int *Blank_Pos, MatrixXd *options)
        {


            if (data[0].cols() != options[0].cols())
            {
                cout<<"the dimension of vector is different in data and options."<<endl;
                exit(0);
            }

            int num_member;

            ofstream fout("output_files/HW3_Prediction.csv");
            fout<<"Id,answer"<<endl;

            for (int i=0; i<num_data; i++)
            {
                num_member = data[i].rows();

                // <^> reset the memory
                Memory_Reset();
 
                // <^> forward propagation
                for (int j=0; j<Blank_Pos[i]; j++)
                {
                    ForwardPropagation(data[i].row(j), j);
 
                }
 
                //CostFunction(num_member, &real_answer[i]);

                Output_Predict_Hw3Data(&fout, Blank_Pos[i], options[i], i+1);
 
 
            } //for (int i=0; i<num_data; i++)

            fout.close();

        } //void Predicting(...)

        void Output_Predict_Hw3Data(ofstream *fout, int Blank_Pos, MatrixXd options, int ID)
        {
            int output_num = layers[last_layer]->layer_size;

            int num_options = 5;

            int index;
#ifdef MAX_INNER_PRODUCT
            MatrixXd ones = MatrixXd::Constant(layer_size[last_layer] ,1 , 1.);
            MatrixXd inner_product = options * (2*layers[last_layer]->a[Blank_Pos-1]-ones);


            double max_tmp=-100000.;
            for (int i=0; i< num_options; i++)
            {
                if (inner_product(i,0) > max_tmp)
                {
                    max_tmp = inner_product(i,0);
                    index = i;
                }
            }
#endif //MAX_INNER_PRODUCT

#ifdef MIN_DISTANCE
            double distance_tmp = 0.;
            double min_distance = 9999999;
            for (int i=0; i<num_options; i++)
            {
                distance_tmp = 0.;
                for (int j=0; j<layer_size[last_layer]; j++)
                {
#ifdef DATA_RANGE
                    distance_tmp += pow(
                            DATA_RANGE*(2.*layers[last_layer]->a[Blank_Pos-1](j)-1.) - options(i,j)
                             , 2.);
#else //DATA_RANGE
                    distance_tmp += pow(
                            (2.*layers[last_layer]->a[Blank_Pos-1](j)-1.) - options(i,j)
                             , 2.);

#endif //DATA_RANGE
                }

                if (distance_tmp < min_distance)
                {
                    min_distance = distance_tmp;
                    index = i;
                }
            }
                

#endif //MIN_DISTANCE

#ifdef MIN_COS_DISTANCE
            MatrixXd ones = MatrixXd::Constant(layer_size[last_layer] ,1 , 1.);
            MatrixXd inner_product = options * (2*layers[last_layer]->a[Blank_Pos-1]-ones);

            double option_length[5]={0};
            for (int i=0; i<num_options; i++)
            {
                for (int j=0; j < layer_size[last_layer]; j++)
                {
                    option_length[i] += pow(options(i, j), 2.); 
                }
                option_length[i] = sqrt(option_length[i]);
            }

            double max_tmp=-100000.;
            for (int i=0; i< num_options; i++)
            {
                if (inner_product(i,0)/option_length[i] > max_tmp)
                {
                    max_tmp = inner_product(i,0)/option_length[i];
                    index = i;
                }
            }
#endif //MIN_COS_DISTANCE

#ifdef MIN_SQUARE_ERROR
            double error_tmp;
            double min_error =999999.;
            for (int i=0; i<num_options; i++)
            {
                error_tmp = 0.;
                for (int j=0; j<layer_size[last_layer]; j++)
                    error_tmp += pow(layers[last_layer]->a[Blank_Pos-1](j) - options(i,j), 2.);

                if (error_tmp < min_error)
                {
                    min_error = error_tmp;
                    index = i;
                }
            }



#endif //MIN_SQUARE_ERROR

            *fout<<ID<<",";
            switch(index)
            {
                case 0:
                    *fout<<"a"<<endl;
                    break;
                case 1:
                    *fout<<"b"<<endl;
                    break;
                case 2:
                    *fout<<"c"<<endl;
                    break;
                case 3:
                    *fout<<"d"<<endl;
                    break;
                case 4:
                    *fout<<"e"<<endl;
                    break;
            }


        }



        void Predicting_ToyData(int num_data, MatrixXd *data)
        {

            int num_member;
            int size_output = 10;
            int *output;
            output = new int [size_output];

            // <^> output prediction file
            ofstream fout("output_files/Prediction.txt");

            // <^> checking parameters
            // ... todo ...


            for (int i=0; i<num_data; i++)
            {
                num_member = data[i].rows();
                if (num_member > size_output)
                {
                    delete []output;
                    output = new int [num_member+5];
                }
 
                // <^> reset the memory
                Memory_Reset();
 
                // <^> forward propagation
                for (int j=0; j<num_member; j++)
                {
                    ForwardPropagation(data[i].row(j), j);
 
                }
 
                //CostFunction(num_member, &real_answer[i]);

                Output_Predict_ToyData(&fout, num_member);
 
 
 
            } //for (int i=0; i<num_data; i++)

            fout.close();

        } //void Predicting(...)

        void Output_Predict_ToyData(ofstream *fout, int total_time)
        {
            int max_index;
            int output_num = layers[last_layer]->layer_size;

            *fout<<"-----"<<endl;
            for (int t=0; t<total_time; t++)
            {
                max_index = layers[last_layer]->FindMaxIndex(t);
                for (int i=0; i< output_num; i++)
                {
                    if (i == max_index && layers[last_layer]->a[t](max_index,0)>0.5)
                        *fout<<"1  ";
                    else
                        *fout<<"0  ";
                }
                *fout<<endl;
            }
        }





        void Output_Parameters(double num)
        {
            char dir_path[40] ="output_files/";
            char str_epoch[15];
            sprintf(str_epoch, "%.1f_", num); 
            char filename0[100], filename1[100], filename2[100];

            // <^> output basic setting
            strcpy(filename0, "BasicSetting.txt");
            ofstream fout(strcat(dir_path, filename0));
            fout<<"number of layers:"<<endl;
            fout<<num_layer<<endl;
            fout<<"layer size:"<<endl;
            for (int i=0; i<num_layer; i++)
                fout<<layer_size[i]<<"  ";
            fout<<endl;
            fout<<"number of memory:"<<endl;
            fout<<num_memory<<endl;
            fout<<"memory layer:"<<endl;
            for (int i=0; i<num_memory; i++)
                fout<<memory_layer_index[i];
            fout.close();

            // <^> output normal bias and weight
            char dir_path1[100] ="output_files/";
            strcpy(filename1, str_epoch);
            strcat(filename1, "NormalParameters.txt");
            fout.open(strcat(dir_path1, filename1));
            for (int i=0; i<num_weight; i++)
            {
                fout<<"bias:"<<endl;
                fout<<bias[i].transpose()<<endl;
                fout<<"weight:"<<endl;
                fout<<weight[i]<<endl;
            }
            fout.close();

            // <^> output memory bias and weight
            char dir_path2[100] ="output_files/";
            strcpy(filename2, str_epoch);
            strcat(filename2, "MemoryParameters.txt");
            fout.open(strcat(dir_path2, filename2));
            for (int i=0; i<num_memory; i++)
            {
                fout<<"m_z_init:"<<endl;
                fout<<((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_z_init.transpose();
                fout<<endl<<"bias:"<<endl;
                fout<<((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_bias.transpose();
                fout<<endl<<"weight:"<<endl;
                fout<<((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_weight<<endl;
            }
            fout.close();

        }

        void Set_Parameters(MatrixXd *bias_load, MatrixXd *weight_load, MatrixXd *m_z_init_load,  MatrixXd *m_bias_load, MatrixXd *m_weight_load)
        {
            for (int i=0; i<num_weight; i++)
            {
                bias[i] = bias_load[i];
                weight[i] = weight_load[i];
            }

            for (int i=0; i<num_memory; i++)
            {
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_z_init = m_z_init_load[i];
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_bias = m_bias_load[i];
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->m_weight = m_weight_load[i];
                ((Sigmoid_Layer_Memory*)layers[memory_layer_index[i]])->reset_memory();
            }

            cout<<"In Set_Parameters:"<<endl<<bias[num_weight-1]<<endl;
        }



};
