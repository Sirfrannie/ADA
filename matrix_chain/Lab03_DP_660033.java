public class Lab03_DP_660033
{
    public static void main(String args[]){
        sub1();
    }

    static int minOperationsMatrixChain(int p[], int n){
        int cost[][] = new int[n][n]; // row 0 and col 0 will not be used
        int i, j, k, L, numOps;

        for (i=0; i<n; ++i){
            cost[i][i] = 0; // cost is zero when multiplyin one matrix
        }

        for (L=2; L<n; ++L){
            for (i=1; i<n-L+1; ++i){
                j = i+L-1;
                cost[i][j] = Integer.MAX_VALUE;
                for (k=i; k<=j-1; ++k){
                    // C[i,k] + C[k+1, j] + Pi-1 Pk Pj
                    numOps = cost[i][k] + cost[k+1][j]+p[i-1]*p[k]*p[j];
                    if ( numOps < cost[i][j]){
                        cost[i][j] = numOps;
                    }
                }
            }
        }

        System.out.println("cache content = ");
        for (int r=1; r<n; ++r){
            for (int c=1; c<n; ++c){
                System.out.print(cost[r][c] + "\t");
            }
            System.out.println();
        }

        return cost[1][n-1];
    }

    static void sub1(){
        int P[] = {4, 10, 3, 12, 20};
        System.out.println(minOperationsMatrixChain(P, P.length));
    }


}
