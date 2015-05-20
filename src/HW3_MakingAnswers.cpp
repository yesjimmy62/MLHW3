#include "General.h"

MatrixXd* HW3_MakingAnswers(MatrixXd* data, MatrixXd* real_answer, int num_data)
{

    real_answer = new MatrixXd [num_data];

    for (int i=0; i<num_data; i++)
    {
        real_answer[i] = MatrixXd::Constant(data[i].rows()-1, data[i].cols(), 0.);
        MatrixXd onehalf = MatrixXd::Constant(1, data[i].cols(), 0.5);
        for (int row=0; row<data[i].rows()-1; row++)
            real_answer[i].row(row) = onehalf + 0.5 * data[i].row(row+1); //make sure its range is 0~1
    }


    return real_answer;
}
