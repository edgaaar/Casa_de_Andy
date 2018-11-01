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

//texturas skybox
CTexture text_arriba;
CTexture text_abajo;
CTexture text_izquierda;	
CTexture text_derecha;	
CTexture text_frente;	
CTexture text_atras;

//texturas casa
CTexture ladrillo;
CTexture teja;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CFiguras fig7; //Para el monito

//Figuras de 3D Studio
CModel kit;
CModel llanta;

//Animaci�n del coche
float movKit = 0.0;
bool g_fanimacion = false;
boolean yallegue = false;



void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
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

	text_atras.LoadTGA("sorbin_bk.tga"); //textura del cubo
	text_atras.BuildGLTexture();
	text_atras.ReleaseImage();

	text_frente.LoadTGA("sorbin_ft.tga"); //textura del cubo
	text_frente.BuildGLTexture();
	text_frente.ReleaseImage();

	text_izquierda.LoadTGA("sorbin_lf.tga"); //textura del cubo
	text_izquierda.BuildGLTexture();
	text_izquierda.ReleaseImage();

	text_derecha.LoadTGA("sorbin_rt.tga"); //textura del cubo
	text_derecha.BuildGLTexture();
	text_derecha.ReleaseImage();

	text_arriba.LoadTGA("sorbin_up.tga"); //textura del cubo
	text_arriba.BuildGLTexture();
	text_arriba.ReleaseImage();

	text_abajo.LoadTGA("sorbin_dn.tga"); //textura del cubo
	text_abajo.BuildGLTexture();
	text_abajo.ReleaseImage();

	ladrillo.LoadTGA("lad.tga"); //textura de la fachada
	ladrillo.BuildGLTexture();
	ladrillo.ReleaseImage();

	teja.LoadTGA("tej.tga"); //textura de la fachada
	teja.BuildGLTexture();
	teja.ReleaseImage();

	//Carga de Figuras
	kit._3dsLoad("kitt.3ds");
	//kit.VertexNormals();

	llanta._3dsLoad("k_rueda.3ds");


	objCamera.Position_Camera(0, 0, 50, 0, -50, -50, 0, 1, 0);

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
			glTranslatef(0, 90 - (22 * 0.8), 0);
			fig1.skybox(180.0, 520.0, 520.0, text_abajo.GLindex, text_arriba.GLindex, text_izquierda.GLindex, text_derecha.GLindex, text_frente.GLindex, text_atras.GLindex); //textura del cubo
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

		glPushMatrix(); //Piso primer nivel
			glTranslatef(0, 0, -20);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(40, 62, 0.2, ladrillo.GLindex);
		glPopMatrix();

		glPushMatrix(); //Techo primer nivel
			glTranslatef(0, 22, -20);
			glRotatef(90, 1, 0, 0);
			fig1.prisma(40, 62, 0.2, ladrillo.GLindex);
		glPopMatrix();

		glPushMatrix(); //Divisi�n vertical primer nivel
			glTranslatef(0, 11, -20);
			glRotatef(90, 0, 1, 0);
			fig1.prisma(22, 40, 0.2, ladrillo.GLindex);
		glPopMatrix();

		glPushMatrix(); //Tapiz izq
			glTranslatef(-31 + 0.2, 11, -20);
			glRotatef(90, 0, 1, 0);
			fig1.prisma(22, 40, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Tapiz atr�s
			glTranslatef(-15.5, 11, -40+0.2);
			fig1.prisma(22, 31, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Tap�z frente
			glTranslatef(-15.5, 11, -0.2);
			fig1.prisma(22, 31, 0.2, 0);
		glPopMatrix();



		glPushMatrix(); //Pared frente
			fig1.prisma(44, 62, 0.2, ladrillo.GLindex);
		glPopMatrix();

		glPushMatrix(); //Pared atr�s
			glTranslatef(0, 0, -40);
			fig1.prisma(44, 62, 0.2, ladrillo.GLindex);
		glPopMatrix();

		glPushMatrix(); //Pared izq
			glTranslatef(-31, 0, -20);
			glRotatef(-90, 0, 1, 0);
			fig1.prisma(44, 40, 0.2, ladrillo.GLindex);
		glPopMatrix();

		glPushMatrix(); //Pared der
			glTranslatef(31, 0, -20);
			glRotatef(90, 0, 1, 0);
			fig1.prisma(44, 40, 0.2, ladrillo.GLindex);
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

void animacion()
{
	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq < -1)
		fig3.text_izq = 0;
	if (fig3.text_der < 0)
		fig3.text_der = 1;

	if (g_fanimacion && movKit <= 100 && yallegue == false)
	{
		movKit += 1.0;
		if (movKit == 100)
			yallegue = true;
	}

	if (yallegue == true && movKit >= 0) {
		movKit -= 1.0;
		if (movKit == 0)
			yallegue = false;
	}
	glutPostRedisplay();
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
		objCamera.Move_Camera(CAMERASPEED * 0.1);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED * 0.1));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED * 0.1));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED * 0.1);
		break;

	case ' ':		//Poner algo en movimiento
		g_fanimacion ^= true; //Activamos/desactivamos la animac�on
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
	glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}
