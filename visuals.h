struct point			//point holds model's vertices
{
	float x; 
	float y; 
	float z; 
};

struct norm				//normal holds model's normals
{
	float x; 
	float y; 
	float z; 
};

struct face				//face holds model's faces
{
	int vtx[3][2]; 
};

struct model			//Struct model holds model tree variables
{
	point obj_points[156];
	face obj_faces[261];
	norm obj_normals[781];
	char Name[40];
	int vertices;
	int faces;
	int normals;
};


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();
////Function for animation

void ReadFile(model*);
//Function for reading a model file

void DisplayModel(model);
// Function for displaying a model

void Keyboard(unsigned char key,int x,int y);
// Function for handling keyboard events.


void DisplayWalker();
// Function for display the walking man

void drawHand();
// Function for displaying hand

void drawLeg();
// Function for displaying leg

void Star(int color);
//Function for displaying a star for crash message

void keimeno(const char* str, float size, int color);
// Function for displaying message
