#include<cstdio>
#include<utility>
#include<algorithm>

using namespace std;

#define MP(a,b) make_pair(a,b)

typedef pair<int,int> P;

bool f;
int ans,n,m,cnt;
P tg[9],tg1[2],tg2[2];

inline int length(int x){
	if(x>m)return m+n-x;
	if(x>n)return n;
	return x;
}

void build(int x,int k){
	int l=length(x);
	int N=x+2>m?l:n;
	
	tg1[f]=MP(0,0);tg2[f]=MP(0,0);
	
	if(k>1)tg1[f]=MP(2,k+1<N?k+1:N);
	if(l-k>2||l-k==2&&x<n)tg2[f]=MP(k+2,l+1<N?l+1:N);
	if(tg1[f].first==tg1[f].second)tg1[f]=MP(0,0);
	if(tg2[f].first==tg2[f].second)tg2[f]=MP(0,0);
	
	if(x+2>m){
		if(tg1[f].first>0)--tg1[f].first,--tg1[f].second; 
		if(tg2[f].first>0)--tg2[f].first,--tg2[f].second;
	}
	if(x+1>m){
		if(tg1[f].second==2)tg1[f]=MP(0,0);
		else --tg1[f].second;
		
		--tg2[f].second;
		if(tg2[f].first>1)--tg2[f].first;
	}
	
	//printf("%d %d %d %d\n",tg1[f].first,tg1[f].second,tg2[f].first,tg2[f].second);
	
	f^=1;
	
	for(int i=1;i<=cnt;++i){
		if(tg[i].second<l)++tg[i].second;
		if(x+1>m){
			if(tg[i].first>1)--tg[i].first;
			//--tg[i].second;
		}
	}
		
	if(tg1[f].first>0)tg[++cnt]=tg1[f];
	if(tg2[f].first>0)tg[++cnt]=tg2[f];
	
	sort(tg+1,tg+cnt+1);
	
	for(int i=1;i<cnt;++i){
		if(tg[i+1].first<=tg[i].second){
			tg[i]=MP(tg[i].first,max(tg[i].second,tg[i+1].second));
			for(int j=1+i;j<cnt;++j)
				tg[j]=tg[j+1];
			--cnt;
		}
	}
	
/*	printf("%d %d\n",x,k);
	for(int i=1;i<=cnt;++i){
		printf("%d %d%c",tg[i].first,tg[i].second," \n"[i==cnt]);
	}*/
	
}

void dfs(int x){
	//printf("x:%d\n ",x);
		
	if(x==n+m-1){
		++ans;
		return;
	}
	
	int i,j=1,l=length(x),tnt=cnt;
	P Tg[9];
	
	for(i=1;i<=tnt;++i)
		Tg[i]=tg[i];

	//if(x==4)printf("**%d %d\n",tg.second.first,cnt);
	
	for(i=0;i<=l;++i)
		if(i<tg[j].first||j>cnt){
			build(x,i);	
			dfs(x+1);
			cnt=tnt;
			for(int k=1;k<=tnt;++k)
				tg[k]=Tg[k];
		}
		else if(i==tg[j].first&&j<=cnt){
			i=tg[j++].second;
			build(x,i);
			dfs(x+1);
			cnt=tnt;
			for(int k=1;k<=tnt;++k)
				tg[k]=Tg[k];
		}	

}

int main(){
	//freopen("4.txt","w",stdout);
    scanf("%d%d",&n,&m);
    if(n>m)std::swap(n,m);
    dfs(2);
    printf("%d\n",(ans<<2)%(int)(1e9+7));
    return 0;
}
