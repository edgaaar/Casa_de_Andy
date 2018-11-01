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

CTexture text_arriba;
CTexture text_abajo;
CTexture text_izquierda;	
CTexture text_derecha;	
CTexture text_frente;	
CTexture text_atras;	

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

//Animación del coche
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

	//Carga de Figuras
	kit._3dsLoad("kitt.3ds");
	//kit.VertexNormals();

	llanta._3dsLoad("k_rueda.3ds");


	objCamera.Position_Camera(20, 15.0f, 20, 1, 1, 1, 0, 1, 0);

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
			glDisable(GL_LIGHT1);
			fig1.skybox(180.0, 520.0, 520.0, /*text_abajo.GLindex*/0, text_arriba.GLindex, text_izquierda.GLindex, text_derecha.GLindex, text_frente.GLindex, text_atras.GLindex); //textura del cubo
			glEnable(GL_LIGHT1);
		glPopMatrix();
		//Para que el comando glColor funcione con iluminacion
		glEnable(GL_COLOR_MATERIAL);
		//glColor3f(1.0, 1.0, 1.0);

		glTranslatef(0, -90+22, 0);

		glPushMatrix(); //Pared atrás
			fig1.prisma(44, 62, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Pared frente
			glTranslatef(0, 0, -40);
			fig1.prisma(44, 62, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Pared izq
			glTranslatef(-31, 0, -20);
			glRotatef(-90, 0, 1, 0);
			fig1.prisma(44, 40, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Pared der
			glTranslatef(31, 0, -20);
			glRotatef(90, 0, 1, 0);
			fig1.prisma(44, 40, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Teja frente
			glTranslatef(0, 22 + 7.5, -10);
			glRotatef(90 + 36.86989765, 1, 0, 0);
			fig1.prisma(25, 62, 0.2, 0);
		glPopMatrix();

		glPushMatrix(); //Teja atrás
			glTranslatef(0, 22 + 7.5, -30);
			glRotatef(180, 0, 1, 0);
			glRotatef(90 + 36.86989765, 1, 0, 0);
			fig1.prisma(25, 62, 0.2, 0);
		glPopMatrix();

		glPushMatrix();
			//glScalef(0.5, 0.5, 1);
			//glScalef(28 / 62, 15 / 44, 1);
			glTranslatef(31 + 14, -22 + 12.5,0);
			glScalef(0.4516129, 0.5681818181, 1);
			//glScalef(28 / 62, 25 / 44, 1);

			glPushMatrix();
				glPushMatrix(); //Pared atrás cochera
				fig1.prisma(44, 62, 0.2, 0);
				glPopMatrix();

				glPushMatrix(); //Pared frente cochera
				glTranslatef(0, 0, -40);
				fig1.prisma(44, 62, 0.2, 0);
				glPopMatrix();

				glPushMatrix(); //Pared izq cochera
				glTranslatef(-31, 0, -20);
				glRotatef(-90, 0, 1, 0);
				fig1.prisma(44, 40, 0.2, 0);
				glPopMatrix();

				glPushMatrix(); //Pared der cochera
				glTranslatef(31, 0, -20);
				glRotatef(90, 0, 1, 0);
				fig1.prisma(44, 40, 0.2, 0);
				glPopMatrix();

				glPushMatrix(); //Teja frente cochera
				glTranslatef(0, 22 + 7.5, -10);
				glRotatef(90 + 36.86989765, 1, 0, 0);
				fig1.prisma(25, 62, 0.2, 0);
				glPopMatrix();

				glPushMatrix(); //Teja atrás cochera
				glTranslatef(0, 22 + 7.5, -30);
				glRotatef(180, 0, 1, 0);
				glRotatef(90 + 36.86989765, 1, 0, 0);
				fig1.prisma(25, 62, 0.2, 0);
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();

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
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case ' ':		//Poner algo en movimiento
		g_fanimacion ^= true; //Activamos/desactivamos la animacíon
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
	glutInitWindowSize(700, 700);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto de laboratorio de computación gráfica"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}
