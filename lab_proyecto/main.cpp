#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

CCamera objCamera;
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

//Para el globo//////
GLUquadric *quad;
/////////////

//texturas skybox
CTexture text_arriba;
CTexture text_abajo;
CTexture text_izquierda;	
CTexture text_derecha;	
CTexture text_frente;	
CTexture text_atras;

//texturas casa
CTexture ladrillo;
CTexture ladrillo_f;
CTexture pared_der;
CTexture pared_izq;
CTexture gar_frente;
CTexture teja;
CTexture tapiz;
CTexture tapiz_F;
CTexture tapiz_D;
CTexture piso;
CTexture tapete;
CTexture mapa;
CTexture asfalto;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CFiguras fig7; //Para el monito

//Figuras de 3D Studio
CModel soporte;

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, Position2);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On

	text_atras.LoadTGA("posz.tga"); //textura del cubo
	text_atras.BuildGLTexture();
	text_atras.ReleaseImage();

	text_frente.LoadTGA("negz.tga"); //textura del cubo
	text_frente.BuildGLTexture();
	text_frente.ReleaseImage();

	text_izquierda.LoadTGA("negx.tga"); //textura del cubo
	text_izquierda.BuildGLTexture();
	text_izquierda.ReleaseImage();

	text_derecha.LoadTGA("posx.tga"); //textura del cubo
	text_derecha.BuildGLTexture();
	text_derecha.ReleaseImage();

	text_arriba.LoadTGA("posy.tga"); //textura del cubo
	text_arriba.BuildGLTexture();
	text_arriba.ReleaseImage();

	text_abajo.LoadTGA("negy.tga"); //textura del cubo
	text_abajo.BuildGLTexture();
	text_abajo.ReleaseImage();

	ladrillo_f.LoadTGA("br3.tga"); //textura de la fachada FRENTE
	ladrillo_f.BuildGLTexture();
	ladrillo_f.ReleaseImage();

	ladrillo.LoadTGA("br.tga"); //textura de la fachada 
	ladrillo.BuildGLTexture();
	ladrillo.ReleaseImage();

	pared_der.LoadTGA("br_der.tga"); //textura de la fachada 
	pared_der.BuildGLTexture();
	pared_der.ReleaseImage();

	pared_izq.LoadTGA("br_izq.tga"); //textura de la fachada 
	pared_izq.BuildGLTexture();
	pared_izq.ReleaseImage();

	teja.LoadTGA("tile2.tga"); //textura de la fachada
	teja.BuildGLTexture();
	teja.ReleaseImage();

	tapiz.LoadTGA("tapiz.tga"); //textura de la fachada
	tapiz.BuildGLTexture();
	tapiz.ReleaseImage();

	tapiz_F.LoadTGA("tapiz_F.tga"); //textura de la fachada
	tapiz_F.BuildGLTexture();
	tapiz_F.ReleaseImage();

	tapiz_D.LoadTGA("tapiz_D.tga"); //textura de la fachada
	tapiz_D.BuildGLTexture();
	tapiz_D.ReleaseImage();

	piso.LoadTGA("piso_mad.tga"); //textura de la fachada
	piso.BuildGLTexture();
	piso.ReleaseImage();

	tapete.LoadTGA("tapete.tga"); //textura de la fachada
	tapete.BuildGLTexture();
	tapete.ReleaseImage();

	mapa.LoadTGA("map.tga"); //textura de la fachada
	mapa.BuildGLTexture();
	mapa.ReleaseImage();

	asfalto.LoadTGA("asp.tga"); //textura de la fachada
	asfalto.BuildGLTexture();
	asfalto.ReleaseImage();
	
	soporte._3dsLoad("sop.3ds");

	objCamera.Position_Camera(-10, 15, 50, -10, 0, 0, 0, 1, 0);
}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}



void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
		glPushMatrix(); //Creamos cielo
			glDisable(GL_LIGHTING);
			glTranslatef(0, 100 - (22 * 0.8), 0);
			fig1.skybox(200.0, 300.0, 300.0, text_abajo.GLindex, text_arriba.GLindex, text_izquierda.GLindex, text_derecha.GLindex, text_frente.GLindex, text_atras.GLindex); //textura del cubo
			glEnable(GL_LIGHTING);
		glPopMatrix();
		//Para que el comando glColor funcione con iluminacion
		glEnable(GL_COLOR_MATERIAL);
		//glColor3f(1.0, 1.0, 1.0);

		

		//Plano cartesiano
		glColor3f(0, 0, 0);

		fig1.prisma(1, 1, 1, 0);

		
		glPushMatrix();
		glTranslatef(0, 25, 0);
		glColor3f(1, 0, 0);
		fig1.prisma(50, 0.5, 0.5, 0); //x
		glPopMatrix();

		glPushMatrix();
		glTranslatef(25, 0, 0);
		glColor3f(0, 1, 0);
		fig1.prisma(0.5, 50, 0.5, 0); //x
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, 25);
		glColor3f(0, 0, 1);
		fig1.prisma(0.5, 0.5, 50, 0); //x
		glPopMatrix();
		
		glColor3f(1, 1, 1);
		//Traslaci�n y escalamiento global
		//glTranslatef(0, -90+ (22*0.8), 0);
		glScalef(1, 0.8, 1);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);


		glPushMatrix(); //tapete
			glTranslatef(-15.5, 0.2, -15);
			glRotatef(180, 0, 0, 1);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(10, 14, 0.1, tapete.GLindex,1,1);
		glPopMatrix();

		glPushMatrix(); //Base asfalto
			glTranslatef(20, -22 + 0.1, -30);
			glRotatef(180, 0, 0, 1);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(120, 160, 0.1, asfalto.GLindex);
		glPopMatrix();

		glPushMatrix(); //Pared frente
		fig1.prisma(44, 62, 0.2, ladrillo_f.GLindex);
		glPopMatrix();

		glPushMatrix(); //Tap�z frente
		
		glTranslatef(-15.5, 11, -0.2);
		glRotatef(180, 0, 1, 0);
		fig1.prisma(22, 31, 0.2, tapiz_F.GLindex,1,1);
		glPopMatrix();

		glPushMatrix(); //Tapiz izq
		glTranslatef(-31 + 0.2, 11, -20);
		glRotatef(90, 0, 1, 0);
		fig1.prisma(22, 40, 0.2, tapiz_D.GLindex,1,1);
		glPopMatrix();

		glPushMatrix(); //Pared izq
		glTranslatef(-31 - 0.2, 7.5, -20);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 0, 1, 0);
		fig1.prisma(44 + 15, 40, 0.2, pared_izq.GLindex, 1 ,1);
		glPopMatrix();

		glPushMatrix(); //Pared der
		glTranslatef(31, 7.5, -20);
		glRotatef(90, 0, 1, 0);
		fig1.prisma(44 + 15, 40, 0.2, pared_der.GLindex, 1, 1);
		glPopMatrix();

		glDisable(GL_ALPHA_TEST);

		glPushMatrix(); //globo
			
			glTranslatef(-28,10,-38);
			glRotatef(-90, 1, 0, 0);
			quad = gluNewQuadric();
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, mapa.GLindex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			gluQuadricTexture(quad, 1);
			
			gluSphere(quad, 1.5, 20, 20);
		glPopMatrix();

		glPushMatrix(); //ba�l
			glTranslatef(-17.5, 1.775, -35);
			//glScalef(0.01, 0.003, 0.003);
			glRotatef(90, 0, 1, 0);
			fig1.prisma(3.55, 6, 3.3, 0);
		glPopMatrix();

		glPushMatrix(); //corbel1.1
			glTranslatef(-31+1, 14.0, -8-5);
			glScalef(0.01, 0.003, 0.003);
			glRotatef(90, 0, 1, 0);
			soporte.GLrender(NULL, _SHADED, 1.0);  
		glPopMatrix();

		glPushMatrix(); //corbel1.2
			glTranslatef(-31 + 1, 14.0, -16-5);
			glScalef(0.01, 0.003, 0.003);
			glRotatef(90, 0, 1, 0);
			soporte.GLrender(NULL, _SHADED, 1.0);  
		glPopMatrix();

		glPushMatrix(); //corbel2.1
			glTranslatef(-31 + 1, 16.5, -8-5);
			glScalef(0.01, 0.003, 0.003);
			glRotatef(90, 0, 1, 0);
			soporte.GLrender(NULL, _SHADED, 1.0);  
		glPopMatrix();

		glPushMatrix(); //corbel2.2
			glTranslatef(-31 + 1, 16.5, -16-5);
			glScalef(0.01, 0.003, 0.003);
			glRotatef(90, 0, 1, 0);
			soporte.GLrender(NULL, _SHADED, 1.0);  
		glPopMatrix();

		glPushMatrix(); //corbel3.1
			glTranslatef(-31 + 1, 11.5, -8-5);
			glScalef(0.01, 0.003, 0.003);
			glRotatef(90, 0, 1, 0);
			soporte.GLrender(NULL, _SHADED, 1.0);  
		glPopMatrix();

		glPushMatrix(); //corbel3.2
			glTranslatef(-31 + 1, 11.5, -16-5);
			glScalef(0.01, 0.003, 0.003);
			glRotatef(90, 0, 1, 0);
			soporte.GLrender(NULL, _SHADED, 1.0);  
		glPopMatrix();

		glPushMatrix(); //repisa1
			glTranslatef(-31+1.5, 15, -12 - 5);
			glRotatef(90, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(3, 10, 0.5, 0);
		glPopMatrix();

		glPushMatrix(); //repisa2
			glTranslatef(-31+1.5, 17.5, -12 - 5);
			glRotatef(90, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(3, 10, 0.5, 0);
		glPopMatrix();

		glPushMatrix(); //repisa3
			glTranslatef(-31+1.5, 12.5, -12 - 5);
			glRotatef(90, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(3, 10, 0.5, 0);
		glPopMatrix();

		glPushMatrix(); //Piso primer nivel
			glTranslatef(0, 0, -20);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(40, 62, 0.2, piso.GLindex);
		glPopMatrix();

		glPushMatrix(); //Techo primer nivel
			glTranslatef(0, 22, -20);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(40, 62, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Divisi�n vertical primer nivel
			glTranslatef(0, 11, -20);
			glRotatef(90, 0, 1, 0);
			fig1.prisma(22, 40, 0.2, tapiz.GLindex);
		glPopMatrix();



		glPushMatrix(); //Tapiz atr�s
			glTranslatef(-15.5, 11, -40+0.2);
			fig1.prisma(22, 31, 0.2, tapiz.GLindex);
		glPopMatrix();

		glPushMatrix(); //Pared atr�s
			glTranslatef(0, 0, -40);
			fig1.prisma(44, 62, 0.2, ladrillo.GLindex);
		glPopMatrix();

		

		glPushMatrix(); //Teja frente
			glTranslatef(0, 22 + 7.5, -10);
			glRotatef(90 + 36.86989765, 1, 0, 0);
			fig1.prisma(25, 62, 0.2, teja.GLindex);
		glPopMatrix();

		glPushMatrix(); //Teja atr�s
			glTranslatef(0, 22 + 7.5, -30);
			glRotatef(180, 0, 1, 0);
			glRotatef(90 + 36.86989765, 1, 0, 0);
			fig1.prisma(25, 62, 0.2, teja.GLindex);
		glPopMatrix();

		glPushMatrix();
			//glScalef(0.5, 0.5, 1);
			//glScalef(28 / 62, 15 / 44, 1);
			glTranslatef(31 + 14, -22 + 12.5,0);
			glScalef(0.4516129, 0.5681818181, 1);
			//glScalef(28 / 62, 25 / 44, 1);

			glPushMatrix();
				glPushMatrix(); //Pared atr�s cochera
				fig1.prisma(44, 62, 0.2, ladrillo.GLindex);
				glPopMatrix();

				glPushMatrix(); //Pared frente cochera
				glTranslatef(0, 0, -40);
				fig1.prisma(44, 62, 0.2, ladrillo.GLindex);
				glPopMatrix();

				glPushMatrix(); //Pared izq cochera
				glTranslatef(-31, 0, -20);
				glRotatef(-90, 0, 1, 0);
				fig1.prisma(44, 40, 0.2, ladrillo.GLindex);
				glPopMatrix();

				glPushMatrix(); //Pared der cochera
				glTranslatef(31, 0, -20);
				glRotatef(90, 0, 1, 0);
				fig1.prisma(44, 40, 0.2, ladrillo.GLindex);
				glPopMatrix();

				glPushMatrix(); //Teja frente cochera
				glTranslatef(0, 22 + 7.5, -10);
				glRotatef(90 + 36.86989765, 1, 0, 0);
				fig1.prisma(25, 62, 0.2, teja.GLindex);
				glPopMatrix();

				glPushMatrix(); //Teja atr�s cochera
				glTranslatef(0, 22 + 7.5, -30);
				glRotatef(180, 0, 1, 0);
				glRotatef(90 + 36.86989765, 1, 0, 0);
				fig1.prisma(25, 62, 0.2, teja.GLindex);
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();




	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 700.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED * 0.15);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED * 0.15));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED * 0.15));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED * 0.15);
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(700, 700);	// Tama�o de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto de laboratorio de computaci�n gr�fica"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut funci�n de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut funci�n en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut funci�n de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	//glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}
