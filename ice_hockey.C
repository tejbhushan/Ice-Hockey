#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<graphics.h>
#include<dos.h>
union REGS i,o;
float dbx,dby,lb,txb,tyb,xt,yt,l,dx,dy,xl,yl,xc,yc,xb,yb,j,tx,ty,xm,ym,dmx,dmy,lm;
int x,y,s1=0,s2=0;
char f,f3,a,f2;
void showmouseptr()
{
i.x.ax=1;
int86(0X33,&i,&o);
}
void getmousepos(int *button,int *x,int *y)
{
i.x.ax=3;
int86(0X33,&i,&o);
*button=o.x.bx;
*x=o.x.cx;
*y=o.x.dx;
}

void calcpath()
{
 dx=abs(xc-xb);
 dy=abs(yc-yb);
 if(dx>dy)
 {
  l=dx;
 }
 else
 {
  l=dy;
 }
 dx=(xc-xb)/l;
 dy=(yc-yb)/l;
 xb=xb+0.5;
 yb=yb+0.5;
 circle(xb,yb,15);
 f='t';
}

/*void calcpath2()
{
 dbx=abs(xm-xb);
 dby=abs(ym-yb);
 if(dbx>dby)
 {
  lb=dbx;
 }
 else
 {
  lb=dby;
 }
 dbx=(xm-xb)/lb;
 dby=(ym-yb)/lb;
 xb=xb+0.5;
 yb=yb+0.5;
 circle(xb,yb,15);
 f3='t';
}
*/
/*void calcpathh()
{
 dmx=abs(xm-xb);
 dmy=abs(ym-yb);
 if(dmx>dmy)
 {
  lm=dmx;
 }
 else
 {
  lm=dmy;
 }
 dmx=(xm-xb)/lm;
 dmy=(ym-yb)/lm;
 xm=xm+0.5;
 ym=ym+0.5;
 circle(xm,ym,30);
 f2='t';
 sprintf(f2," YEA %c",f2);
 outtextxy(limx-100,limy-25,msg);
}
*/
void main()
{
 int p,q,r,button,limx,limy,gd=DETECT,gm;
 char msg[20];
 float ss,ssc,A[1][3],B[1][3],C[3][3];
 initgraph(&gd,&gm,"..//BGI");
 limx=getmaxx();
 limy=getmaxy();

 label:

 for(p=0;p<3;p++)
 {
  A[0][p]=0;
  B[0][p]=0;
  for(q=0;q<3;q++)
   B[p][q]=0;
 }
 txb=0;
 tyb=0;
 xt=0;
 yt=0;
 l=0;
 dx=0;
 dy=0;
 xl=0;
 yl=0;
 j=0;
 tx=0;
 ty=0;
 xm=limx/2;
 ym=50;
 xc=limx/2;
 yc=limy-50;
 txb=xb=limx/2;
 yb=limy/2;
 line(0,limy,limx/3,limy);
 line(2*limx/3,limy,limx,limy);
 line(0,0,0,limy);
 line(limx,0,limx,limy);
 line(2*limx/3,0,limx,0);
 line(0,0,limx/3,0);

 while(1)
 {
  cleardevice();
  line(0,limy,limx/3,limy);
  line(2*limx/3,limy,limx,limy);
  line(0,0,0,limy);
  line(limx,0,limx,limy);
  line(2*limx/3,0,limx,0);
  line(0,0,limx/3,0);

  showmouseptr();
  getmousepos(&button,&x,&y);

  if(button==1)
  {
   sprintf(msg," left ptr @ %d,%d",x,y);
   outtextxy(2,2,msg);
   if((y>limy/2)&&(x+30<limx)&&(x-30>0)&&(y+30<limy))
   {
    xc=x;
    yc=y;
   }
   circle(xm,ym,30);
   circle(xc,yc,30);
   circle(xb,yb,15);
  }
  else if(button==2)
  {
   sprintf(msg," right ptr @ %d,%d",x,y);
   outtextxy(2,2,msg);
   break;
  }
  else
  {
   sprintf(msg," only ptr @ %d,%d ",x,y);
   outtextxy(2,2,msg);
   sprintf(msg," score - %d",s1);
   outtextxy(limx-100,25,msg);
   sprintf(msg," score - %d",s2);
   outtextxy(limx-100,limy-25,msg);
   circle(xm,ym,30);
   circle(xc,yc,30);
   circle(xb,yb,15);
  }
  if(pow((xc-xb),2)+pow((yc-yb),2)<=2025)
  {
   f='f';
   sprintf(msg," yea ");
   outtextxy(20,20,msg);
   calcpath();
  }

  if(pow((xm-xb),2)+pow((ym-yb),2)<=2025)
  {
   xt=xc;
   yt=yc;
   ss=((yb-ym)/(xb-xm));
   ssc=ym-xm*(yb-ym)/(xb-xm);
   B[0][0]=txb;
   B[0][1]=tyb;
   B[0][2]=1;
   C[0][0]=(1-ss*ss)/(ss*ss+1);
   C[0][1]=2*ss/(ss*ss+1);
   C[0][2]=0;
   C[1][0]=2*ss/(ss*ss+1);
   C[1][1]=(ss*ss-1)/(ss*ss+1);
   C[1][2]=0;
   C[2][0]=-2*ssc*ss/(ss*ss+1);
   C[2][1]=2*ssc/(ss*ss+1);
   C[2][2]=1;
   for(q=0;q<3;q++)
    for(r=0;r<3;r++)
    {
     A[0][q]+=B[0][r]*C[r][q];
    }
   xc=xb;
   yc=yb;
   xb=A[0][0];
   yb=A[0][1];
   calcpath();
   xc=xt;
   yc=yt;
  }

  if(f=='t')
  {
   txb=xb;
   tyb=yb;
   xb-=dx;
   yb-=dy;
  }
  if((xb-15>limx/3)&&(xb+15<2*limx/3)&&(yb-15<=0))
  {
   s1++;
   cleardevice();
   sprintf(msg," score - %d",s1);
   outtextxy(limx-100,25,msg);
   break;
  }
  else if((xb-15>limx/3)&&(xb+15<2*limx/3)&&(yb+15>=limy))
  {
   s2++;
   cleardevice();
   sprintf(msg," score - %d",s2);
   outtextxy(limx-100,limy-25,msg);
   break;
  }
  else
  {
   if(xb+15>=limx)
   {
    xt=xc;
    yt=yc;
    xc=xb;
    yc=yb;
    xb=txb;
    yb=2*yb-tyb;
    calcpath();
    xc=xt;
    yc=yt;
   }
   else if(xb-15<=0)
   {
    xt=xc;
    yt=yc;
    xc=xb;
    yc=yb;
    xb=txb;
    yb=2*yb-tyb;
    calcpath();
    xc=xt;
    yc=yt;
   }
   else if(yb-15<=0)
   {
    xt=xc;
    yt=yc;
    xc=xb;
    yc=yb;
    xb=2*xb-txb;
    yb=tyb;
    calcpath();
    xc=xt;
    yc=yt;
   }
   else if(yb+15>=limy)
   {
    xt=xc;
    yt=yc;
    xc=xb;
    yc=yb;
    xb=2*xb-txb;
    yb=tyb;
    calcpath();
    xc=xt;
    yc=yt;
   }
   else
   {

   }
  }
  if(xb>limx/2)
   xm=txb-15;
  else
   xm=txb+15;
  if((f2=='t')&&(ym<=limy/2)&&(xm+30<=limx)&&(xm-30<=0)&&(ym-30>=0))
  {
   xm+=dmx;
   ym+=dmy;
   circle(xm,ym,30);
  }

 /* if(pow((xm-xb),2)+pow((ym-yb),2)<=2025)
  {
   f3='f';
   calcpath2();
  }
  if(f3=='t')
  {
   xb-=dbx;
   yb-=dby;
   circle(xb,yb,30);
  }
 */
  delay(1);

 }
 a=getch();
 sprintf(msg," OK ");
 outtextxy(20,20,msg);
 if(a=='a')
 goto label;
}