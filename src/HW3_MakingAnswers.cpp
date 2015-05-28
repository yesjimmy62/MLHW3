#include "General.h"

MatrixXd* HW3_MakingAnswers(MatrixXd* data, MatrixXd* real_answer, int num_data)
{

    real_answer = new MatrixXd [num_data];



    for (int i=0; i<num_data; i++)
    {
        real_answer[i] = MatrixXd::Constant(data[i].rows()-1, data[i].cols(), 0.);
        MatrixXd onehalf = MatrixXd::Constant(1, data[i].cols(), 0.5);
        for (int row=0; row<data[i].rows()-1; row++)
            real_answer[i].row(row) = onehalf + 1./(DATA_RANGE*2.) * data[i].row(row+1); //make sure its range is 0~1

#ifdef  ANS_TRUNCATE
        for (int row=0; row<data[i].rows()-1; row++)
            for (int col=0; col<data[i].cols(); col++)
            {
                if (real_answer[i](row,col) > 1.)
                    real_answer[i](row,col) = 0.99999;
                else if (real_answer[i](row,col) < 0.)
                    real_answer[i](row,col) = 0.00001;
            }
#endif 

    }


    return real_answer;
}
