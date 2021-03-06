// ---
// 一、适用问题: \\
// \\
// 回文自动机其实可以当作回文串问题的大杀器，主要可以解决以下问题：\\
// 1. 本质不同回文串个数 \\
// 2. 每个本质不同回文串出现的次数 \\
// 3. 以某一个节点为结尾的回文串个数 \\
// 4. ... \\
// \\
// 而且都是在 O(n) 的复杂度内解决了这些问题。但是要注意，回文自动机并不能完全替代马拉车算法，因为马拉车针对的是以一个节点为中心所能扩展的最远的距离，而回文自动机更多的是处理以一个节点为结尾的回文串数量。\\
// \\
// 二、回文自动机算法解析 \\
// \\
// (1) 基础思想\\
// 与$AC$自动机一样，回文自动机的构造也使⽤了$Trie$树的结构。\\
// \\
// 不同点在于回文自动机有两个根，一个是偶数⻓度回⽂串的根，一个是奇数⻓度回⽂串的根，简称为奇根和偶根。自动机中每个节点表⽰⼀个回⽂串，且都有⼀个 $fail$ 指针，指向当前节点所表⽰的回文串的最长回文后缀（不包括其本身）。\\
// \\
// (2) 具体构建过程\\
// 首先将偶根的 $fail$ 指针指向奇根，奇根的 $fail$ 指针指向偶根，然后令奇根的长度为 $-1$，偶根长度为 $1$。\\
// \\
// 在构建过程中，始终要记录一个 $last$ 指针，表示上一次插入之后所位于的回文自动机节点。然后判断插入当前节点之后是否能够形成一个新的回文串，如果不能则跳 $fail$ 指针，整体逻辑与$AC$自动机的构建没有太大差别。\\
// \\
// $fail$ 指针表示当前节点所代表的回文串的最长后缀回文串，此处$fail$指针的定义与$AC$自动机有一定区别，但本质目的相同，都是为了尽可能地保存之前的匹配结果。\\
// \\
// 而 $fail$ 指针的构建是根据当前节点的父节点的 $fail$ 节点构建而来，与$AC$自动机的 $fail$ 构建没有太大差别。\\
// \\
// 大致上就是这样一个构建过程，具体细节可以查看下述模板，也可以查看 $oi_wiki$ 的图解构建。\\
// \\
// (3) 统计每个本质不同回文串的出现次数\\
// 与$AC$自动机一样，每个节点所代表字符串出现的次数要加上其所有 $fail$ 子孙出现的次数，因此需要倒序遍历所有节点将节点出现次数累加到其 $fail$ 节点上。\\
// ---
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define per(i,a,b) for(int i = a; i >= b; i--)
const int N = 1e5+10;
using namespace std;

struct PAM{
	#define KIND 26
	int n,last,tot;
	int len[N],trie[N][KIND],fail[N],cnt[N],S[N],num[N];
	//len[i]: 节点i所代表的回文串长度, fail[i]: 当前回文串的最长回文后缀（不包括自身）
	//cnt[i]: 节点i所代表的回文串的个数, S[i]: 第i次添加的字符, num[i]: 以第i个字符为结尾的回文串个数
	//last: 上一个字符构成最长回文串的位置，方便下一个字符的插入
	//tot: 总结点个数 = 本质不同的回文串的个数+2, n: 插入字符的个数 
	int newnode(int l){
		rep(i,0,KIND-1) trie[tot][i] = 0;
		cnt[tot] = 0, len[tot] = l, num[tot] = 0;
		return tot++;
	}
	inline void init(){
		tot = n = last = 0, newnode(0), newnode(-1);
		S[0] = -1, fail[0] = 1;
	}
	int get_fail(int x){ //获取fail指针
		while(S[n-len[x]-1] != S[n]) x = fail[x];
		return x;
	}
	inline int insert(int c){ //插入字符
		c -= 'a';
		S[++n] = c;
		int cur = get_fail(last);
		//在节点cur前的字符与当前字符相同，即构成一个回文串
		if(!trie[cur][c]){ //这个回文串没有出现过
			int now = newnode(len[cur]+2);
			fail[now] = trie[get_fail(fail[cur])][c];
			trie[cur][c] = now;
			num[now] = num[fail[now]]+1; //更新以当前字符为结尾的回文串的个数
		}
		last = trie[cur][c];
		cnt[last]++; //更新当前回文串的个数
		return num[last]; //返回以当前字符结尾的回文串的个数
	}
	void count(){ //统计每个本质不同回文串的个数
		per(i,tot-1,0) cnt[fail[i]] += cnt[i];
	}
}pam;

// Fail[i] 失配指针。像AC自动机差不多的失配指针，这个指向的是同样回文串结尾的最长回文串。\\
// len[i] 当前回文串的长度。 \\
// num[i]  代表 i 这个节点所代表的回文串中的回文后缀个数;\\
// cnt[i]  代表 i 这个节点所代表的回文串一共出现了多少次。 这个最后要 $count()$ 一下。\\

// sz 节点个数代表本质不同的回文串的个数。\\

// 每个回文串的长度还有出现的次数.\\

#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+100;
char s[N];
namespace PAM {
    int sz, fl[N], len[N], ch[N][26], num[N], cnt[N],now,n;
    long long ans = 0;    
    char *s;
    int find(int x, int y) {
        return s[y] == s[y - len[x] - 1] ? x : find(fl[x], y);
    }
    void init(char *str){
        memset(ch, 0, sizeof(ch));
        memset(fl, 0, sizeof(fl));
        memset(cnt, 0, sizeof cnt);
        memset(num, 0, sizeof num);  //多组数据的时候别忘记 清零.
        s = str; now = 0;
        n = strlen(s + 1);    //字符串从　１　开始．　
        sz = 1;  fl[0] = 1;  
        len[0] = 0;   len[1] = -1;
    }
    void cal() {
        for (int i = 1; i <= n; i++) {
            now = find(now, i);
            if (!ch[now][s[i] - 'a']) {
                len[++sz] = len[now] + 2;
                fl[sz] = ch[find(fl[now], i)][s[i] - 'a'];
                ch[now][s[i] - 'a'] = sz;
                num[sz] = num[fl[sz]] + 1;
            }
            now = ch[now][s[i] - 'a'];
            cnt[now]++;
        }
        for (int i = sz; i > 1; --i) {
            cnt[fl[i]] += cnt[i];
            ans = max(ans,1ll*cnt[i]*len[i]);
        }
    }
};
int main(){
    scanf("%s",s+1);
    PAM::init(s);
    PAM::cal();
    printf("%lld\n",PAM::ans);
    return 0;
}