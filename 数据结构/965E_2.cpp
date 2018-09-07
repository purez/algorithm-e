 * 题意：给出很多字符串(1e5)，总长度不超过1e5.
 * 每个字符串用其某前缀代替，代替后要保证每个字符串互不相同。
 * 求代替后最短的总距离。
 *
 *
 *    题解：
 *
 *    做法非常巧妙和套路
 *
 *    建个Trie树，每个节点维护深度和一个multiset用于存储深度（当前取得字符串前缀的长度）（也可以用priority_queue，这种做法明天补上）
 *
 *    初始时，叶节点的multiset存储该节点的深度，这个初始状态就是最差的情况，即每个字符串都保留原串，下面会在合并的时候进行统计和优化。
 *
 *    然后从根节点开始dfs，dfs回溯段合并子节点的multiset，合并之后，去掉multiset中的最大值，插入当前节点深度（意义就是将当前最长的前缀替换成当前节点所代表的前缀，这样贪心一定是最优的）。
 *
 *    最后遍历根节点的multiset就可以得到答案。
 *    合并的复杂度是这样的，根据主定理，就是mlogm
 *     ，multiset的操作的复杂度是logm，总复杂度是m*(logm)^2
 *     合并之后一定要把子节点的multiset清空，不然会MLE。

#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<string>
#include<set>
#include<vector>
using namespace std;
int read(){
   	int xx=0,ff=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){xx=xx*10+ch-'0';ch=getchar();}
    return xx*ff;
}
const int maxn=100010;
int N;
char str[maxn];
struct Trie{
    int lin[26];
    int depth;
    multiset<int>s;
}T[maxn];
int cnt=0;
void insert(int depth,int root){
	if(!str[depth]){
		T[root].s.insert(T[root].depth);
		return;
   	}
	if(!T[root].lin[str[depth]-'a']){
		T[root].lin[str[depth]-'a']=++cnt;
		T[cnt].depth=T[root].depth+1;
   	}	insert(depth+1,T[root].lin[str[depth]-'a']);
}
void trav(int x){
	bool flag=x&&T[x].s.empty();
	for(int i=0;i<26;i++)
		if(T[x].lin[i]){
			trav(T[x].lin[i]);
			if(T[x].s.size()<T[T[x].lin[i]].s.size())
				swap(T[x].s,T[T[x].lin[i]].s);
			for(multiset<int>::iterator it=T[T[x].lin[i]].s.begin();it!=T[T[x].lin[i]].s.end();it++)
				T[x].s.insert(*it);
			T[T[x].lin[i]].s.clear();												}
	if(flag){
		T[x].s.erase(--T[x].s.end());
		T[x].s.insert(T[x].depth);
	}
}
int main(){
	    //freopen("in","r",stdin);
	N=read();
	for(int i=1;i<=N;i++){
		gets(str);
		insert(0,0);
	}
	trav(0);
	long long ans=0;
	for(multiset<int>::iterator it=T[0].s.begin();it!=T[0].s.end();it++)
		ans+=(*it);
		printf("%I64d\n",ans);
		return 0;
}
