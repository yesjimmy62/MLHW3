#include "General.h"

MatrixXd* Load_Data(const char* filename, MatrixXd *data)
{
    ifstream fin(filename);
    FILE *File;
    File = fopen(filename, "r");
    char str[2000];
    string s;
    int max_n = 2000;

    fgets(str, max_n, File);  getline(fin, s);
    fgets(str, max_n, File);  getline(fin, s);

    cout<<"str:"<<str<<endl;

    int num_data;
    sscanf(str, "%d", &num_data);

    cout<<"num_data:"<<num_data<<endl;
    
    data = new MatrixXd [num_data];

    int row;
    int col;

    for (int i=0; i<num_data; i++)
    {
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

        cout<<endl<<"data->rows():"<<data[i].rows()<<endl;

        cout<<"data="<<endl<<data[i]<<endl;
    }

    fclose(File);
    fin.close();

    return data;
}






