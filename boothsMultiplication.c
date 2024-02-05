#include<stdio.h>
#include<stdlib.h>
int power(int a,int b){
    int sum=1;
    for(int i=0;i<b;i++){
        sum=sum*a;
    }
    return sum;
}
int bitofnum(int bin,int base){
    int rem=0,b=bin,r;
    while(b>0)
    {
        rem+=1;
        b=b/base;
    }
    return rem;
}
void decimaltornary(int bin,int base){
    int rem=0,b=bin,r;
    while(b>0)
    {
        rem+=1;
        b=b/base;
    }
    int a[rem];
    for(int i=0;i<rem;i++)
    {
        r=bin%base;
        a[i]=r;
        bin/=base;
    }
    printf("Ans = ");
    for(int i=(rem-1);i>=0;i--)
    {
        printf("%d",a[i]);
    }
}
int rtodecimal(int *arr,int base,int bit){
    int answer=0;
    for(int i=0;i<bit;i++){
        answer=answer+(*(arr+i)*power(base,i));
    }
    return answer;
}
int rnarytodecimal(int bin,int base)
{
    int rem=0,b=bin,r,ans;
    rem=bitofnum(bin,base);
    int arr[rem];
    for(int i=0;i<rem;i++)
    {
        r=bin%10;
        arr[i]=r;
        bin/=10;
    }
    return rtodecimal(arr,base,rem);
}

void multiply(int base,int bita,int bitb,int *arr_a,int *arr_b){
    int bit;
    if(bita>=bitb)
        bit=bita+1;
    else
        bit=bitb+1;
    int M[bit],Q[bit],ans[2*bit];
    for(int i=0;i<bit;i++){
        M[i]=*(arr_a+i);
        Q[i]=*(arr_b+i);
    }
    if(bita>bitb){
        M[bita]=0;
        for(int i=bitb;i<bit;i++)
            Q[i]=0;
    }
    else{
        Q[bitb]=0;
        for(int i=bita;i<bit;i++)
            M[i]=0;
    }

    int A[bit],Q_1=0,counter=bit,M_1[bit];
    for(int i=0;i<bit;i++){
        A[i]=0;
    }
    for(int i=0;i<bit;i++){
        M_1[i]=M[i]^1;
    }
    int carr=0,carr2=0;
    M_1[0]=M_1[0]+1;
    for(int i=0;i<bit;i++){
        if(M_1[i]+carr==2){
            M_1[i]=0;
            carr=1;
        }
        else{
            M_1[i]=M_1[i]+carr;
            carr=0;
        }
    }
    carr=0; 
    while(counter>0){
        if(Q[0]==0 && Q_1==1){
            carr2=0,carr=0;
            for(int i=0;i<bit;i++){
                carr=(A[i]+M[i]+carr)/2;
                A[i]=(A[i]+M[i]+carr2)%2;
                carr2=carr;
            }
            Q_1=Q[0];
            for(int i=0;i<bit;i++){
                Q[i]=Q[i+1];
            }
            Q[bit-1]=A[0];
            for(int i=0;i<bit-1;i++){
                A[i]=A[i+1];
            }
        }
        else if(Q[0]==1 && Q_1==0){
            carr2=0,carr=0;
            for(int i=0;i<bit;i++){
                carr=(A[i]+M_1[i]+carr)/2;
                A[i]=(A[i]+M_1[i]+carr2)%2;
                carr2=carr;
            }
            Q_1=Q[0];
            for(int i=0;i<bit;i++){
                Q[i]=Q[i+1];
            }
            Q[bit-1]=A[0];
            for(int i=0;i<bit-1;i++){
                A[i]=A[i+1];
            }
        }
        else{
            Q_1=Q[0];
            for(int i=0;i<bit;i++){
                Q[i]=Q[i+1];
            }
            Q[bit-1]=A[0];
            for(int i=0;i<bit-1;i++){
                A[i]=A[i+1];
            }
        }
        counter--;
    }
    for(int i=0;i<bit;i++){
        ans[i]=Q[i];
    }    
    for(int i=0;i<bit;i++){
        ans[bit+i]=A[i];
    }
    int answer=rtodecimal(ans,2,2*bit);
    decimaltornary(answer,base);
      
}

int main(){
    while(1){
        int a,b,base;
        printf("\nEnter Base: ");
        scanf("%d",&base);
        printf("Enter 1st number: ");
        scanf("%d",&a);
        printf("Enter 2nd number: ");
        scanf("%d",&b);     
        int c,d;
        c=rnarytodecimal(a,base);
        d=rnarytodecimal(b,base);
        int bita=1,bitb=1;
	    for(int i=2;i<c;i=i*2){
		    bita++;
    	}
    	for(int i=2;i<d;i=i*2){
    		bitb++;
	    }
	    int arr_a[bita];
	    for(int i=0;c>0;i++){
		    arr_a[i]=c%2;
    		c=c/2;
	    }
	    int arr_b[bitb];
	    for(int i=0;d>0;i++){
		    arr_b[i]=d%2;
    		d=d/2;
	    }
        multiply(base,bita,bitb,arr_a,arr_b);
    }
}
