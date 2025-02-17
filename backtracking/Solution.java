import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.LinkedList;
import java.lang.StringBuilder;

public class Solution
{
    void permute1(int arr[], int k){
        List<List<Integer>> ans = new ArrayList<>();

        naive_permute(arr, k, 0, 0, "", ans); 
        for (List<Integer> subset : ans){
            System.out.println(subset);
        }
    } 
    void permute2(int arr[], int k){
        List<List<Integer>> ans = new ArrayList<>();

        permute(arr, k, 0, 0, "", ans);
        for (List<Integer> subset : ans){
            System.out.println(subset);
        }
    }

    void naive_permute(int arr[], int k, int i, int subsum, String state, List<List<Integer>> set){
        if (k == 0)
            return;
        if (subsum == k){
            List<Integer> one_case = new ArrayList<>();
            String charArr[] = state.split(",");
            for (int j=0; j<charArr.length; ++j){
                if (!charArr[j].equals("")){
                    one_case.add(Integer.parseInt(charArr[j]));
                }
            }
            if (!set.contains(one_case))
                set.add(one_case);
            /* A */
        }

        if ( i == arr.length){
            return;
        }
        naive_permute(arr, k, i+1, subsum + arr[i], state+","+arr[i], set);
        naive_permute(arr, k, i+1, subsum, state+",", set);
    }

    void permute(int arr[], int k, int i, int subsum, String state, List<List<Integer>> set){
        if (k == 0)
            return;
        if (subsum > k) /* B */
            return;
        if (subsum == k){
            List<Integer> one_case = new ArrayList<>();
            String charArr[] = state.split(",");
            for (int j=0; j<charArr.length; ++j){
                if (!charArr[j].equals("")){
                    one_case.add(Integer.parseInt(charArr[j]));
                }
            }
            if (!set.contains(one_case))
                set.add(one_case);
            /* A */
            return;
        }

        if ( i == arr.length){
            return;
        }
        permute(arr, k, i+1, subsum + arr[i], state+","+arr[i], set);
        permute(arr, k, i+1, subsum, state+",", set);
    }
    void subsetSum(int arr[], int k){
        Set<List<Integer>> set = new HashSet<>();
        subsetEqualsTarget(arr, k, 0, 0, new LinkedList<Integer>(), set);
        for (List<Integer> one_case : set){
            System.out.println(one_case);
        }
        System.out.println("bye");
    } 
    void subsetEqualsTarget(int arr[], int k, int i, int sum, LinkedList<Integer> curState, Set<List<Integer>> set){
        if (k == 0)
            return;
        if (sum > k)
            return;
        if (sum == k){
            set.add(new LinkedList<>(curState));
            return;
        }
        if (i == arr.length)
            return;
        curState.add(arr[i]);
        subsetEqualsTarget(arr, k, i+1, sum + arr[i], curState, set);
        curState.removeLast();
        subsetEqualsTarget(arr, k, i+1, sum, curState, set);
    }
    /* --------------------------------------------------------------------------------- */

    /* given maze as N*N matrix 
       0 -> path is blocked you can't move to it
       1 -> path is available you can move to it

       Note: In a path, no cell can be visited more than one time.
        If the source cell is 0, the rat(you) can not move to any cell */

    static void sub_1(){
        System.out.println("sub_1");
        int maze[][] = {
            {1, 0, 0, 0}, // _ X X X
            {1, 1, 0, 1}, // _ _ X _
            {1, 1, 0, 0}, // _ _ X X
            {0, 1, 1, 1}  // X _ _ _
        };
        int n = maze.length;
        List<String> result = new ArrayList<>();
        StringBuilder currentPath = new StringBuilder();

        if (maze[0][0] != 0 && maze[n-1][n-1] != 0){
            Solution s = new Solution();
            s.findPath(0, 0, maze, n, result, currentPath);
        }
        for (String r: result){
            System.out.print(r + " ");
        }
        System.out.println();
    }

    // the direction rat can move
    // Down(1,0) Left(0,1) Right(0,1) Up(1,0)
    static String direction = "DLRU";
    // represent change in rows and columns
    static int rowise[] = {1, 0, 0, -1};
    static int colwise[] = {0, -1, 1, 0};

    /* use blacktracking to explore all possible paths, keep track of the direction we have moved so far
       and when we reach to the BOTTOM RIGHT CELL */

    /* APPROACH
       isValid() check if position[row][col] is inside maze and unblocked.
       findPath() to get all valid Path:
            Base case : If curent position is the destination, add current path and return
            Mark the current cell as blocked
            Iterate through all possible directions
                * Calculate the next position based on the current direction
                * If the next position is Valid *APPEND* the direction to current path and call *findPath()* for the next cell
                * Backtrack by removing the last direction for the current path */

    private boolean isValid(int row, int col, int n, int maze[][]){
        return row >= 0 && col >= 0 && row < n && col < n && maze[row][col] == 1;
    }

    public void findPath(int row, int col, int maze[][], int n, List<String> ans, StringBuilder currentPath){
        // System.out.printf("[%d, %d] currentPath = %s\n",row, col, currentPath);
        if (row == n-1 && col == n-1) { // destination reached
            ans.add(currentPath.toString());
            // System.out.println("got an answer "+currentPath);
            return;
        }
        // mark current cell as blocked
        maze[row][col] = 0;

        for (int dir=0; dir<4; dir++) { // Down Left Rigth Up
            // Calculate next position
            int new_row = row + rowise[dir];
            int new_col = col + colwise[dir];

            // check if the new destination valid
            if ( isValid(new_row, new_col, n, maze) ){
                // append the direction
                currentPath.append(Solution.direction.charAt(dir));
                // call findPath() for the next cell
                findPath(new_row, new_col, maze, n, ans, currentPath);

                // backtracking remove last direction
                currentPath.deleteCharAt(currentPath.length()-1);
                // to ensures all path are explored 
                // to restores the maze's originak state for other paths
                // Correctly manages the path infomation by removing the last direction
                // System.out.printf("---Backtracked---[%d, %d] currentPath = %s\n",row, col, currentPath);
            }
        }
        // mark current cell as unblocked
        maze[row][col] = 1;
    }
}
