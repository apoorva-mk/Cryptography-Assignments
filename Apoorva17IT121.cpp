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

void testprime(long long int p)
{
	
	int ar[100]={0},i=0,j=0,a=7;
	long long int p2=p-1;
	long long int res=1,res2=0;
	while(p2>0)
	{
		ar[i++]=p2%2;
		p2/=2;
		
	}

	j=0;
	
	res2=a%p;
	

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

	if (res==1&&p!=1)
		cout<<"prime";

	else
		cout<<"not prime";
}

void fermat(long long int num)
{
	

	cout<<"\n\n\n\nFermat Method\n";
	int start_s=clock();
	long long int x=(sqrt(num))+1,w=0,y;
		x=sqrt(num)+1;
		
	
		while(x < num)
		{
			w=(x*x)-num;
			y=sqrt(w);
		
			if(pow(y,2)==w)
				break;

			else
				x++;
		}
		int stop_s=clock();

		if (x!=num)
		{
			cout<<"\nFactor-1 is "<<x-y<<" and it is ";
			int s1=clock();
			testprime(x-y);
			int s2=clock();
			
			cout<<"\nFactor-2 is "<<x+y<<" and it is ";
			
			int s3=clock();
			testprime(x+y);
			int s4=clock();

			cout<<"\nTime to derive factors is "<<(double)(stop_s-start_s)/CLOCKS_PER_SEC<<" seconds";
			cout<<"\nTime to verify primality of factor-1 is "<<(double)(s2-s1)/CLOCKS_PER_SEC<<" seconds";
			cout<<"\nTime to verify primality of factor-2 is "<<(double)(s4-s3)/CLOCKS_PER_SEC<<" seconds";
			
			
		}

		else
			cout<<"Fermat method failed"<<endl;


		
		
}

long long int f(long long int x)
{
	return (x*x)+1;
}

void pollrho(long long int num)
{
	

	cout<<"\n\n\n\nPollard Rho Method\n";


	long long int a,b,p;
		a=2;
		b=2;
		p=1;
	
		int start_s=clock();
		while(p==1)
		{
			a=f(a)%num;
			b=f(f(b)%num)%num;
			b%=num;
			p=__gcd(abs(a-b),num);
		}
		int stop_s=clock();

		if(p<=1)
		cout<<"\nPollard rho method failed"<<endl;

		else
		{
			cout<<"\nFactor-1 is "<<p<<" and it is ";
			int s1=clock();
			testprime(p);
			int s2=clock();
			cout<<"\nFactor-2 is "<<num/p<<" and it is ";
			int s3=clock();
			testprime(num/p);
			int s4=clock();
		

			cout<<"\nTime to derive factors is "<<(double)(stop_s-start_s)/CLOCKS_PER_SEC<<" seconds";
			cout<<"\nTime to verify primality of factor-1 is "<<(double)(s2-s1)/CLOCKS_PER_SEC<<" seconds";
			cout<<"\nTime to verify primality of factor-2 is "<<(double)(s4-s3)/CLOCKS_PER_SEC<<" seconds";
		}

}


void poll(long long int num)
{
	long long int c=2,e=2,p1=0;
	cout<<"\n\n\nPollard P-1 Method\n";
	int start_s=clock();
	long long int B=2,v=(ceil(sqrt(num)));	
	
	
	while(p1<=1 && B<=v)
	{
		c=2;
		e=2;
		
		while(e<=B)
		{
			c=sqmul(c,e,num);
			e=e+1;
		}
		
		B++;
		p1=__gcd(c-1,num);
		
	}
	 
	int stop_s=clock();

	if(p1<=1||p1==num)
	cout<<"\nPollard method failed"<<endl;

	else
	{
		cout<<"\nFactor-1 is "<<p1<<" and it is ";
		int s1=clock();
		testprime(p1);
		int s2=clock();
		cout<<"\nFactor-2 is "<<num/p1<<" and it is ";
		int s3=clock();
		testprime(num/p1);
		int s4=clock();
		

		cout<<"\nTime to derive factors is "<<(double)(stop_s-start_s)/CLOCKS_PER_SEC<<" seconds";
		cout<<"\nTime to verify primality of factor-1 is "<<(double)(s2-s1)/CLOCKS_PER_SEC<<" seconds";
		cout<<"\nTime to verify primality of factor-2 is "<<(double)(s4-s3)/CLOCKS_PER_SEC<<" seconds";
		
		
	}
	
}


int main()
{
	long long int num,b;
	cout<<"Enter number:";
	cin>>num;
	
	
	fermat(num);
	poll(num);
	pollrho(num);


}


