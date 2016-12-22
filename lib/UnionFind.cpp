#include <iostream>

using namespace std;

class UnionFind;

class SubSet
{
	private:
		int parent;
		int rank;
		friend class UnionFind;
	public:
		//SubSet(long n){}
};

class UnionFind
{
	private:
		SubSet *S;
	public:
		UnionFind(int n);
		void Union(int x, int y);
		int find(int i);
		bool isConnected(int x, int y);
};

UnionFind::UnionFind(int n)
{
	S = new SubSet[n];
	for(int i = 0; i< n;i++)
	{
		S[i].parent = i;
		S[i].rank = 0;
	}
}

int UnionFind::find(int i)
{
    // find root and make root as parent of i (path compression)
    if (S[i].parent != i)
    {
        S[i].parent = find(S[i].parent);
	}
 
    return S[i].parent;
}

void UnionFind::Union(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
 
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (S[xroot].rank < S[yroot].rank)
    {
        S[xroot].parent = yroot;
	}
    else if (S[xroot].rank > S[yroot].rank)
    {
        S[yroot].parent = xroot;
	}
    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        S[yroot].parent = xroot;
        S[xroot].rank++;
    }
}

bool UnionFind::isConnected(int x,int y)
{
	return find(x) == find(y);
}

int main()
{
	UnionFind uf(110000);
	uf.Union(3,110000);
	cout<<"is Connected : "<<uf.isConnected(7,110000)<<endl;
	return 0;
}

