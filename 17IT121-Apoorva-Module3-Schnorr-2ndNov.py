import hashlib
import math

def hsh(string):
	return hashlib.md5(string.encode())

def sqmul(c, e, p) : 
	ans = 1     
	while e > 0 : 
		if e % 2 == 1 : 
			ans = (ans * c) % p  
 
		e = e >> 1     
		c = ( c * c ) % p 
          
	return ans 


	
def sig(p,q,e1,d,r,e2,M):
	temp=sqmul(e1,r,p)
	print("\nThe string before hashing to generate S1 : ", M+str(temp))
	S1=int(hsh(M+str(temp)).hexdigest(),16)
	S2=(r+d*S1)%q
	print("S1: ",S1," ","\nS2: ",S2)	
	return (S1,S2)
	

def euclid2(a, b, x, y): 
	if a == 0 :  
		x = 0
		y = 1
		return b 
       
	x1 = 1
	y1 = 1
	gcd = euclid(b%a, a, x1, y1) 
	x = y1 - (b/a) * x1 
	y = x1 
	return gcd 



def ext(p,q):
	if p==0:
		return (0,1)

	else:
		a,b=ext(q%p,p)
		return(b-int((q/p))*a,a)

def euclid(a, m):
	
	if math.gcd(a,m)!= 1:
		print("Inverse can't be calculated")
		exit()

	else:
		x,y=ext(a,m)
		return x%m

def verify(e1,e2,M,S2,S1,p):
	inv=euclid(e2,p)		
	temp2=str( (sqmul(e1,S2,p)*sqmul(inv,S1,p))%p )
	print("\n\nThe string before hashing to generate V : ", M+temp2)
	V=int(hsh(M+temp2).hexdigest(),16)
	print("V :",V)
	
	S1=S1%p
	if V%p==S1:
		print("\nS1%p = ",S1," ","\nV%p= ",V%p)
		print("Hence Signatures Verified")
		
	else:	
		print("Signatures not verified")
		

	return V

def main():
	M=(input("Enter message: "))
	mes=""
	for i in M:
		mes=mes+str(ord(i))

	M=str(mes)
	p=2267
	p=int(input("Enter p: "))
	q=103
	q=int(input("Enter q: "))
	e1=354
	e0=0
	e0=int(input("Enter e0: "))

	f=open("Schnorr_output.txt","w");

	if( math.gcd(p,q)==1):	
		for i in range(1,p-1):
			if int((e0**i)) %p==1:
				print('q is not a primitive root')
				f.write('q is not a primitive root')
				exit()

	else:
		print('q is not a primitive root')
		f.write('q is not a primitive root')
		exit()



	e1=sqmul(e0,int((p-1)/q),p)
			
	d=30
	d=int(input("Enter d: "))
	r=11
	r=int(input("Enter r: "))
	S1=0
	S2=0
	V=0
	e2=sqmul(e1,d,p)
	print("M: ",M)
	print("\ne1: ",e1,"\ne2: ",e2," ")
	f.write("\ne1: "+str(e1)+"\ne2: "+str(e2)+" ")
	
	S1,S2=sig(p,q,e1,d,r,e2,M)
	f.write("\nS1: "+str(S1)+" "+"\nS2: "+str(S2))
	V=verify(e1,e2,M,S2,S1,p)
	f.write("\nV :"+str(V))
	if V%p==S1%p:
		f.write("\nS1%p = "+str(S1%p)+" "+"\nV%p= "+str(V%p))
		f.write("\nHence Signatures Verified")

	else:	
		f.write("Signatures not verified")
		

if __name__=='__main__':
	main()
