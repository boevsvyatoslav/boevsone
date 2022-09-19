#include <stdlib.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void dfs(int i,int ii,int w,int ih,unsigned char* F, int* D,int num)
{
    D[w*i+ii]=num;
    if(i>0 && i<ih && ii>2 && ii<w)
    {
        if((abs(F[w*i+ii]-F[w*i+ii-2])<=63)&&(D[w*i+ii-2]==0))
            dfs(i,ii-2,w,ih,F,D,num);
    }
    if(i>2 && i<ih+2 && ii>-1 && ii<w-1)
    {
        if((abs(F[w*i+ii]-F[w*(i-2)+ii+1])<=63)&&(D[w*(i-2)+ii+1]==0))
            dfs(i-2,ii+1,w,ih,F,D,num);
    }
    if(i>-2 && i<ih-2 && ii>-1 && ii<w-1)
    {
        if((abs(F[w*i+ii]-F[w*(i+2)+ii+1])<=63)&&(D[w*(i+2)+ii+1]==0))
            dfs(i+2,ii+1,w,ih,F,D,num);
    }
}
int main()
{
    int w,ih,n,num=0,check=0,c;
    unsigned char *data = stbi_load("hampster.png", &w, &ih, &n, 0);
    if (data == NULL)
    {
        printf("can't read\n");
        return -1;
    }
    unsigned char* F = (unsigned char*)malloc(ih*w*sizeof(unsigned char));
    int i,ii,k=0;
    for (i=0; i<ih*w*n; i=i+n)
    {
        F[k]=0.34375*data[i]+0.5*data[i+1]+0.15625*data[i+2];
        k++;
    }
    for (i=2;i<=ih-2;i++)
    {
        for (ii=2;ii<=w-2;ii++)
        {
            if(F[w*i+ii]>150)F[w*i+ii]=255;
            if(F[w*i+ii]<97)F[w*i+ii]=0;
        }
    }
    int* D=(int*)malloc((w*ih)*sizeof(int));//it dislikes recursion
    for(i=0;i<w*ih;i++)
        D[i]=0;
    for (i=1;i<ih;i++)
    {
        for (ii=1;ii<w;ii++)
        {
            if(D[w*i+ii]==0)
            {
                num++;
                dfs(i,ii,w,ih,F,D,num);
            }
        }
    }
    unsigned char* end=(unsigned char*)malloc(w*ih*n*sizeof(unsigned char));
    k=0;
    for (i=0; i<ih*w*n; i=i+n)
    {
        c=D[k]%10+D[k]%30;
        end[i]=5*c-27;
        end[i+1]=7*c+1;
        end[i+2]=2*c+51;
        end[i+3]=255;
        k++;
    }

    stbi_write_png("DividedHampster.png", w, ih, n, end, 0);
    stbi_image_free(data);
    stbi_image_free(F);
    stbi_image_free(end);
    return 0;
}
