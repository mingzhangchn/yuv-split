#include<stdio.h>
#include <string.h>
#include <stdlib.h>
int simplest_yuv420_split(char *url, int w, int h,int num){  
    FILE *fp=fopen(url,"rb+");  
    FILE *fp1=fopen("output_420_y.y","wb+");  
    FILE *fp2=fopen("output_420_u.y","wb+");  
    FILE *fp3=fopen("output_420_v.y","wb+");  
  
    unsigned char *pic=(unsigned char *)malloc(w*h*3/2);  
    int i = 0;
    for(i=0;i<num;i++){  
  
        fread(pic,1,w*h*3/2,fp);  
        //Y  
        fwrite(pic,1,w*h,fp1);  
        //U  
        fwrite(pic+w*h,1,w*h/4,fp2);  
        //V  
        fwrite(pic+w*h*5/4,1,w*h/4,fp3);  
    }  
  
    free(pic);  
    fclose(fp);  
    fclose(fp1);  
    fclose(fp2);  
    fclose(fp3);  
  
    return 0;  
}  

int simplest_yuv2_split(char *url, int w, int h,int num){  
    FILE *fp=fopen(url,"rb+");  
    FILE *fp1=fopen("output_yuv2_y.y","wb+");  
    FILE *fp2=fopen("output_yuv2_u.y","wb+");  
    FILE *fp3=fopen("output_yuv2_v.y","wb+");  
  
    unsigned char *pic=(unsigned char *)malloc(w*h*2);  
    int i = 0;
    for(i=0;i<num;i++){  
  
        fread(pic,1,w*h*2,fp);  
        int line = 0;
        for(line = 0; line < h; ++line){
            int j = 0;
            for(j = line*w*2; j < w*2 + line*w*2; j+=2 ){
                fwrite(&pic[j],1,1,fp1);//y
                if(j/2%2){
                    fwrite(&pic[j+1],1,1,fp3); //v
                }
                else{
                    fwrite(&pic[j+1],1,1,fp2);//u 
                }
            }
        }
    }  
  
    free(pic);  
    fclose(fp);  
    fclose(fp1);  
    fclose(fp2);  
    fclose(fp3);  
  
    return 0;  
}  


int main(){
    simplest_yuv2_split("./out.yuv", 640, 480,1);
    
    return 0;
}
