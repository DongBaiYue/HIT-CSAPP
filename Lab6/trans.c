/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, x = 0, y = 0;
	int tmp, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	if (N == 32 || N == 67) {
		for (y = 0;y < M;y = y + 8) {
			for (x = 0;x < N;x = x + 8) {
				for (i = 0; i < 8 && x + i < N; i++) {
					for (j = 0; j < 8 && y + j < M; j++) {
						if (x + i != y + j) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
					if (x == y) {
						tmp = A[x + i][x + i];
						B[x + i][x + i] = tmp;
					}
				}
			}
		}
	}
	if (N == 64) {
		for (x = 0;x < N;x =x + 8) {
			for (y = 0;y < M;y = y + 8) {
				if (x == y) {
					for (i = 0;i < 4;i++) {
						for (j = 0;j < 4;j++) {
							if (x + i != y + j) {
								tmp = A[x + i][y + j];
								B[y + j][x + i] = tmp;
							}
						}
						tmp = A[x + i][x + i];
						B[x + i][x + i] = tmp;
					}
					for (;i < 8;i++) {
						for (j = 0;j < 4;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
					for (i = 4;i < 8;i++) {
						for (j = 4;j < 8;j++) {
							if (x + i != y + j) {
								tmp = A[x + i][y + j];
								B[y + j][x + i] = tmp;
							}
						}
						tmp = A[x + i][x + i];
						B[x + i][x + i] = tmp;
					}
					for (i = 0;i < 4;i++) {
						for (j = 4;j < 8;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
				}
				else {
					for (i = 0;i < 4;i++) {
						for (j = 0;j < 4;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
						for (;j < 8;j++) {
							tmp = A[x + i][y + j];
							B[y + j - 4][x + i + 4] = tmp;
						}
					}
					for (j = 0;j < 4;j++) {
						tmp = B[y + j][x + 4];
						tmp1 = B[y + j][x + 5];
						tmp2 = B[y + j][x + 6];
						tmp3 = B[y + j][x + 7];
						tmp4 = A[x + 4][y + j];
						tmp5 = A[x + 5][y + j];
						tmp6 = A[x + 6][y + j];
						tmp7 = A[x + 7][y + j];
						B[y + j][x + 4] = tmp4;
						B[y + j][x + 5] = tmp5;
						B[y + j][x + 6] = tmp6;
						B[y + j][x + 7] = tmp7;
						B[y + j + 4][x] = tmp;
						B[y + j + 4][x + 1] = tmp1;
						B[y + j + 4][x + 2] = tmp2;
						B[y + j + 4][x + 3] = tmp3;
					}
					for (i = 4;i < 8;i++) {
						for (j = 4;j < 8;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
				}
			}
		}
	} 
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

char trans1_desc[] = "transpose1";
void trans1(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x = 0, y = 0;                                                
    int b = 32 / (N / 8);                                                       
    while (y < M) {                                                             
        for (i = 0; i < b && x + i < N; i++) {                                  
                for (j = 0; j < b && y + j < M; j++) {                          
                        if(x+i != y+j){                                         
                                tmp = A[x + i][y + j];                          
                                B[y + j][x + i] = tmp;                          
                        }                                                       
                }                                                               
                if(x == y){                                                     
                        tmp = A[x+i][x+i];                                      
                        B[x+i][x+i] = tmp;                                      
                }                                                               
        }                                                                       
        x = x + b;                                                              
        if (x >= N) {                                                           
                x = 0;                                                          
                y = y + b;                                                      
        }                                                                       
}

}

char trans2_desc[] = "transpose2";
void trans2(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, x = 0, y = 0;
	int tmp, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	if (N == 32 || N == 67) {
		for (y = 0;y < M;y = y + 8){
			for (x = 0;x < N;x = x + 8) {
				for (i = 0; i < 8 && x + i < N; i++) {
					for (j = 0; j < 8 && y + j < M; j++) {
						if (x + i != y + j) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
					if (x == y) {
						tmp = A[x + i][x + i];
						B[x + i][x + i] = tmp;
					}
				}
			}
		}
	}
	if (N == 64) {
		for (x = 0;x < N;x =x + 8) {
			for (y = 0;y < M;y = y + 8) {
				if (x == y) {
					for (i = 0;i < 4;i++) {
						for (j = 0;j < 4;j++) {
							if (x + i != y + j) {
								tmp = A[x + i][y + j];
								B[y + j][x + i] = tmp;
							}
						}
						tmp = A[x + i][x + i];
						B[x + i][x + i] = tmp;
					}
					for (;i < 8;i++) {
						for (j = 0;j < 4;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
					for (i = 4;i < 8;i++) {
						for (j = 4;j < 8;j++) {
							if (x + i != y + j) {
								tmp = A[x + i][y + j];
								B[y + j][x + i] = tmp;
							}
						}
						tmp = A[x + i][x + i];
						B[x + i][x + i] = tmp;
					}
					for (i = 0;i < 4;i++) {
						for (j = 4;j < 8;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
				}
				else {
					for (i = 0;i < 4;i++) {
						for (j = 0;j < 4;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
						for (;j < 8;j++) {
							tmp = A[x + i][y + j];
							B[y + j - 4][x + i + 4] = tmp;
						}
					}
					for (j = 0;j < 4;j++) {
						tmp = B[y + j][x + 4];
						tmp1 = B[y + j][x + 5];
						tmp2 = B[y + j][x + 6];
						tmp3 = B[y + j][x + 7];
						tmp4 = A[x + 4][y + j];
						tmp5 = A[x + 5][y + j];
						tmp6 = A[x + 6][y + j];
						tmp7 = A[x + 7][y + j];
						B[y + j][x + 4] = tmp4;
						B[y + j][x + 5] = tmp5;
						B[y + j][x + 6] = tmp6;
						B[y + j][x + 7] = tmp7;
						B[y + j + 4][x] = tmp;
						B[y + j + 4][x + 1] = tmp1;
						B[y + j + 4][x + 2] = tmp2;
						B[y + j + 4][x + 3] = tmp3;
					}
					for (i = 4;i < 8;i++) {
						for (j = 4;j < 8;j++) {
							tmp = A[x + i][y + j];
							B[y + j][x + i] = tmp;
						}
					}
				}
			}
		}
	}
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 
    registerTransFunction(trans1, trans1_desc);
    registerTransFunction(trans2, trans2_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

