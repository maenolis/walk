#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>

#include "gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

model md;							//Montelo gia na krathsei tis metavlhtes provolhs tou dentrou
float xAngle = 0.0f;						//Arxikopoihsh gwnias "x" theashs ths skhnhs
float yAngle = 10.0f;						//Arxikopoihsh gwnias "y" theashs ths skhnhs
float zoom = -20.0f;						//Arxikopoihsh zoom theashs ths skhnhs
float v = -0.5f;							//Taxuthta paraskhniou
float dt = 0.05f;						//Metavlhth xronou
float dtHolder;							//Metavlhth xronou gia thn paush/epenarksh
float xPositionDentro1 = -50.0f;					//thesh gia dentro 1
float xPositionDentro2 = -40.0f;					//thesh gia dentro 2
float xPositionDentro3 = -30.0f;					//thesh gia dentro 3
float xPositionDentro4 = -20.0f;					//thesh gia dentro 4
float xPositionPagkaki = - 6.0f;					//thesh gia pagkaki
float xPositionBackGround = -100.0f;				//thesh gia 1 apo ta 12 motiva dentrwn
GLUquadricObj *quadObj = gluNewQuadric();			//Arxikopoihsh metavlhths gia ta kulindrika kommatia (gkri tmhmata anthrwpou)
float limbAngle = 0.0f;						//Metavlhth gia thn gwnia twn akrwn tou anthrwpou
float radiusSpeed = 7.5f;					//Gwniakh taxythta twn akrwn
bool crashed = false;						//Metavlhth sugkroushs
float yWalker = -0.35f;						//Thesh ston aksona y tou anthrwpou
float yWalkerSpeed = 0.0f;					//Taxuthta ston aksona y tou anthrwpou
float currentCrashedTime = 0.0f;					//Metavlhth gia thn metrhsh diarkeias tou mhnumatos "crashed!!"
const float crashedTime = 50.0f;					//Diarkeia tou mhnumatos
const int backGroundsNum = 12;						//Metavlhth arithmoy motivwn paraskhniou


using namespace std;


void Render()
{    
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														   // and the depth buffer
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	  
	glEnable( GL_NORMALIZE );

	if (crashed){
		Star(2);								//provolh asteriou gia to mhnuma
		keimeno("crash!!", 0.2, 1);				//provolh keimenou gia to mhnuma
		currentCrashedTime += 0.05;				//metrhsh diarkeias mhnumatos
		if (currentCrashedTime > crashedTime) {
			crashed = false;				//arxikopoihsh ths crashed
			currentCrashedTime = 0.0;			//arxikopoihsh tou metrhth diarkeias
		}
	}
	else{

  
      
		glTranslatef(0.0,0.0,zoom);					//Estiash gia na petuxoume thn allagh analoga me thn entolh tou xrhsth
		glRotatef(xAngle,0,1,0);					//Peristrofh gia na petuxoume thn allagh gwnias analoga me thn entolh tou xrhsth
		glRotatef(yAngle,1,0,0);					//Peristrofh gia na petuxoume thn allagh gwnias analoga me thn entolh tou xrhsth
		glScalef(0.95,0.95,0.95);					//Ena scaling gia na fainetai olh h skhnhs

	  

		DisplayWalker();						//provolh anthrwpou
		  

  //(02)             //when disabling depth test this is rendered first
  
  
	  //dhmiourgia 12 mitivwn gia ta dentra kai ta pagkakia
	for (int i = 0; i < backGroundsNum; i++){
		glPushMatrix();
		glTranslatef(xPositionBackGround + 50*i,0,0);	//metafora sto antistoixo shmeio gia to sugkekrimeno motivo

		glPushMatrix();							//pagkaki katw kommati
		glTranslatef(xPositionPagkaki,0.8,-11);
		glScalef(0.8,0.1,0.4);
		glColor3f(0.4,0.4,0.4);
		glutSolidCube(5.0);
		glPopMatrix();

		glPushMatrix();							//pagkaki panw kommati
		glTranslatef(xPositionPagkaki,1.3,-12);
		glScalef(0.8,0.5,0.05);
		glColor3f(0.4,0.4,0.4);
		glutSolidCube(5.0);
		glPopMatrix();
		
		glPushMatrix();							//dentro 1
		glTranslatef(xPositionDentro1,-0.2,-14);
		glScalef(10,10,10);
		glColor3f(0.0,1.0,0.5);
		DisplayModel(md);
		glPopMatrix();
	
		glPushMatrix();							//dentro 2
		glTranslatef(xPositionDentro2,-0.2,-14);
		glScalef(5,20,5);
		glColor3f(0.0,1.0,0.5);
		DisplayModel(md);
		glPopMatrix();
	  
		glPushMatrix();							//dentro 3
		glTranslatef(xPositionDentro3,-0.15,-14);
		glScalef(14,8,14);
		glColor3f(0.0,1.0,0.5);
		DisplayModel(md);
		glPopMatrix();
	  
		glPushMatrix();							//dentro 4
		glTranslatef(xPositionDentro4,-0.12,-14);
		glScalef(18,6,18);
		glColor3f(0.0,1.0,0.5);
		DisplayModel(md);
		glPopMatrix();


		glPushMatrix();							//empodio
		glTranslatef(-20,1,0);
		glColor3f(0.0,1.0,1.0);
		glScalef(0.5,1,3);
		glutSolidCube(2);
		glPopMatrix();
	  
		glPopMatrix();
	}
  

	glPushMatrix();							//dromos
	glScalef(100,0.01,2);
	glColor3f(0.6,0.6,0.6);
	glutSolidCube(10.0);
	glPopMatrix();

	glPushMatrix();							//pezodromio
	glTranslatef(0,0.1,-12.5);
	glScalef(100,0.02,0.5);
	glColor3f(0.65,0.16,0.16);
	glutSolidCube(10.0);
	glPopMatrix();
	}

	glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0 ,0 , w ,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  gluPerspective(60.0, (float)w/(float)h, 1, 500.0);
}

void Idle()
{

	// an den egine sugkroush kane ta preponta
	if (!crashed) {
		yWalker += yWalkerSpeed*dt;				//vriskoume thn thesh ston y
		
		if (yWalker > -0.35f) {
			yWalkerSpeed -= dt/2.5f;				//an exei ginei alma meiwse thn taxuthta ston y
		}
		else if (yWalkerSpeed < 0.0f){				//an exei ftasei sto edafos h y taxuthta ginetai 0
			yWalkerSpeed = 0.0f;
		}
		
		for(int i = 0; i < backGroundsNum; i++) {				//elegxos me ola ta empodia apo ta motiva
			if (xPositionBackGround + 50.0*i -20.0f > -1.0f && xPositionBackGround + 50.0f*i -20.0f < 1.0f && yWalker < 1.0f){
				crashed = true;				//an o anthrwpos epese se empodio
				xPositionBackGround -= 2.0f;		//metakinhse to paraskhnio wste na sunexisei thn kinhsh meta to mhnuma sugkroushs
				break;
			}
		}

		if (limbAngle > 30.0f || limbAngle < -30.0f) {		//molis ftasoun ta akra sthn megisth gwnia
			radiusSpeed = -radiusSpeed;			//anestrepse thn kinhsh
		}
		limbAngle += radiusSpeed*dt;				//upologise thn gwnia twn akrwn

		if (xPositionBackGround < -250.0f) {			//metavlhth kinhshs twn 6 motivwn tou paraskhniou
			xPositionBackGround = -100.0f;			// thn kratame se kapoio euros gia na ginetai
		}							//pseudesthisi oti einai ateleiwto to paraskhnio
		else {
			xPositionBackGround += dt*v;			//kai thn metakinoume sto epitrepto euros
		}
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'q' :						//Periptwsh telous paixnidiou
		exit(0);
		break;
	
	case 'z' :						//Periptwsh aukshshs zoom	
		if (zoom < -10.0f){
			zoom+=1.0f;
			cout << "z" << zoom << endl;
		}
		break;
	
	case 'x' :						//Periptwsh meiwshs zoom
		if (zoom > -50.0f){
			zoom-=1.0f;
			cout << "x" << zoom << endl;
		}
		break;
	
	case 'w' : 							//Periptwsh aukshshs gwnias theashs ston y
		yAngle+=1.0f;
		break;
	
	case 's' :						//Periptwsh meiwshs gwnias  ston y	
		yAngle-=1.0f;
		break;

	case 'd' : 						//Periptwsh aukshshs gwnias theashs ston x
		xAngle-=1.0f;	
		break;
	
	case 'a' :						//Periptwsh meiwshs gwnias theashs ston x	
		xAngle+=1.0f;
		break;
	
	case 'i' :						//Periptwsh aukshshs tou vhmatos xronou kata dt
		if (dt < 0.10f && dt > 0.0f) {
			dt+=0.01f;
		}
		break;
	
	case 'u' :						//Periptwsh meiwshs tou vhmatos xronou kata dt
		if (dt > 0.02f) {
			dt-=0.01f;
		}
		break;
	
	case 'j' :						//Periptwsh almatos
		if (yWalkerSpeed == 0.0f) {
			yWalkerSpeed = 1.7f;
		}
		break;
	
	case 'h' :						//Periptwsh paushs/enarkshs
		if (dt != 0.0f) {
			dtHolder = dt;
			dt = 0.0f;
		}
		else{
			dt = dtHolder;
		}
		break;
	
	default : break;
	}

	glutPostRedisplay();

}


void Setup()  // TOUCH IT !! 
{ 
	ReadFile(&md);			//Klhsh anagnwshs tou montelou md(dentrou)

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1.0);
    
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] =  { (-200.0, 200.0, 50.0, 0.5), (0.0, 200.0, 50.0, 0.5) , (200.0, 200.0, 50.0, 0.5)};
	//3 phges fwtos!!panw aristera//panw//panw deksia
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void ReadFile(model *md)
{
	char a[60], * stra;
	int cv=0,cf=0,cvn=0;									//Arxikopoihsh metrhtwn vertices, faces kai normals
	ifstream obj_file("tree.obj");                   //Anoigma tou arxeiou tree.obj
   
	if (obj_file.fail()){							//Periptwsh oxi kalou anoigmatos
		exit(1);
	}
	obj_file >> a;
	while(obj_file.good()){
		if(!strcmp(a,"v")){
			obj_file >> md->obj_points[cv].x;		//Krathma twn vertices tou object
			obj_file >> md->obj_points[cv].y;
			obj_file >> md->obj_points[cv].z;
			cv++;
		}
		else if(!strcmp(a, "g")){
			obj_file >> md->Name;					//Krathma tou onomatos tou object
		}
		else if(!strcmp(a,"f")) {
		  obj_file >> a;
		  stra= strtok (a,"/");
		  md->obj_faces[cf].vtx[0][0] = atoi(stra);	//Krathma antistoixou vertice
		  stra= strtok (NULL,"/");
		  md->obj_faces[cf].vtx[0][1] = atoi(stra); //Krathma antistoixou normal
		  
		  obj_file >> a;
		  stra= strtok (a,"/");
		  md->obj_faces[cf].vtx[1][0] = atoi(stra); //Krathma antistoixou vertice
		  stra= strtok (NULL,"/");
		  md->obj_faces[cf].vtx[1][1] = atoi(stra); //Krathma antistoixou normal

		  obj_file >> a;
		  stra= strtok (a,"/");
		  md->obj_faces[cf].vtx[2][0] = atoi(stra); //Krathma antistoixou vertice
		  stra= strtok (NULL,"/");
		  md->obj_faces[cf].vtx[2][1] = atoi(stra); //Krathma antistoixou normal
          cf++;	
	  }
		else if(!strcmp(a,"vn")){
			obj_file >> md->obj_normals[cvn].x; ////Krathma twn normals tou object
			obj_file >> md->obj_normals[cvn].y;
			obj_file >> md->obj_normals[cvn].z;
			cvn++;
		}
		obj_file >> a;
	}
	md->vertices = cv;							//Krathma tou arithmou twn vertices
	md->faces = cf;								//Krathma tou arithmou twn faces
	md->normals = cvn;							//Krathma tou arithmou twn normals
	cout<<cv<<" : vertices read"<<endl;
	cout<<cf<<" : faces read"<<endl;
	cout<<cvn<<" : normals read"<<endl;
	obj_file.close();							//Kleisimo tou arxeiou
}




void DisplayModel(model md) {

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < md.faces; i++) {
		//normal x, y, z
		glNormal3f(md.obj_normals[md.obj_faces[i].vtx[0][1]-1].x, md.obj_normals[md.obj_faces[i].vtx[0][1]-1].y, md.obj_normals[md.obj_faces[i].vtx[0][1]-1].z);
		//vertice x, y, z
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0][0]-1].x,md.obj_points[md.obj_faces[i].vtx[0][0]-1].y,md.obj_points[md.obj_faces[i].vtx[0][0]-1].z);
		//normal x, y, z
		glNormal3f(md.obj_normals[md.obj_faces[i].vtx[1][1]-1].x,md.obj_normals[md.obj_faces[i].vtx[1][1]-1].y, md.obj_normals[md.obj_faces[i].vtx[1][1]-1].z);
		//vertice x, y, z
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1][0]-1].x,md.obj_points[md.obj_faces[i].vtx[1][0]-1].y,md.obj_points[md.obj_faces[i].vtx[1][0]-1].z);
		//normal x, y, z
		glNormal3f(md.obj_normals[md.obj_faces[i].vtx[2][1]-1].x,md.obj_normals[md.obj_faces[i].vtx[2][1]-1].y, md.obj_normals[md.obj_faces[i].vtx[2][1]-1].z);
		//vertice x, y, z
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2][0]-1].x,md.obj_points[md.obj_faces[i].vtx[2][0]-1].y,md.obj_points[md.obj_faces[i].vtx[2][0]-1].z);
	}

	glEnd();
	glPopMatrix();
}

void DisplayWalker() 
{
	glPushMatrix();
	  glTranslatef(0,yWalker,0);
	  glPushMatrix();						//laimos
      glColor3f(1.0,1.0,1.0);
	  glTranslatef(0,5.5,0);
	  glScalef(0.1,1,0.1);
	  glRotatef(90,1,0,0);
	  gluCylinder(quadObj, 2, 2, 2.9, 20, 20);
      glPopMatrix();

	  glPushMatrix();						//swma
      glColor3f(1.0,1.0,1.0);
	  glTranslatef(0,4.5,0);
	  glScalef(0.1,1,0.3);
	  glRotatef(90,1,0,0);
	  gluCylinder(quadObj, 2, 2, 2.0, 20, 20);
      glPopMatrix();

	  glPushMatrix();						//isxua
      glColor3f(1.0,1.0,1.0);
	  glTranslatef(0,2.5,-0.58);
	  glScalef(0.1,0.1,0.8);
	  gluCylinder(quadObj, 2, 2, 1.5, 20, 20);
      glPopMatrix();

	  glPushMatrix();
      glColor3f(1.0,1.0,1.0);			//kleides
	  glTranslatef(0,4.48,-0.75);
	  glScalef(0.1,0.1,1);
	  gluCylinder(quadObj, 2, 2, 1.5, 20, 20);
      glPopMatrix();

	  glPushMatrix();					//deksi podi
      glTranslatef(0,2.5,0.6);
	  glRotatef(90,1,0,0);
	  glRotatef(-limbAngle, 0, 1, 0);
	  drawLeg();
      glPopMatrix();

	  glPushMatrix();					//aristero podi
      glTranslatef(0,2.5,-0.6);
	  glRotatef(90,1,0,0);
	  glRotatef(limbAngle, 0, 1, 0);
	  drawLeg();
      glPopMatrix();
	  
	  glPushMatrix();					//deksi xeri
      glTranslatef(0,4.4,0.85);
	  glRotatef(90,1,0,0);
	  glRotatef(limbAngle, 0 , 1, 0);
	  drawHand();
	  glPopMatrix();
	  
	  glPushMatrix();					//aristero xeri
      glTranslatef(0,4.4,-0.85);
	  glRotatef(90,1,0,0);
	  glRotatef(-limbAngle, 0 , 1, 0);
	  drawHand();
	  glPopMatrix();

	
	  glPushMatrix();					//kefali
      glColor3f(1.0,0.0,0.0);
	  glTranslatef(0,5.65,0.0);
	  glRotatef(90,1,0,0);
	  glutSolidSphere(0.45,20,20);
      glPopMatrix();

	  glPopMatrix();
}

void drawHand() {
	glPushMatrix();					//kulindriko komati
      glColor3f(1.0,1.0,1.0);
	  glTranslatef(0,0,0);
	  glScalef(0.1,0.1,0.55);
	  glRotatef(90,0,0,1);
	  gluCylinder(quadObj, 2, 2, 2, 20, 20);
      glPopMatrix();

	  glPushMatrix();					//panw mpala
      glColor3f(1.0,0.0,0.0);
	  glRotatef(90,1,0,0);
	  glutSolidSphere(0.25,20,20);
      glPopMatrix();

	  glPushMatrix();					//katw mpala
      glColor3f(1.0,0.0,0.0);
	  glTranslatef(0,0,1.1);
	  glRotatef(90,1,0,0);
	  glutSolidSphere(0.25,20,20);
      glPopMatrix();

}

void drawLeg() {
	glPushMatrix();					//kulindriko komati
      glColor3f(1.0,1.0,1.0);
	  glTranslatef(0,0,0);
	  glScalef(0.1,0.1,0.85);
	  glRotatef(90,0,0,1);
	  gluCylinder(quadObj, 2, 2, 2, 20, 20);
      glPopMatrix();

	  glPushMatrix();					//panw mpala
      glColor3f(1.0,0.0,0.0);
	  glRotatef(90,1,0,0);
	  glutSolidSphere(0.25,20,20);
      glPopMatrix();

	  glPushMatrix();					//katw mpala
      glColor3f(1.0,0.0,0.0);
	  glTranslatef(0,0,1.8);
	  glRotatef(90,1,0,0);
	  glutSolidSphere(0.25,20,20);
      glPopMatrix();

}

void Star(int color)						//Sunarthsh pou sxhmatizei to asteri pisw apo to mhnuma crashed
{											//Emmesa xrhsimopoihthikan ta shmeia 2 kuklwn me diafora 30 moires apo
	glPushMatrix();							//komvo se komvo
	  if (color == 1) {
		  glColor3f(1,0,0);
	  }
	  else if (color == 2) {
		  glColor3f(0,1,0);
	  }
	  else if (color == 3) {
		  glColor3f(0,0,1);
	  }
	  glTranslatef(0.0,0.0,-150.0);
	  glBegin(GL_POLYGON);
	    glVertex3f(50.0,0.0,1.0);
	    glVertex3f(86.6,50.0,1.0);
	    glVertex3f(25.0,43.3,1.0);
	    glVertex3f(0.0,100.0,1.0);
	    glVertex3f(-25.0,43.3,1.0);
	    glVertex3f(-86.6,50.0,1.0);
	    glVertex3f(-50.0,0.0,1.0);
	    glVertex3f(-86.6,-50.0,1.0);
	    glVertex3f(-25.0,-43.3,1.0);
	    glVertex3f(0.0,-100.0,1.0);
	    glVertex3f(25.0,-43.3,1.0);
	    glVertex3f(86.6,-50.0,1.0);
	  glEnd();
	glPopMatrix();
}

void keimeno(const char *str,float size, int color)				//Sunarthsh parousiashs keimenou (str) se megethos size
{																//kai xrwma kokkino, prasino kai mple (1,2,3)
	glPushMatrix();
	if (color == 1) {
		  glColor3f(1,0,0);
	  }
	  else if (color == 2) {
		  glColor3f(0,1,0);
	  }
	  else if (color == 3) {
		  glColor3f(0,0,1);
	  } 
	glTranslatef(-35,0,-149);
	glScalef(size,size,size);
	  for (int i=0;i < (int)strlen(str);i++){
		  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	  }
	glPopMatrix();

}