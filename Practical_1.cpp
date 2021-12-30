#include<iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;

int msg,gen,length_msg,length_gen;

void rev(int num[],int len){
	for(int i=0,j=len-1;i<len/2;i++,--j){
		int temp=num[i];
		num[i]=num[j];
		num[j]=temp;
	}
	return;
}

int dec_to_bin(int dec,int bin[]){
	int temp=dec,i=0;
	while(temp!=0){
		bin[i]=temp%2;
		temp/=2;
		i++;
	}
	
	for(int j=0,k=i-1;j<=k;j++,--k){
		temp=bin[j];
		bin[j]=bin[k];
		bin[k]=temp;
	}
	
	for(int j=0;j<=i;j++){
		cout<<bin[j]<<" ";
	}
	cout<<endl;
	return i;
}

int xOR(int msg[],int gen[],int len_gen,int len_msg)
 {
      int j=0,k;
      while(msg[j]!=1)
         j++;
      if((len_msg-j)<len_gen)
         return 0;


      for(int i=j,k=0;i<(j+len_gen);i++,k++)
      {
         if(msg[i]==gen[k])
            msg[i]=0;
         else
            msg[i]=1;
      }
      return 1;
 }


 void modulo_2_division(int msg[],int &len_msg,int gn[],int len_gn)
 {
      int flag;
      for(int i=0;i<len_gn;i++){
         msg[len_msg+i] = 0;
        }

        len_msg=len_msg+len_gn-1;
		cout<<"\nmsg after appending zeroes : ";
      
      for(int i=0;i<len_msg;i++){
         cout<<msg[i]<<" ";
      }
	  cout<<endl;

      for(int i=0;i<len_msg-2;i++)
      {
         flag=xOR(msg,gn,len_gn,len_msg);
         if(flag==0)
         break;
      }

      cout<<"\nThe msg now after dividing : ";

      for(int i=0;i<len_msg;i++)
         cout<<msg[i]<<" ";
      cout<<endl;
 }
  
void modulo_2_division(int msg[],int gn[])
 {
      int flag;
      for(int i=0;i<length_msg-2;i++)
      {
         flag=xOR(msg,gn,length_gen,length_msg);
         if(flag==0)
         break;
      }
      cout<<"\nThe msg now after checking : ";

      for(int i=0;i<length_msg;i++)
         cout<<msg[i]<<" ";
      cout<<endl;
 }

int main(){
      int msg_pass[20],codeword[20],i=0,genr[6],rem[6],ori_msg_len;
      
      cout<<"\nEnter the message to be passed(in decimal) : ";
      cin>>msg;
      cout<<"\nThe message in binary code : ";
      
      length_msg=dec_to_bin(msg,msg_pass);

      cout<<"\nEnter the generator number i.e, the divisor:(in decimal) : ";
      cin>>gen;
      cout<<"\nthe binary value of generator is : ";
      
      length_gen=dec_to_bin(gen,genr);
      for(int j=0;j<length_msg;j++)
         codeword[j]=msg_pass[j];
      ori_msg_len=length_msg;

      modulo_2_division(msg_pass,length_msg,genr,length_gen);

      int codeword_lenght=ori_msg_len;
      cout<<"\nThe crc remainder is : ";
      for(int j=length_msg-length_gen+1;j<length_msg;j++)
      {
        cout<<msg_pass[j]<<" ";
          codeword[codeword_lenght]=msg_pass[j];
          codeword_lenght++;
      }
      cout<<endl;

      cout<<"\nThe msg to be passed : ";

      for(i=0;i<codeword_lenght;i++)
         cout<<codeword[i]<<" ";
      cout<<endl;

      int codeword_rec[length_msg];
      for(int i=0;i<length_msg;i++)
         codeword_rec[i] = codeword[i];

      srand((unsigned) time(0));
      bool choice = rand()%2;
      int index = rand()%length_msg;

      if(choice)
        codeword_rec[index]=(codeword_rec[index]+1)%2;

      cout<<"\ncodeword recieved : ";
      for(int i=0;i<length_msg;i++)
        cout<<codeword_rec[i]<<" ";
      cout<<endl;
      int checker[length_msg];
      for(int i=0;i<length_msg;i++)
        checker[i] = codeword_rec[i];

      modulo_2_division(checker,genr);

      bool flag=true;

      for(int i=0;i<length_msg;i++){
        if(checker[i]==1){
          flag=false;
          break;
        }
      }

      if(flag){
        cout<<"No error detected in codeword, extracting dataword ... \n";
        for(int i=0;i<length_msg-length_gen+1;i++)
          cout<<codeword_rec[i]<<" ";
        cout<<endl;
      }
      else
        cout<<"\nerror detected in recieved codeword!!\nDiscarding codeword!!!\n";
      return 0;
}  
