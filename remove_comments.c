#include "header.h"
extern int cnt;
void *remove_comments(char(*line)[200])
{
        char *p=NULL,*m=NULL;
        for(int i=0;i<cnt;i++)
        {
                int lno=-1,lno1=-1,flag=0;
                p=line[i];
                for(int j=0;p[j]!='\0';j++)
                {
                        int gm=0;
                        if(p[j]=='"')
                        {
                                int k=j+1;
                                m=p;
                                while(m[k]!='\0')
                                {
                                        if(m[k]=='"')
                                                break;
                                        k++;
                                }
                                if(m[k]!='"')
                                        continue;
                                else
                                {
                                        j=k;
                                        continue;
                                }
                        }
                        else if(p[j]=='/'&&p[j+1]=='/')
                        {
                                p[j]='\0';
                                continue;
                        }
                        else if(p[j]=='/' && p[j+1]=='*')
                        {
                                 int r=j+2,d=0;
                                while(p[r]!='\0')
                                {
                                        if(p[r]=='*' && p[r+1]=='/')
                                        {
                                                break;
                                        }
                                        r++;
                                }
                                if(p[r]!='\0'&& p[r+1]=='/')
                                {
                                        memmove(p+j,p+r+2,strlen(p+r+2)+1);
                                        j=j-1;
                                        continue;
                                }
                                else
                                {
                                        m=line[i+1];
                                        while(m[d]!='\0')
                                        {
                                                if(m[d]=='/')
                                                        break;
                                                d++;
                                        }
                                        if(m[d]=='/')
                                        {
                                                memmove(m+0,m+d+1,strlen(m+d+1)+1);
                                                continue;
                                        }
                                        else
                                        {
                                                lno=i;
                                                 for(int k=i+1;k<cnt;k++)
                                                 {
                                                        m=line[k];
                                                        for(int h=0;m[h]!='\0';h++)
                                                        {
                                                                if(m[h]=='*'&&m[h+1]=='/')
                                                                 {
                                                                        lno1=k;
                                                                        flag=1;
                                                                         break;
                                                                 }
                                                        }
                                                        if(flag==1)
                                                                break;
                                                 }
                                        }
                                }
                        }
                        if(flag==1)
                                break;
                   }
                if(lno>=0&&lno1>=0)
                {
                        if(((lno1-lno)-1)!=0)
                        {
                                memmove(line+(lno+1),line+lno1,((cnt-lno1)+1)*sizeof(*line));
                                cnt=cnt-((lno1-lno)-1);
                                line=realloc(line,(cnt*sizeof(*line)));
                        }
                        m=line[lno];
                        int z=0;
                        while(m[z]!='\0')
                        {
                                if(m[z]=='/'&&m[z+1]=='*')
                                        break;
                                z++;
                        }
                        if(m[z]=='/' && m[z+1]=='*')
                        {
                                int w=0;
                                while(m[w]!='\0')
                                {
                                        if(m[w]=='\n')
                                                break;
                                        w++;
                                }
                                memmove(m+z,m+w,strlen(m+w)+1);
                        }
                        m=line[lno+1];
                        z=0;
                        while(m[z]!='\0')
                        {
                                if(m[z]=='*'&&m[z+1]=='/')
                                        break;
                                z++;
                        }
                        if(m[z]=='*'&&m[z+1]=='/')
                        {
                                memmove(m+(z-1),m+z+2,strlen(m+z+2)+1);
                        }
                }
        }
        return line;
}

