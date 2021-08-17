/*Complete the function below*/
void multiply(int A[][100], int B[][100], int C[][100], int N)
{
    for (auto i = 0; i != N; ++i) {
        for (auto k = 0; k != N; ++k) {
            C[i][k] = 0;
            for (auto j = 0; j != N; ++j) C[i][k] += A[i][j] * B[j][k];
        }
    }
}
