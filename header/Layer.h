#ifndef __LAYER_H__
#define __LAYER_H__
#include "General.h"

class Layer
{
    public:
        //int type;
        
        //neutrons
        VectorXd *a; //include different time information
        VectorXd *z;

        int layer_size;

        virtual void activate(int){}
        virtual VectorXd D_z(int){}
        virtual void Forward(Layer*, MatrixXd *, MatrixXd *, int){}
        virtual void Print_Info(){}

        Layer(int layersize)
        {
            layer_size = layersize;
            a = new VectorXd [TIME_CONTAINER];
            z = new VectorXd [TIME_CONTAINER];
            for (int i=0; i<TIME_CONTAINER; i++)
            {
                a[i] = VectorXd::Constant(layer_size, 0.);
                z[i] = VectorXd::Constant(layer_size, 0.);
            }
        }

        int FindMaxIndex(int time)
        {
            double max_tmp = -100000.;
            int index=-1;
            for (int i=0;i<layer_size;i++)
            {
                if (a[time](i) > max_tmp)
                {
                    index = i;
                    max_tmp = a[time](i);
                }
            }
            return index;
        }

};


class Sigmoid_Layer : public Layer
{
    public:
        Sigmoid_Layer(int layersize) : Layer(layersize)
        {
        }
        
        double sigmoid(double x)
        {
            return 1./(1.+exp(-x));
        }

        virtual void activate(int time)
        {
            for (int i=0; i<layer_size;i++)
                a[time](i) = sigmoid(z[time](i));
        }
        
        virtual VectorXd D_z(int time)
        {
            VectorXd D_z(layer_size);
            for (int i=0;i<layer_size;i++)
                D_z(i) = sigmoid(z[time](i)) * (1. - sigmoid(z[time](i)));
            return D_z;
        }

        virtual void Forward(Layer* pre_layer, MatrixXd *weight, MatrixXd *bias, int time)
        {
            z[time] = (*weight)*pre_layer->a[time] + (*bias);
            activate(time);
        }
        virtual void Print_Info()
        {
            cout<<"Type: Sigmoid Layer"<<endl;
            cout<<"layer size:"<<layer_size<<endl;
            
        }

}; 


class Sigmoid_Layer_Memory : public Layer
{
    public:
        //memory
        VectorXd m_a;
        VectorXd m_z_init;
        VectorXd m_a_init;
        MatrixXd m_weight;
        MatrixXd m_bias;

        //gradient descent change
        MatrixXd D_m_weight;
        MatrixXd D_m_bias;
        VectorXd D_m_z_init;

        Sigmoid_Layer_Memory(int layersize) : Layer(layersize)
        {
            srand(time(NULL));
            m_a        = VectorXd::Constant(layer_size, 0.);
#ifdef TRAIN_MEMORY_INIT
            m_z_init   = 0.1 * VectorXd::Random(layer_size);
            m_a_init   = 0.1 * VectorXd::Random(layer_size);

#else
            m_z_init   = VectorXd::Constant(layer_size, 0.);
            m_a_init   = VectorXd::Constant(layer_size, 0.);
#endif 

            m_weight   = MatrixXd::Random  (layer_size, layer_size);
            m_bias     = MatrixXd::Constant(layer_size, 1,  0.);

            D_m_weight = MatrixXd::Constant(layer_size, layer_size, 0.);
            D_m_bias   = MatrixXd::Constant(layer_size, 1,  0.);

            D_m_z_init = VectorXd::Constant(layer_size, 0.);
        }
        
        double sigmoid(double x)
        {
            return 1./(1.+exp(-x));
        }
        
        virtual void activate(int time)
        {
            for (int i=0; i<layer_size;i++)
                a[time](i) = sigmoid(z[time](i));
        }

        virtual VectorXd D_z(int time)
        {
            VectorXd D_z(layer_size);
            for (int i=0;i<layer_size;i++)
            {
                if (time >= 0)
                    D_z(i) = sigmoid(z[time](i)) * (1. - sigmoid(z[time](i)));
                else if (time == -1)
                    D_z(i) = sigmoid(m_z_init(i)) * (1. - sigmoid(m_z_init(i)));
                else
                {
                    cout<<"ERROR: no time <= -2..."<<endl;
                    exit(0);
                }
            }
            return D_z;
        }

        virtual void Forward(Layer* pre_layer, MatrixXd *weight, MatrixXd *bias, int time)
        {
            z[time] = (*weight)*pre_layer->a[time] + (*bias);
            //memory
            if ( time == 0)
                z[time] += m_weight*m_a_init + m_bias;
            else
                z[time] += m_weight*m_a + m_bias;

            activate(time);
            m_a = a[time];
        }
        
        
        void Memory_BackPropagation(VectorXd *delta, int time)
        {
            VectorXd delta_tmp = (*delta);
            *delta = (m_weight.transpose() * delta_tmp).cwiseProduct(D_z(time));

            if (time>=0)
                D_m_weight += delta_tmp * a[time].transpose();
            else if (time == -1)
            {
                D_m_weight += delta_tmp * m_a_init.transpose();
#ifdef TRAIN_MEMORY_INIT
                D_m_z_init += *delta;
#endif
            }
            else
            {
                cout<<"in Memory_BackPropagation: time <=-2! wrong!"<<endl;
                exit(0);
            }

            
            D_m_bias   += *delta;
            
        }



        virtual void Print_Info()
        {
            cout<<"Type: Sigmoid Layer with Memory"<<endl;
            cout<<"layer size:"<<layer_size<<endl;
            
        }

        void reset_memory()
        {
#ifdef TRAIN_MEMORY_INIT
            for (int i=0; i<layer_size; i++)
            {
                m_a(i) = sigmoid(m_z_init(i));
                m_a_init = m_a;
            }

#else
            for (int i=0; i<layer_size; i++)
                m_a(i) = 0;
#endif
        }

};

#endif //__LAYER_H__
