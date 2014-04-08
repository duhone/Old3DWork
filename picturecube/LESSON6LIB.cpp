//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LESSON6LIB.h"
#include <stdio.h>								// Header File For Standard Input/Output ( NEW )
#include <stdlib.h>
#include <math.h>
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>		// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The GLaux Library
#include "jpeg.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)

GLuint	texture[6];								// Storage For One Texture ( NEW )
unsigned char *pic[6];
GLuint cubelist;

void createlist()
 {
    glNewList(cubelist,GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, texture[0]);				// Select Our Texture
    glBegin(GL_QUADS);
		// Front Face
		glNormal3f(0.0f,0.0f,-1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
     glEnd();
     glBindTexture(GL_TEXTURE_2D, texture[1]);
     glBegin(GL_QUADS);
		// Back Face
	  	glNormal3f(0.0f,0.0f,1.0f);
     	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
      glEnd();
      glBindTexture(GL_TEXTURE_2D, texture[2]);
      glBegin(GL_QUADS);
		// Top Face
	  	glNormal3f(0.0f,-1.0f,0.0f);
     	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
       glEnd();
       glBindTexture(GL_TEXTURE_2D, texture[3]);
       glBegin(GL_QUADS);
	    	// Bottom Face
	    	glNormal3f(0.0f,1.0f,0.0f);
     	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
       glEnd();
       glBindTexture(GL_TEXTURE_2D, texture[4]);
       glBegin(GL_QUADS);
		// Right face
	    	glNormal3f(-1.0f,0.0f,0.0f);
     	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
      glEnd();
      glBindTexture(GL_TEXTURE_2D, texture[5]);
      glBegin(GL_QUADS);
		// Left Face
		 	glNormal3f(1.0f,0.0f,0.0f);
     glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
	glEnd();
    glEndList();
 }

void pictotex(TPicture* pict,unsigned char* tex,float piccounty,float piccountx,float yinc,float xinc,int texcounty,int texcountx,int numy,int numx,int texsize)
{
  char* picline;
  int curtexcountx;
     float curpiccountx;
  int count2;
  unsigned char* temptex;
  int tempcurpiccountx;
  for(int count = 0;count<numy;count++)
    {
     picline = (char*)pict->Bitmap->ScanLine[(int)(ceil(piccounty))];
     piccounty -= yinc;
     //count3 = 0;
     //piccountx = 0;
     curtexcountx = texcountx;
     curpiccountx = piccountx;
     temptex = (tex+(texsize*4)*abs(texcounty));

     for(count2=0;count2<numx;count2++)
        {
       tempcurpiccountx = (((int)curpiccountx)*3)+2;
       curpiccountx += xinc;
       temptex[curtexcountx] = picline[(tempcurpiccountx)];
       tempcurpiccountx--;
       curtexcountx++;
       temptex[curtexcountx] = picline[(tempcurpiccountx)];
       tempcurpiccountx--;
       curtexcountx++;
       temptex[curtexcountx] = picline[tempcurpiccountx];
       curtexcountx++;
       temptex[curtexcountx] = 1;
       curtexcountx++;
      }
     texcounty++;
    }

}



int LoadGLTextures()								// Load Bitmaps And Convert To Textures
{
   int piccounty,piccountx,texcounty,texcountx,numy,numx;
    AnsiString  names[6];
    TPicture *   temppic[6];
     bool stretch;
    bool hirestex;
    int texsize;
    TRegistry *reg;
  /*char* picline;*/
   unsigned int *clearpic;						// Status Indicator

 AUX_RGBImageRec *TextureImage[6];					// Create Storage Space For The Texture
 memset(TextureImage,0,sizeof(void *)*6);				// Set The Pointer To NULL
 	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
  TJPEGImage *jpeg;
    reg = new TRegistry;
    temppic[0] = new TPicture;
    temppic[1] = new TPicture;
    temppic[2] = new TPicture;
    temppic[3] = new TPicture;
    temppic[4] = new TPicture;
    temppic[5] = new TPicture;
  reg->OpenKey("software",true);
  reg->OpenKey("picube",true);
   if(reg->ValueExists("speed")) speed = reg->ReadInteger("speed");
  else speed = 0;
  if(reg->ValueExists("stretch")) stretch = reg->ReadInteger("stretch");
  else stretch = false;
  if(reg->ValueExists("hirestex")) hirestex = reg->ReadInteger("hirestex");
  else hirestex = false;
  //hirestex = false;
   if(hirestex)
   {
    texsize = 512;
        pic[0] = new unsigned char[(512*2048)];  // STEP 2: SET UP THE COLUMNS
          pic[1] = new unsigned char[(512*2048)];  // STEP 2: SET UP THE COLUMNS
     pic[2] = new unsigned char[(512*2048)];  // STEP 2: SET UP THE COLUMNS
     pic[3] = new unsigned char[(512*2048)];  // STEP 2: SET UP THE COLUMNS
     pic[4] = new unsigned char[(512*2048)];  // STEP 2: SET UP THE COLUMNS
     pic[5] = new unsigned char[(512*2048)];  // STEP 2: SET UP THE COLUMNS

   }
   else
    {
     texsize = 256;
           pic[0] = new unsigned char[(1024*256)];  // STEP 2: SET UP THE COLUMNS
            pic[1] = new unsigned char[(1024*256)];  // STEP 2: SET UP THE COLUMNS
           pic[2] = new unsigned char[(1024*256)];  // STEP 2: SET UP THE COLUMNS
           pic[3] = new unsigned char[(1024*256)];  // STEP 2: SET UP THE COLUMNS
           pic[4] = new unsigned char[(1024*256)];  // STEP 2: SET UP THE COLUMNS
           pic[5] = new unsigned char[(1024*256)];  // STEP 2: SET UP THE COLUMNS
   }



   names[0] = reg->ReadString("pic1");
  names[0] = names[0].LowerCase();
  if((names[0] == NULL) || (names[0] == ""))
   {
    names[0] == "";
   }
  else
   {
    /*TJPEGImage **/jpeg = new TJPEGImage();

   if((names[0][names[0].Length()]) == 'p')
   {
    temppic[0]->LoadFromFile(names[0]);

   }
   else
    {
      jpeg->LoadFromFile(names[0]);

    temppic[0]->Bitmap->Assign(jpeg);
    temppic[0]->Bitmap->Width = jpeg->Width;
    temppic[0]->Bitmap->Height = jpeg->Height;
   }
   delete jpeg;
   float yinc,xinc;
   if(stretch)
    {
     piccounty = temppic[0]->Bitmap->Height;
     piccountx = 0;
     yinc = (piccounty)/(float)texsize;
     xinc = (temppic[0]->Bitmap->Width)/(float)texsize;
     texcounty = 0;
     texcountx = 0;
     numy = texsize;
     numx = texsize;
     piccounty -= 1;
    }
   else
    {
     if(temppic[0]->Bitmap->Height > temppic[0]->Bitmap->Width)
      {
     piccounty = temppic[0]->Bitmap->Height;
     piccountx = 0;
     yinc = (temppic[0]->Bitmap->Height)/(float)texsize;
     xinc = yinc;
     texcountx = ((texsize-temppic[0]->Bitmap->Width*((float)texsize/temppic[0]->Bitmap->Height))*2);
     texcountx -= texcountx%4;
     texcounty = 0;
     numx = temppic[0]->Bitmap->Width*((float)texsize/temppic[0]->Bitmap->Height);
     numy = texsize;
     piccounty -= 1;

      }
      else
       {
    piccounty = temppic[0]->Bitmap->Height;
     piccountx = 0;
    xinc = (temppic[0]->Bitmap->Width)/(float)texsize;
     yinc = xinc;
     texcounty = (texsize-temppic[0]->Bitmap->Height*((float)texsize/temppic[0]->Bitmap->Width))/2;
     texcountx = 0;
     numy = temppic[0]->Bitmap->Height*((float)texsize/temppic[0]->Bitmap->Width);
     numx = texsize;
     piccounty -= 1;

       }
    }
  clearpic = (unsigned int*)pic[0];
  for(int count = 0;count<((texsize*texsize));count+=8)
    {
    clearpic[count] = 0xffffffff;
    clearpic[count+1] = 0xffffffff;
    clearpic[count+2] = 0xffffffff;
    clearpic[count+3] = 0xffffffff;
    clearpic[count+4] = 0xffffffff;
    clearpic[count+5] = 0xffffffff;
    clearpic[count+6] = 0xffffffff;
    clearpic[count+7] = 0xffffffff;
    }
   pictotex(temppic[0],pic[0],piccounty,piccountx,yinc,xinc,texcounty,texcountx,numy,numx,texsize);

   glGenTextures(1,&texture[0]);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, 4,texsize/*temppic[0]->Width*/,texsize/*temppic[0]->Height*/, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

   }



 names[1] = reg->ReadString("pic2");
  names[1] = names[1].LowerCase();
  if((names[1] == NULL) || (names[1] == ""))
   {
    names[1] == "";
   }
  else
   {
    /*TJPEGImage **/jpeg = new TJPEGImage();

   if(names[1][names[1].Length()] == 'p')
   {
    temppic[1]->LoadFromFile(names[1]);

   }
   else
    {
      jpeg->LoadFromFile(names[1]);

    temppic[1]->Bitmap->Assign(jpeg);
    temppic[1]->Bitmap->Width = jpeg->Width;
    temppic[1]->Bitmap->Height = jpeg->Height;
   }
   delete jpeg;
   float yinc,xinc;
   if(stretch)
    {
     piccounty = temppic[1]->Bitmap->Height;
     piccountx = 0;
     yinc = (piccounty)/(float)texsize;
     xinc = (temppic[1]->Bitmap->Width)/(float)texsize;
     texcounty = 0;
     texcountx = 0;
     numy = texsize;
     numx = texsize;
     piccounty -= 1;
    }
   else
    {
     if(temppic[1]->Bitmap->Height > temppic[1]->Bitmap->Width)
      {
     piccounty = temppic[1]->Bitmap->Height;
     piccountx = 0;
     yinc = (temppic[1]->Bitmap->Height)/(float)texsize;
     xinc = yinc;
     texcountx = ((texsize-temppic[1]->Bitmap->Width*((float)texsize/temppic[1]->Bitmap->Height))*2);
     texcountx -= texcountx%4;
     texcounty = 0;
     numx = temppic[1]->Bitmap->Width*((float)texsize/temppic[1]->Bitmap->Height);
     numy = texsize;
     piccounty -= 1;

      }
      else
       {
    piccounty = temppic[1]->Bitmap->Height;
     piccountx = 0;
    xinc = (temppic[1]->Bitmap->Width)/(float)texsize;
     yinc = xinc;
     texcounty = (texsize-temppic[1]->Bitmap->Height*((float)texsize/temppic[1]->Bitmap->Width))/2;
     texcountx = 0;
     numy = temppic[1]->Bitmap->Height*((float)texsize/temppic[1]->Bitmap->Width);
     numx = texsize;
     piccounty -= 1;

       }
    }
 clearpic = (unsigned int*)pic[1];
  for(int count = 0;count<((texsize*texsize));count+=8)
    {
    clearpic[count] = 0xffffffff;
    clearpic[count+1] = 0xffffffff;
    clearpic[count+2] = 0xffffffff;
    clearpic[count+3] = 0xffffffff;
    clearpic[count+4] = 0xffffffff;
    clearpic[count+5] = 0xffffffff;
    clearpic[count+6] = 0xffffffff;
    clearpic[count+7] = 0xffffffff;
    }
     pictotex(temppic[1],pic[1],piccounty,piccountx,yinc,xinc,texcounty,texcountx,numy,numx,texsize);

   glGenTextures(1,&texture[1]);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, 4,texsize/*temppic[0]->Width*/,texsize/*temppic[0]->Height*/, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic[1]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

   }




 names[2] = reg->ReadString("pic3");
  names[2] = names[2].LowerCase();
  if((names[2] == NULL) || (names[2] == ""))
   {
    names[2] == "";
   }
  else
   {
    jpeg = new TJPEGImage();

   if(names[2][names[2].Length()] == 'p')
   {
    temppic[2]->LoadFromFile(names[2]);

   }
   else
    {
      jpeg->LoadFromFile(names[2]);

    temppic[2]->Bitmap->Assign(jpeg);
    temppic[2]->Bitmap->Width = jpeg->Width;
    temppic[2]->Bitmap->Height = jpeg->Height;
   }
   delete jpeg;
   float yinc,xinc;
   if(stretch)
    {
     piccounty = temppic[2]->Bitmap->Height;
     piccountx = 0;
     yinc = (piccounty)/(float)texsize;
     xinc = (temppic[2]->Bitmap->Width)/(float)texsize;
     texcounty = 0;
     texcountx = 0;
     numy = texsize;
     numx = texsize;
     piccounty -= 1;
    }
   else
    {
     if(temppic[2]->Bitmap->Height > temppic[2]->Bitmap->Width)
      {
     piccounty = temppic[2]->Bitmap->Height;
     piccountx = 0;
     yinc = (temppic[2]->Bitmap->Height)/(float)texsize;
     xinc = yinc;
     texcountx = ((texsize-temppic[2]->Bitmap->Width*((float)texsize/temppic[2]->Bitmap->Height))*2);
     texcountx -= texcountx%4;
     texcounty = 0;
     numx = temppic[2]->Bitmap->Width*((float)texsize/temppic[2]->Bitmap->Height);
     numy = texsize;
     piccounty -= 1;

      }
      else
       {
    piccounty = temppic[2]->Bitmap->Height;
     piccountx = 0;
    xinc = (temppic[2]->Bitmap->Width)/(float)texsize;
     yinc = xinc;
     texcounty = (texsize-temppic[2]->Bitmap->Height*((float)texsize/temppic[2]->Bitmap->Width))/2;
     texcountx = 0;
     numy = temppic[2]->Bitmap->Height*((float)texsize/temppic[2]->Bitmap->Width);
     numx = texsize;
     piccounty -= 1;

       }
    }
clearpic = (unsigned int*)pic[2];
  for(int count = 0;count<((texsize*texsize));count+=8)
    {
    clearpic[count] = 0xffffffff;
    clearpic[count+1] = 0xffffffff;
    clearpic[count+2] = 0xffffffff;
    clearpic[count+3] = 0xffffffff;
    clearpic[count+4] = 0xffffffff;
    clearpic[count+5] = 0xffffffff;
    clearpic[count+6] = 0xffffffff;
    clearpic[count+7] = 0xffffffff;
    }
    pictotex(temppic[2],pic[2],piccounty,piccountx,yinc,xinc,texcounty,texcountx,numy,numx,texsize);

   glGenTextures(1,&texture[2]);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glTexImage2D(GL_TEXTURE_2D, 0, 4,texsize,texsize, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic[2]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

   }



 names[3] = reg->ReadString("pic4");
  names[3] = names[3].LowerCase();
  if((names[3] == NULL) || (names[3] == ""))
   {
    names[3] == "";
   }
  else
   {
    jpeg = new TJPEGImage();

   if(names[3][names[3].Length()] == 'p')
   {
    temppic[3]->LoadFromFile(names[3]);

   }
   else
    {
      jpeg->LoadFromFile(names[3]);

    temppic[3]->Bitmap->Assign(jpeg);
    temppic[3]->Bitmap->Width = jpeg->Width;
    temppic[3]->Bitmap->Height = jpeg->Height;
   }
   delete jpeg;
   float yinc,xinc;
   if(stretch)
    {
     piccounty = temppic[3]->Bitmap->Height;
     piccountx = 0;
     yinc = (piccounty)/(float)texsize;
     xinc = (temppic[3]->Bitmap->Width)/(float)texsize;
     texcounty = 0;
     texcountx = 0;
     numy = texsize;
     numx = texsize;
     piccounty -= 1;
    }
   else
    {
     if(temppic[3]->Bitmap->Height > temppic[3]->Bitmap->Width)
      {
     piccounty = temppic[3]->Bitmap->Height;
     piccountx = 0;
     yinc = (temppic[3]->Bitmap->Height)/(float)texsize;
     xinc = yinc;
     texcountx = ((texsize-temppic[3]->Bitmap->Width*((float)texsize/temppic[3]->Bitmap->Height))*2);
     texcountx -= texcountx%4;
     texcounty = 0;
     numx = temppic[3]->Bitmap->Width*((float)texsize/temppic[3]->Bitmap->Height);
     numy = texsize;
     piccounty -= 1;

      }
      else
       {
    piccounty = temppic[3]->Bitmap->Height;
     piccountx = 0;
    xinc = (temppic[3]->Bitmap->Width)/(float)texsize;
     yinc = xinc;
     texcounty = (texsize-temppic[3]->Bitmap->Height*((float)texsize/temppic[3]->Bitmap->Width))/2;
     texcountx = 0;
     numy = temppic[3]->Bitmap->Height*((float)texsize/temppic[3]->Bitmap->Width);
     numx = texsize;
     piccounty -= 1;

       }
    }
  clearpic = (unsigned int*)pic[3];
  for(int count = 0;count<((texsize*texsize));count+=8)
    {
    clearpic[count] = 0xffffffff;
    clearpic[count+1] = 0xffffffff;
    clearpic[count+2] = 0xffffffff;
    clearpic[count+3] = 0xffffffff;
    clearpic[count+4] = 0xffffffff;
    clearpic[count+5] = 0xffffffff;
    clearpic[count+6] = 0xffffffff;
    clearpic[count+7] = 0xffffffff;
    }
    pictotex(temppic[3],pic[3],piccounty,piccountx,yinc,xinc,texcounty,texcountx,numy,numx,texsize);

   glGenTextures(1,&texture[3]);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glTexImage2D(GL_TEXTURE_2D, 0, 4,texsize,texsize, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic[3]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

   }



 names[4] = reg->ReadString("pic5");
  names[4] = names[4].LowerCase();
  if((names[4] == NULL) || (names[4] == ""))
   {
    names[4] == "";
   }
  else
   {
    jpeg = new TJPEGImage();

   if(names[4][names[4].Length()] == 'p')
   {
    temppic[4]->LoadFromFile(names[4]);

   }
   else
    {
      jpeg->LoadFromFile(names[4]);

    temppic[4]->Bitmap->Assign(jpeg);
    temppic[4]->Bitmap->Width = jpeg->Width;
    temppic[4]->Bitmap->Height = jpeg->Height;
   }
   delete jpeg;
   float yinc,xinc;
   if(stretch)
    {
     piccounty = temppic[4]->Bitmap->Height;
     piccountx = 0;
     yinc = (piccounty)/(float)texsize;
     xinc = (temppic[4]->Bitmap->Width)/(float)texsize;
     texcounty = 0;
     texcountx = 0;
     numy = texsize;
     numx = texsize;
     piccounty -= 1;
    }
   else
    {
     if(temppic[4]->Bitmap->Height > temppic[4]->Bitmap->Width)
      {
     piccounty = temppic[4]->Bitmap->Height;
     piccountx = 0;
     yinc = (temppic[4]->Bitmap->Height)/(float)texsize;
     xinc = yinc;
     texcountx = ((texsize-temppic[4]->Bitmap->Width*((float)texsize/temppic[4]->Bitmap->Height))*2);
     texcountx -= texcountx%4;
     texcounty = 0;
     numx = temppic[4]->Bitmap->Width*((float)texsize/temppic[4]->Bitmap->Height);
     numy = texsize;
     piccounty -= 1;

      }
      else
       {
    piccounty = temppic[4]->Bitmap->Height;
     piccountx = 0;
    xinc = (temppic[4]->Bitmap->Width)/(float)texsize;
     yinc = xinc;
     texcounty = (texsize-temppic[4]->Bitmap->Height*((float)texsize/temppic[4]->Bitmap->Width))/2;
     texcountx = 0;
     numy = temppic[4]->Bitmap->Height*((float)texsize/temppic[4]->Bitmap->Width);
     numx = texsize;
     piccounty -= 1;

       }
    }
  clearpic = (unsigned int*)pic[4];
  for(int count = 0;count<((texsize*texsize));count+=8)
    {
    clearpic[count] = 0xffffffff;
    clearpic[count+1] = 0xffffffff;
    clearpic[count+2] = 0xffffffff;
    clearpic[count+3] = 0xffffffff;
    clearpic[count+4] = 0xffffffff;
    clearpic[count+5] = 0xffffffff;
    clearpic[count+6] = 0xffffffff;
    clearpic[count+7] = 0xffffffff;
    }
    pictotex(temppic[4],pic[4],piccounty,piccountx,yinc,xinc,texcounty,texcountx,numy,numx,texsize);

   glGenTextures(1,&texture[4]);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glTexImage2D(GL_TEXTURE_2D, 0, 4,texsize,texsize, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic[4]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

   }




 names[5] = reg->ReadString("pic6");
  names[5] = names[5].LowerCase();
  if((names[5] == NULL) || (names[5] == ""))
   {
    names[5] == "";
   }
  else
   {
    jpeg = new TJPEGImage();

   if(names[5][names[5].Length()] == 'p')
   {
    temppic[5]->LoadFromFile(names[5]);

   }
   else
    {
      jpeg->LoadFromFile(names[5]);

    temppic[5]->Bitmap->Assign(jpeg);
    temppic[5]->Bitmap->Width = jpeg->Width;
    temppic[5]->Bitmap->Height = jpeg->Height;
   }
   delete jpeg;
   float yinc,xinc;
   if(stretch)
    {
     piccounty = temppic[5]->Bitmap->Height;
     piccountx = 0;
     yinc = (piccounty)/(float)texsize;
     xinc = (temppic[5]->Bitmap->Width)/(float)texsize;
     texcounty = 0;
     texcountx = 0;
     numy = texsize;
     numx = texsize;
     piccounty -= 1;
    }
   else
    {
     if(temppic[5]->Bitmap->Height > temppic[5]->Bitmap->Width)
      {
     piccounty = temppic[5]->Bitmap->Height;
     piccountx = 0;
     yinc = (temppic[5]->Bitmap->Height)/(float)texsize;
     xinc = yinc;
     texcountx = ((texsize-temppic[5]->Bitmap->Width*((float)texsize/temppic[5]->Bitmap->Height))*2);
     texcountx -= texcountx%4;
     texcounty = 0;
     numx = temppic[5]->Bitmap->Width*((float)texsize/temppic[5]->Bitmap->Height);
     numy = texsize;
     piccounty -= 1;

      }
      else
       {
    piccounty = temppic[5]->Bitmap->Height;
     piccountx = 0;
    xinc = (temppic[5]->Bitmap->Width)/(float)texsize;
     yinc = xinc;
     texcounty = (texsize-temppic[5]->Bitmap->Height*((float)texsize/temppic[5]->Bitmap->Width))/2;
     texcountx = 0;
     numy = temppic[5]->Bitmap->Height*((float)texsize/temppic[5]->Bitmap->Width);
     numx = texsize;
     piccounty -= 1;

       }
    }
  clearpic = (unsigned int*)pic[5];
  for(int count = 0;count<((texsize*texsize));count+=8)
    {
    clearpic[count] = 0xffffffff;
    clearpic[count+1] = 0xffffffff;
    clearpic[count+2] = 0xffffffff;
    clearpic[count+3] = 0xffffffff;
    clearpic[count+4] = 0xffffffff;
    clearpic[count+5] = 0xffffffff;
    clearpic[count+6] = 0xffffffff;
    clearpic[count+7] = 0xffffffff;
    }
    pictotex(temppic[5],pic[5],piccounty,piccountx,yinc,xinc,texcounty,texcountx,numy,numx,texsize);

   glGenTextures(1,&texture[5]);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glTexImage2D(GL_TEXTURE_2D, 0, 4,texsize,texsize, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic[5]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

   }
  

   /*   	if (TextureImage[5]=LoadBMP("inez6.bmp"))
	{
		Status=TRUE;							// Set The Status To TRUE
        glGenTextures(1, &texture[5]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[5]);
        	// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[5]->sizeX, TextureImage[5]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[5]->data);
        	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
	}

  /* for(int count = 0;count<6;count++)
    {
    if (TextureImage[count])							// If Texture Exists
	{
		if (TextureImage[count]->data)					// If Texture Image Exists
		{
			free(TextureImage[count]->data);				// Free The Texture Image Memory
		}

		free(TextureImage[count]);						// Free The Image Structure
	}
    }*/
 delete reg;
 delete temppic[0];
 delete temppic[1];
 delete temppic[2];
 delete temppic[3];
 delete temppic[4];
 delete temppic[5];
 return true;								// Return The Status
 }



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)	// Resize And Initialize The GL Window
{
	if (height==0)					// Prevent A Divide By Zero By
	{
		height=1;				// Making Height Equal One
	}

	glViewport(0, 0, width, height);		// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();				// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);			// Select The Modelview Matrix
	glLoadIdentity();				// Reset The Modelview Matrix
}

int InitGL(GLvoid)					// All Setup For OpenGL Goes Here
{
  if (!LoadGLTextures())							// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;							// If Texture Didn't Load Return FALSE ( NEW )
	}
  glFrontFace(GL_CCW);

  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);						// Enable Texture Mapping ( NEW )

  glShadeModel(GL_FLAT);			// Enables Smooth Shading

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// Black Background

  glClearDepth(1.0f);				// Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
  glEnable(GL_LIGHTING);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
  cubelist = glGenLists(1);
  createlist();
    GLfloat ambientlight[] = {0.0f,0.0f,0.0f,1.0f};
     GLfloat diffuselight[] = {1.0f,1.0f,1.0f,1.0f};
   GLfloat white[] = {1.0f,1.0f,1.0f,1.0f};
     GLfloat lightpos[] = {0.0f,0.0f,-100.0f,0.0f};
    	glLoadIdentity();					// Reset The Current Modelview Matrix
   
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientlight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuselight);
    glEnable(GL_LIGHT0);
	  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,white);
  return TRUE;						// Initialization Went OK
}

int DrawGLScene(GLvoid)						// Here's Where We Do All The Drawing
{
    static GLfloat	xrot;									// X Rotation ( NEW )
    static GLfloat	yrot;									// Y Rotation ( NEW )
    static GLfloat	zrot;									// Z Rotation ( NEW )
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
 	glLoadIdentity();					// Reset The Current Modelview Matrix
   glTranslatef(0.0f,0.0f,-5.0f);						// Move Into The Screen 5 Units
    glRotatef(xrot,1.0f,0.0f,0.0f);						// Rotate On The X Axis
	glRotatef(yrot,0.0f,1.0f,0.0f);						// Rotate On The Y Axis
	//glRotatef(zrot,0.0f,0.0f,1.0f);						// Rotate On The Z Axis
    glCallList(cubelist);
    xrot+=0.02*speed;								// X Axis Rotation
	yrot+=0.04*speed;								// Y Axis Rotation
	//zrot+=0.000*speed;


	return TRUE;						// Everything Went OK
}

GLvoid KillGLWindow(HGLRC hRC,HDC hDC,HWND hWnd)					// Properly Kill The Window
{
  glDeleteLists(cubelist,1);
  if (hRC)						// Do We Have A Rendering Context?
	{
     if (!wglMakeCurrent(NULL,NULL))			// Are We Able To Release The DC And RC Contexts?
		{
          	MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
     if (!wglDeleteContext(hRC))			// Are We Able To Delete The RC?
		{
          	MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;					// Set RC To NULL
	}

  if (hDC && !ReleaseDC(hWnd,hDC))			// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;					// Set DC To NULL
	}
  

}

BOOL CreateGLWindow(HWND hWnd,HDC *hDC,HGLRC	*hRC,int width, int height, int bits, bool *fullscreenflag)
{
  GLuint		PixelFormat;

  if (!((*hDC)=GetDC(hWnd)))						// Did We Get A Device Context?
	{
		KillGLWindow((*hRC),(*hDC),hWnd);						// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;						// Return FALSE
	}
    bits = GetDeviceCaps(hDC,BITSPIXEL);
    static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,							// Version Number
		PFD_DRAW_TO_WINDOW |					// Format Must Support Window
		PFD_SUPPORT_OPENGL |					// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,					// Must Support Double Buffering
		PFD_TYPE_RGBA,						// Request An RGBA Format
		bits,							// Select Our Color Depth
		0, 0, 0, 0, 0, 0,					// Color Bits Ignored
		0,							// No Alpha Buffer
		0,							// Shift Bit Ignored
		0,							// No Accumulation Buffer
		0, 0, 0, 0,						// Accumulation Bits Ignored
		16,							// 16Bit Z-Buffer (Depth Buffer)
		0,							// No Stencil Buffer
		0,							// No Auxiliary Buffer
		PFD_MAIN_PLANE,
        0,							// Reserved
		0, 0, 0							// Layer Masks Ignored
	};
 
   if (!(PixelFormat=ChoosePixelFormat((*hDC),&pfd)))			// Did Windows Find A Matching Pixel Format?
	{
     KillGLWindow((*hRC),(*hDC),hWnd);						// Reset The Display
     MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
     return FALSE;						// Return FALSE
	}
   if(!SetPixelFormat((*hDC),PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
     KillGLWindow((*hRC),(*hDC),hWnd);						// Reset The Display
     MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
     return FALSE;						// Return FALSE
	}
   if (!((*hRC)=wglCreateContext((*hDC))))				// Are We Able To Get A Rendering Context?
	{
	   	KillGLWindow((*hRC),(*hDC),hWnd);						// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;						// Return FALSE
	}
   if(!wglMakeCurrent((*hDC),(*hRC)))					// Try To Activate The Rendering Context
	{
	  	KillGLWindow((*hRC),(*hDC),hWnd);						// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;						// Return FALSE
	}
   ShowWindow(hWnd,SW_SHOW);					// Show The Window
   SetForegroundWindow(hWnd);					// Slightly Higher Priority
   SetFocus(hWnd);							// Sets Keyboard Focus To The Window
   ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

   if (!InitGL())							// Initialize Our Newly Created GL Window
	{
	 	KillGLWindow((*hRC),(*hDC),hWnd);						// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;						// Return FALSE
	}
   	return TRUE;							// Success
}


