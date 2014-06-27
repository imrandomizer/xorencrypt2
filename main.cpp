#include <iostream>
#include <fstream>
#include <string>
#include <hashlibpp.h>
#include <hl_sha256.cpp>
#include <hl_sha256wrapper.cpp>
#include <stdlib.h>

using namespace std;

int int_parse(char *a){

    int ret=0,i=0,len=strlen(a);
    while(i!=len)
    ret=ret*10+(int)a[i++]-(int)'0';
    return ret;
}

//arr : array to be xored
//file file name , n =overwrite or not ?
int enc_or_dec(char *arr,char  *pswd,char *file,int n,int msg_leng,int mode,string h_code){
    if(n==0){
        char *ocr;
        ocr=strstr(file,".jpeg");
        if(ocr==nullptr){
            char *last=strchr(file,'.');
            char ext[5];
            strcpy(ext,last);
            last[0]='\0';
            strcat(file,"_encrypted");
            strcat(file,ext);
        }
    }
    ofstream out(file,ios_base::binary);
    if(mode==1){
        out<<h_code<<" ";
    }

    int pswd_len=strlen(pswd);
    int xor_head=0;

    for(int i=0;i<msg_leng;i++){
        xor_head=i+1+(int)pswd[i%pswd_len];
        arr[i]=(char)(xor_head^(int)arr[i]);
    }
    out.write(arr,msg_leng);
    return 0;
}

int main (int argc, char *argv[]) {

    if(argc==0||argc==1){
        cout<<"Designed And Programmed By Namit Sinha , Randomizer\n";
        return 0;
    }
    int enc_dec=int_parse(argv[2]);
    int owt=int_parse(argv[3]);
    string pswd(argv[4]);
    hashwrapper *md5 = new sha256wrapper();
    string hashed=md5->getHashFromString(pswd);
    ifstream inps(argv[1],ios_base::binary);
    inps.seekg(0,ios_base::end);
    int x=inps.tellg();
    inps.seekg(0);

    int head=0;
    if(enc_dec==2){
        string hashcmp;
        inps>>hashcmp;
        if(hashcmp.compare(hashed)!=0){
            cout<<"3";
            return 0;
        }
        head=65;
    }
    inps.seekg(head);
    char *chrs=new char[x+1];
    if(chrs==nullptr)
    {
      cout<<"4";
      return 0;
    }
    int  leng=x-head;
    inps.read(chrs,leng);
    enc_or_dec(chrs,argv[4],argv[1],owt,leng,enc_dec,hashed);
    cout<<"1";
    return 0;

}
