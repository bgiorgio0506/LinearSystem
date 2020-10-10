// linearSysResolution.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

//include libs
#include <iostream>
#include <math.h>

//N is the maximum number of unkowns possible NOTE: Tested with 3 unknowns
#define N 10
using namespace std;


class Matrix {
    public: 
        float mat[N][N + 1];
        int dim; 

        /* for dim equations there will be dim unknowns which will be stored in array 'res' */
        float res[N];

        Matrix() {
            cout << "Matrice inizialied waiting function to run" << endl;
            system("cls");
        }

        void LoadBidimensionalArray(int uniqueDimension)
        {
            dim = uniqueDimension;
            int i, j;
            for (i = 0; i < dim; i++)
            {
                for (j = 0; j < dim+1; j++)
                {
                    cout << "Inserire numero da caricare nella matrice nella posizione [" << i + 1 << ";" << j + 1 << "]" << endl;
                    cin >> mat[i][j];
                }
            }
        }

        int LoadDim()
            /* if no of equations are n then size of augmented matrix will be n*n+1. So here we are declaring 2d array 'mat' of size n+n+1 */
        {
            do
            {
                cout << "Inserisci dimensione: ";
                cin >> dim;
                if (dim >= N)
                {
                    cout << "Error dimension too big error" << endl;
                }
            } while (dim > N);

            return dim;
        }


        //display matrix
        void DisplayBidimensional()
        {
            int i, j;
            for (i = 0; i < dim; i++)
            {
                for (j = 0; j < dim+1; j++)
                {
                    cout << "\nEcco l'elemento caricato nella posizione [" << i + 1 << ":" << j + 1 << "]"
                        << ": " << mat[i][j] << endl;
                }
            }
            cout << "*********End Matrice Print**********" << endl;
        }

        //Swap Raw operation 
        void sawpRow() {
            int i, j, k;
            for (i = 0; i < dim; i++)
            {
                for (j = i + 1; j < dim; j++)
                {
                    if (abs(mat[i][i]) < abs(mat[j][i]))
                    {

                        for (k = 0; k < dim + 1; k++)
                        {
                            cout << "\nSwapping position[" << i << ";" << k << "] with position[" << j << ";" << k << "]\n";
                            /* swapping mat[i][k] and mat[j][k] */
                            mat[i][k] = mat[i][k] + mat[j][k];
                            mat[j][k] = mat[i][k] - mat[j][k];
                            mat[i][k] = mat[i][k] - mat[j][k];
                        }
                    }
                }
            }
        };

        void gaussianElimination() {
            /* performing Gaussian elimination */
            int i, j, k;
            for (i = 0; i < dim - 1; i++)
            {
                for (j = i + 1; j < dim; j++)
                {
                    float f = mat[j][i] / mat[i][i];
                    for (k = 0; k < dim + 1; k++)
                    {
                        mat[j][k] = mat[j][k] - f * mat[i][k];
                    }
                }
            }
        }

        void backSub() {
            int i, j;
            /* Backward substitution for discovering values of unknowns */
            for (i = dim - 1; i >= 0; i--)
            {
                res[i] = mat[i][dim];

                for (j = i + 1; j < dim; j++)
                {
                    if (i != j)
                    {
                        res[i] = res[i] - mat[i][j] * res[j];
                    }
                }
                res[i] = res[i] / mat[i][i];
            }
        }

        //Utility get dim
        int getBidimesionDimension()
        {
            return dim;
        }

        //Show linear sys solutions
        void showSystemSolutions() {
            int i;
            cout << "\nThe values of unknowns for the above equations=>\n";
            for (i = 0; i < dim; i++)
            {
                cout << res[i] << "\n";
            }

        }

        ~Matrix() {
            cout << "\nMatrix destroyed\n";
        }
};







int main()
{
    //int i, j, k, n;
    int dim;

    Matrix linearSystem;

    dim = linearSystem.LoadDim();
    linearSystem.LoadBidimensionalArray(dim);

    //Debug
    /*cout << "\n ===== Debug Output =====\n";
    linearSystem.DisplayBidimensional();
    cout << "\n ===== End Debug Output =====\n";*/


    linearSystem.sawpRow();
    linearSystem.gaussianElimination();

    //Debug
    /*cout << "\n ===== Debug Output =====\n";
    linearSystem.DisplayBidimensional();
    cout << "\n ===== End Debug Output =====\n";*/


    linearSystem.backSub();
    linearSystem.showSystemSolutions();
    system("PAUSE");

    return 0;
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug


