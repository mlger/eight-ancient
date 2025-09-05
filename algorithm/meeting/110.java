import java.util.Scanner;

public class Main {
    static final int maxn = (int)1e5 + 5;
    static final int mod = (int)1e9 + 7;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt();
        
        long[] val = new long[n + 1];
        int[] nums = new int[n + 1];
        
        for (int i = 1; i <= n; i++) {
            val[i] = scanner.nextLong();
        }
        
        for (int i = 1; i <= n; i++) {
            nums[i] = scanner.nextInt();
        }
        
        // f[j][k] 表示前i-1个数处理完毕，倒数第二个数为j，倒数第一个数为k的最大价值
        // 0/1 表示对应的数字，2 表示空
        long[][] f = new long[3][3];
        long[][] g = new long[3][3];
        
        // 初始化为最小值
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                f[i][j] = -1;
            }
        }
        
        f[2][2] = 0; // 初始状态：所有数都未保留
        
        for (int i = 1; i <= n; i++) {
            int x = nums[i];
            
            // 复制当前状态到g
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    g[j][k] = f[j][k];
                }
            }
            
            // 1. 不保留当前位置
            // (状态已复制，无需额外操作)
            
            // 2. 保留当前位置
            // 2.1 删剩下一个(与当前位置)
            if (f[2][x] == -1 || f[2][x] < val[i]) {
                g[2][x] = val[i];
            } else {
                g[2][x] = f[2][x];
            }
            
            // 2.2 删剩下两个数字
            if (x == 0) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        // 不能拼接110
                        if (j == 1 && k == 1) {
                            continue;
                        }
                        // 前置状态需要存在
                        if (f[j][k] == -1) {
                            continue;
                        }
                        if (g[k][x] == -1 || g[k][x] < f[j][k] + val[i]) {
                            g[k][x] = f[j][k] + val[i];
                        }
                    }
                }
            } else { // x == 1
				// TODO
            }
            
            // 更新状态
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    f[j][k] = g[j][k];
                }
            }
        }
        
        // 找出最大值
        long maxVal = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (f[i][j] > maxVal) {
                    maxVal = f[i][j];
                }
            }
        }
        
        System.out.println(maxVal % mod);
    }
}


/**
 * 
 * x个小写, y个大写
 * 翻1次, x+2y
 * 2, x+4y
 * n, x+ 2^ny
 */