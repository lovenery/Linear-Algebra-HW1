#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream input("input.txt"); //Ū�����A
    ofstream output("output.txt"); //�g�J���A
    int row=0,column=0,leading=0,noZero=0,zeroCount=0; // row , column , leading one 's column , non-zero number , counting zero
    while(!input.eof()) //�����ɮ׵���
    {
        input >> row >> column ; //���orow,column
        int matrix[row][column]; //�إ߯x�}
        //���o�x�}���e��
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                input >> matrix[i][j];
            }
        }

        //Turn into Reduce Row Echelon Form
        for(int i=0; i<row; i++) // row=0,1,2,3,4....
        {
            //�p�G�S��1 �N�i�Ӹ�O�C������
            if(matrix[i][leading]==0)
            {
                //�̫�@�C��Ƴ�0,�N���ΦA���F
                zeroCount=0;
                for(int c=0; c<column; c++)
                {
                    if(matrix[row-1][c]==0)
                    {
                        zeroCount++;
                    }
                }
                if(zeroCount==column) //���X�j��s���o
                {
                    break;
                }

                //����
                for(int f=row-1; f>0; f--) //����C���O�@��,�q�̫�@�C�}�l��
                {
                    if(matrix[f][leading]!=0)
                    {
                        noZero=f;
                        break;
                    }
                }
                for(int c = 0; c<column; c++) //���N�洫
                {
                    swap(matrix[i][c],matrix[noZero][c]);
                }
            }

            //�s�yleading one
            int toOne=matrix[i][leading];
            for(int c = 0; c<column; c++) //��leading�o�@�C �P��leading�ۤv �N�|�X�{leading one(�L�Ҽ{����)
            {
                matrix[i][c]/=toOne;
            }

            //�����h
            for(int r = 0; r<row; r++)
            {
                if(r==i) //leading one�Ҧb���C(i)���ݮ��h
                {
                    continue;
                }
                int val=matrix[r][leading]; //�����ܼƥX��,�������b�U���|��
                for(int c = 0; c<column; c++) //��������leading one���C���W�n����C����
                {
                    matrix[r][c]-=matrix[i][c]*val;
                }
            }
            leading++; //�����@���̥~�����j��,���U�@�C�F,�ҥHleading one����m�V�k���@��
        }

        //��²����,��X����
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                cout<<setw(3)<<matrix[i][j];
            }
            cout<<endl;
        }
        cout<<endl;

        //�g�J��output.txt
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                if(j!=0)
                {
                    output << " ";
                }
                output << matrix[i][j];
            }
            output << endl;
        }
    }
    system("pause");
    return 0;
}
