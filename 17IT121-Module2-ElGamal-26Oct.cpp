#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<bits/stdc++.h>
#include <ctime> 
 

using namespace std;



long long int sqmul(long long int c, long long int e,long long int p)
{
	int ar[100]={0},i=0,j=0;
	long long int p2=e;
	long long int res=1,res2=0;
	while(p2>0)
	{
		ar[i++]=p2%2;
		p2/=2;
		
	}

	j=0;
	
	res2=c%p;
	

	while(j<i)
	{
		if(ar[j])		
		{
			res*=res2;
		}
			
		res%=p;
		
		res2=(res2*res2)%p;
		
		j++;	
	}

	return res;
} 
 

void euclid(long long int p, long long int q, long long int *x,long long int *y) 
{ 
    
	if (p == 0) 
	{	 
		*x=0; 
		*y=1; 
		return ; 
	} 
  
	long long int x1, y1;
	euclid(q%p, p, &x1, &y1); 
   
	*x=y1-(q/p)*x1; 
	*y=x1; 
  
	return; 
} 

class A
{
	private:
	long long int d,r,rinv;
	
	public:
	long long int e1,e2,p,S1,S2;
	
	void keygen()
	{
		cout<<"\nEnter p: ";
		cin>>p;
		cout<<"\nEnter e1: ";
		cin>>e1;
		cout<<"\nEnter d: ";
		cin>>d; 
		e2=sqmul(e1,d,p);
		cout<<"\n\nPublic keys\np: "<<p<<"\ne1: "<<e1<<"\ne2: "<<e2<<endl<<endl;

	}

	void sig(long long int M)
	{
		
		cout<<"\nEnter r: ";
		cin>>r;
		long long int a,b;
		euclid(p-1,r,&a,&b);
		rinv=b;
		while(rinv<0)
		{
			rinv+=(p-1);
		}
		S1=sqmul(e1,r,p);
		S2=((M-d*S1));
		while(S2<0)
		{
			S2+=(p-1);
		}
		S2=(S2*rinv)%(p-1);
		cout<<"\nS1:"<<S1<<"\nS2:"<<S2;
		
	}

};



class B
{
	

	public:	
	long long int V1,V2;
	void ver(long long int M,long long int S1, long long int S2,long long int e2,long long int p,long long int e1)
	{
		V1=(sqmul(e2,S1,p)*sqmul(S1,S2,p))%p;
		V2=sqmul(e1,M,p);
		cout<<"\nV1: "<<V1<<" "<<"\nV2: "<<V2;	
		if(V1==V2)
		{
			cout<<"\nSignature Verfied and Message Accepted";
		}

		else
		{
			cout<<"Signature not verified";
		}
	}


};


int main()
{
	A Alice;
	B Bob;
	long long int mes;
	string M;
	ofstream fileout;
	fileout.open("Output.txt");
	
	cout<<"\nEnter message: ";
	cin>>M;
	
	Alice.keygen();
	int j=8;
	fileout<<"\n\nPublic keys\np: "<<Alice.p<<"\ne1: "<<Alice.e1<<"\ne2: "<<Alice.e2<<endl<<endl;
	while( Alice.p >= pow(2,j) && Alice.p >= pow(2,j+1) )
	{
		j+=8;
	}
		
	j/=8;	
	for(int i=0;i<M.size();i++)
	{
		mes=0;
		for(int k=1;k<=j && i<M.size();k++)
		{	
			
			mes+= int(M[i]);
			i++;
			
		}

		i--;

		Alice.sig(mes);
		fileout<<"\nS1: "<<Alice.S1<<"\nS2: "<<Alice.S2;
		
		Bob.ver(mes,Alice.S1,Alice.S2,Alice.e2,Alice.p,Alice.e1);
		fileout<<"\nV1: "<<Bob.V1<<" "<<"\nV2: "<<Bob.V2;
		if(Bob.V1==Bob.V2)
		{
			fileout<<"\nSignature Verfied and Message Accepted\n\n";
		}

		else
		{
			fileout<<"\n\nSignature not verified\n\n";
		}
		
	}
	fileout.close();

	
  	return 0;
}
	
	
	
	
