#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream input("input.txt"); //讀取狀態
    ofstream output("output.txt"); //寫入狀態
    int row=0,column=0,leading=0,noZero=0,zeroCount=0; // row , column , leading one 's column , non-zero number , counting zero
    while(!input.eof()) //直到檔案結尾
    {
        input >> row >> column ; //取得row,column
        int matrix[row][column]; //建立矩陣
        //取得矩陣內容物
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
            //如果沒有1 就進來跟別列換換看
            if(matrix[i][leading]==0)
            {
                //最後一列整排都0,就不用再換了
                zeroCount=0;
                for(int c=0; c<column; c++)
                {
                    if(matrix[row-1][c]==0)
                    {
                        zeroCount++;
                    }
                }
                if(zeroCount==column) //跳出迴圈存檔囉
                {
                    break;
                }

                //換換
                for(int f=row-1; f>0; f--) //找哪列不是一的,從最後一列開始找
                {
                    if(matrix[f][leading]!=0)
                    {
                        noZero=f;
                        break;
                    }
                }
                for(int c = 0; c<column; c++) //找到就交換
                {
                    swap(matrix[i][c],matrix[noZero][c]);
                }
            }

            //製造leading one
            int toOne=matrix[i][leading];
            for(int c = 0; c<column; c++) //把leading這一列 同除leading自己 就會出現leading one(無考慮分數)
            {
                matrix[i][c]/=toOne;
            }

            //做消去
            for(int r = 0; r<row; r++)
            {
                if(r==i) //leading one所在之列(i)不需消去
                {
                    continue;
                }
                int val=matrix[r][leading]; //不拉變數出來,直接乘在下面會錯
                for(int c = 0; c<column; c++) //元素扣掉leading one那列乘上要減的那列倍數
                {
                    matrix[r][c]-=matrix[i][c]*val;
                }
            }
            leading++; //結束一次最外面的迴圈,換下一列了,所以leading one的位置向右移一個
        }

        //化簡完畢,輸出測試
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                cout<<setw(3)<<matrix[i][j];
            }
            cout<<endl;
        }
        cout<<endl;

        //寫入至output.txt
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
