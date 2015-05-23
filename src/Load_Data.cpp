#include "General.h"

MatrixXd* Load_Data(const char* filename, MatrixXd *data, int *ptr_num_data)
{
    ifstream fin(filename);
    FILE *File;
    File = fopen(filename, "r");
    char str[2000];
    string s;
    int max_n = 2000;

    fgets(str, max_n, File);  getline(fin, s);
    fgets(str, max_n, File);  getline(fin, s);


    sscanf(str, "%d", ptr_num_data);
    (*ptr_num_data) = min (*ptr_num_data, MAX_NUM_DATA);

    int num_data = *ptr_num_data;
    
    data = new MatrixXd [num_data];

    int row;
    int col;

    for (int i=0; i<num_data; i++)
    {
        cout<<"Load Data: "<<i<<" / "<<num_data<<endl;
        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        sscanf(str, "%d", &row); 

        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        sscanf(str, "%d", &col); 
        
        fgets(str, max_n, File); getline(fin, s);

        data[i] = MatrixXd::Constant(row, col, 0);

        for (int j=0; j<row; j++)
        {
            fgets(str, max_n, File);
            for (int k=0; k<col; k++)
                fin>>data[i](j,k);
        }
        getline(fin, s);

    }

    fclose(File);
    fin.close();

    return data;
}






