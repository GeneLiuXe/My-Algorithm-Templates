// ---
// 题意:\\
// 一条街上一共 $N$ 个点，需要在某些点上建路灯，使得整条街被照亮，一个路灯可以照亮左右两个点，每个点都有一个建路灯的花费。现在你还有 $K$ 次机会，可以交换两个路灯的建造费用，求使得整条街被照亮的最小花费。$(1\leq N\leq 250000,0\leq k\leq 9)$\\
// \\
// 思路:\\
// 如果这道题没有 $K$ 次交换路灯花费的操作的话，问题将会变得简单很多，只需要记录每个点某尾和前一个点的状态即可递推求解。\\
// \\
// 但是此题有了 $K$ 次交换路灯的条件。仔细观察，可以发现，交换路灯花费时，一定是在便宜的那个点上建路灯，在贵的那个点上不建路灯，交换两个都要建路灯的节点是没有意义的。因此我们考虑将建灯花费先欠着，即对于点 $i$ 来说，我们让这个点灯亮，但是具体花费先欠着，等到后面一个点的时候再还这个费用。\\
// \\
// 因此我们构建 $DP$ 状态，$dp[i][j][k][l]$ 表示第 $i$ 个点，欠了 $j$ 次，还了 $k$ 次，$l$ 表示节点最后两个点的状态。$l=0$，亮+不亮。$l=1$，不亮+亮。$l=2$，(亮/不亮)+亮。\\
// \\
// 然后就可以进行转移了，具体转移过程见代码，并不复杂，主要难点在于这个思想。\\
// \\
// 总结:\\
// 亏欠型 $DP$ 的核心关键点在于 “欠” 与 “还”。“欠” 对应着预支花费，“还” 对应着预付花费，可以有效的解决交换花费的问题。\\
// \\
// 这种方法的重要思想是 “预支”，与此类似的还有一种思想是 “反悔”，就是我先把这个值拿过来，如果之后发现更好的，我再把它扔掉。（如网络流中的反向边）\\
// ---
#include <bits/stdc++.h>
#define __ ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define LOG1(x1,x2) cout << x1 << ": " << x2 << endl;
#define LOG2(x1,x2,y1,y2) cout << x1 << ": " << x2 << " , " << y1 << ": " << y2 << endl;
#define LOG3(x1,x2,y1,y2,z1,z2) cout << x1 << ": " << x2 << " , " << y1 << ": " << y2 << " , " << z1 << ": " << z2 << endl;
typedef long long ll;
typedef double db;
const db EPS = 1e-9;
const int N = 250000+100;
using namespace std;

int n,K;
ll dp[N][10][10][3],w[N];

int main()
{
	scanf("%d%d",&n,&K);
	rep(i,1,n) scanf("%lld",&w[i]);
	memset(dp,0x3f,sizeof dp);
	dp[0][0][0][0] = 0; //第i个位置，欠了j个，还了k个
	rep(i,1,n)
		rep(j,0,K){
			rep(k,0,K){
				dp[i][j][k][0] = dp[i-1][j][k][2];
				if(k > 0) dp[i][j][k][0] = min(dp[i][j][k][0],dp[i-1][j][k-1][2]+w[i]);

				dp[i][j][k][1] = dp[i-1][j][k][0];
				if(k > 0) dp[i][j][k][1] = min(dp[i][j][k][1],dp[i-1][j][k-1][0]+w[i]);		
				
				rep(h,0,2)
					dp[i][j][k][2] = min(dp[i][j][k][2],dp[i-1][j][k][h]+w[i]);
				if(j > 0){
					rep(h,0,2)
						dp[i][j][k][2] = min(dp[i][j][k][2],dp[i-1][j-1][k][h]);
				}
			}
		}
	ll ans = 1e17;
	rep(i,0,K)
		ans = min(ans,min(dp[n][i][i][0],dp[n][i][i][2]));
	printf("%lld\n",ans);
	return 0;
}