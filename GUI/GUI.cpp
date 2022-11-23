

#include "GUI.h"

#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include "../World/src/bomb.h"

#include "Libs/glut.h"

#define LABEL_SHOW				false
#define HEALTH_SHOW				true
#define PROXIMITY_SHOW			true
#define PROXIMITY_MAX			1

#define GRID_SIZE				20
#define PROXIMITY_RESOLUTION	10

using namespace std;

GUI* GUI::_instance = NULL;

GUI::GUI() : _frame(0) {
	_mouseX = 0;
	_mouseY = 0;
	_mouseEnabled = false;
	_brainEnabled = false;
	_fullscreen = false;
	_windowpmPositionX = 0;
	_windowpmPositionY = 0;
	_paused = true;
}

GUI::~GUI() {
}

GUI* GUI::Instance(void) {
	if (_instance==NULL) {
		_instance = new GUI();
	}
	return _instance;
}

void GUI::execute() {
	glutMainLoop();
}

// GLUT popup menu item definitions
#define OPTION_DEGREE2 12
#define OPTION_DEGREE3 13
#define OPTION_DEGREE4 14
#define OPTION_DEGREE5 15
#define OPTION_DEGREE6 16
#define OPTION_QUIT 27


void GUI::displayText(float x, float y, string text) {
	// Outputs text using GLUT, at the specyfied location.

	char c[100];
	memset(c,0,sizeof(c));
	strcpy_s(c, text.data());
  
	glRasterPos2f(x, y);
	for (int i=0; i < (int)strlen(c); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c[i]);
	}
}

void GUI::drawCircle(float x, float y, float r) {
	float PI = 3.14159265;
	float PI180 = PI/180.0f;
	glPushMatrix();
		glTranslatef(x, y, 0);
		glBegin(GL_LINES);

			x = (float)r * cos(359 * PI180);
			y = (float)r * sin(359 * PI180);
			for(int j = 0; j < 360; j++)
			{
				glVertex2f(x,y);
				x = (float)r * cos(j * PI180);
				y = (float)r * sin(j * PI180);
				glVertex2f(x,y);
			}
		glEnd();
	glPopMatrix();
}

void GUI::drawWorld() {
	int w = _world->width(), h = _world->height();
	float hw = w * 0.5f, hh = h * 0.5f;
	float sw = _screenwidth * 0.5f, sh = _screenheight * 0.5f;

	int gs = GRID_SIZE;

	// Draw walls.
	float xc, yc;
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_QUADS);
	for (int y = 0; y < h; ++y)
		for(int x = 0; x < w; ++x)
			if(_world->get(x, y) != 0) {
				xc = sw + (x - hw) * gs;
				yc = sh + (hh - y) * gs;
				glVertex2f(xc, yc);
				glVertex2f(xc + gs, yc);
				glVertex2f(xc + gs, yc - gs);
				glVertex2f(xc, yc - gs);
			}
	glEnd();

	// Draw wall proximity data.
	if(PROXIMITY_SHOW) {
		int r = PROXIMITY_RESOLUTION;
		pmMatrix<pmAcceleration<float, 2>*>* wp = _world->getWallProximities();
		float ww = wp->getNumColumns() * 0.5f, wh = wp->getNumRows() * 0.5f;
		float step = float(gs) / r, spd;
		pmAcceleration<float, 2>* acc;
		glBegin(GL_QUADS);
		for(int y = 0; y < h * r; ++y)
			for(int x = 0; x < w * r; ++x) {
				acc = wp->get(x, y);
				spd = acc->magnitude();
				if(spd != 0) {
					xc = sw + (x - ww) * step;
					yc = sh + (wh - y) * step;
					float color = 1 - (spd / PROXIMITY_MAX);
					glColor3f(color, color, color);
					glVertex2f(xc, yc);
					glVertex2f(xc + step, yc);
					glVertex2f(xc + step, yc - step);
					glVertex2f(xc, yc - step);
				}
			}
		glEnd();
	}
}

void GUI::drawBombs() {
	vector<Bomb<float, 2>>::iterator it;
	vector<Bomb<float, 2>>* bombs = _world->getBombs();
	
	int xOff = _screenwidth/2;
	int yOff = _screenheight/2;
	int cid = 0;

	pmPosition2f pos;
	float range;
	float x, y;

	glColor3f(1, 0.2f, 0);
	for (it = bombs->begin(); it!=bombs->end(); ++it) {
		pos = (*it).getpmPosition();
		range = (*it).getRange();

		x = xOff + pos.get(0) * GRID_SIZE;
		y = yOff + pos.get(1) * GRID_SIZE;

		drawCircle(x, y, range* GRID_SIZE);
	}
}

void GUI::drawSafezones() {
	vector<pmPosition2f*>::iterator it;
	vector<pmPosition2f*>* safezones = _world->getSafezones();
	
	int xOff = _screenwidth/2;
	int yOff = _screenheight/2;
	int cid = 0;

	pmPosition2f pos;
	float x, y;

	glColor3f(0.0f, 0.8f, 1.0f);
	for (it = safezones->begin(); it!=safezones->end(); ++it) {
		x = xOff + (*it)->get(0) * GRID_SIZE;
		y = yOff + (*it)->get(1) * GRID_SIZE;

		drawCircle(x, y, float(GRID_SIZE)/2);
	}
}

void GUI::drawBoids() {
	vector<Boid2f*>::iterator it;
	vector<Boid2f*> boids = _bs->getBoids();
	
	int xOff = _screenwidth/2;
	int yOff = _screenheight/2;
	int cid = 0;

	pmPosition2f* pos;
	pmOrientation2f* ori;
	pmOrientation2f north;
	north.set(1, 1);
	float x, y, a, h;
	for (it = boids.begin(); it!=boids.end(); ++it) {
		h = float((*it)->getHealth()) / 100;
		pos = (*it)->getpmPosition();
		ori = (*it)->getpmOrientation();
		x = xOff + pos->get(0) * GRID_SIZE;
		y = yOff + pos->get(1) * GRID_SIZE;
		a = angle(north, *ori);
		a = ori->get(0) > 0 ? -a : a;

		// Show boid location.
		if(LABEL_SHOW) {
			glColor3f(0.5f, 0.5f, 0.5f);
			stringstream ss;
			float px = float(int(pos->get(0) * 100)) / 100;
			float py = float(int(pos->get(1) * 100)) / 100;
			ss << "(" << px << ", " << py << ")";
			displayText(x + 10, y - 2, ss.str());
		}

		// Show boid.
		glPushMatrix();
			glTranslatef(x, y, 0);

			// Show boid health.
			if(HEALTH_SHOW && !(*it)->isSaved() && h > 0) {
				glPushMatrix();
				glScalef(8, 8, 8);
				glTranslatef(0, 1, 0);
				glBegin(GL_QUADS);
					glColor3f(1, 0, 0);
					glVertex2f(-0.5f, -0.1f);
					glVertex2f(+0.5f, -0.1f);
					glVertex2f(+0.5f, +0.1f);
					glVertex2f(-0.5f, +0.1f);
					glColor3f(0, 1, 0);
					glVertex2f(-0.5f, -0.1f);
					glVertex2f(+0.5f - (1.0f - h), -0.1f);
					glVertex2f(+0.5f - (1.0f - h), +0.1f);
					glVertex2f(-0.5f, +0.1f);
				glEnd();
				glPopMatrix();
			}

			glRotatef((a * (180.0f / 3.14159265358f)), 0, 0, 1);
			// Determine color.
			cid = (*it)->getColonyID();
			if ((*it)->isSaved()) {
				glColor3f(0.4f, 0.8f, 1.0f);
			} else
			if(h > 0) {
				if(cid == 0)
					glColor3f(0,1,0);
				else if(cid == 1)
					glColor3f(0,0,1);
				else if(cid == 2)
					glColor3f(1,0,0);
				else
					glColor3f(.5f,.5f,.5f);
			} else if(cid == 1)
				glColor3f(0.5f, 0, 0);
			else
				glColor3f(.5f,.5f,.5f);
			// Draw triangle.
			glBegin(GL_LINE_LOOP);
				glVertex2f(+0.10f * GRID_SIZE, -0.15f * GRID_SIZE);
				glVertex2f(+0.00f * GRID_SIZE, +0.15f * GRID_SIZE);
				glVertex2f(-0.10f * GRID_SIZE, -0.15f * GRID_SIZE);
			glEnd();
		glPopMatrix();
	}
}

void GUI::drawMouse() {
	if (_mouseEnabled) {
		glPushMatrix();
			glTranslatef(_mouseX, _mouseY, 0);
			glColor3f(1,1,1);
			glBegin(GL_TRIANGLES);
				glVertex2f(0,0);
				glVertex2f(8,-11);
				glVertex2f(0,-14);
			glEnd();
		glPopMatrix();
	}
}

void GUI::draw (void) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0.0, _screenwidth, 0.0, _screenheight, -1.0, 1.0 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();

	// Draw the world and all entities
	drawWorld();
	drawBombs();
	drawSafezones();
	drawBoids();
	drawMouse();

	// Display the current frame.
	glColor3f(0.8,0.8,0.8);
	stringstream info;
	info << "Frame: " << _frame;
	displayText(4, _screenheight - 14, info.str());

	// Display the current fitness
	int total = _bs->countBoids(NEUTRAL);
	int alive = _bs->countBoids(NEUTRAL, true);
	int dead = total - alive;
	int saved = _bs->getNrOfSavedBoids();
	int score = dead * -10 + alive * 5 + saved * 20;
	stringstream infofitness;
	infofitness << "Fitness: " << score;
	displayText(4, _screenheight - 28, infofitness.str());

	if (_paused) {
		displayText(4, _screenheight - 42, "Paused, press p to resume");
	}
	// Output everything correctly to the screen
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
	glutSwapBuffers();
}

void GUI::toggleFullscreen() {
	_fullscreen = !_fullscreen;

	if (_fullscreen) {
		_windowpmPositionX = glutGet((GLenum)GLUT_WINDOW_X);
		_windowpmPositionY = glutGet((GLenum)GLUT_WINDOW_Y);
		glutDestroyWindow(1);
		glutGameModeString("1024x768:32@60");
		glutEnterGameMode();
		glutSetCursor(GLUT_CURSOR_NONE); 
		_mouseEnabled = true;				
	} else {
		glutLeaveGameMode();
		glutCreateWindow("GNA Engine 2012");
		glutReshapeWindow(_world->width() * GRID_SIZE, _world->height() * GRID_SIZE);
		glutPositionWindow(_windowpmPositionX, _windowpmPositionY);
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		_mouseEnabled = false;
	}
	glutDisplayFunc(drawCallback);
	glutKeyboardFunc(keyInputHandlerCallback);
	glutMouseFunc(mouseInputHandlerCallback);
	glutPassiveMotionFunc(mouseMotionHandlerCallback);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void GUI::update() {
	if (!_paused) {
		if (_brainEnabled) {
			pmVectord input(84), output(16);

			//Read positions for brain.
			vector<Boid<float, 2>*> _Boids = _bs->getBoids();
			unsigned int nrOfBoids = _Boids.size();
			for(unsigned int i = 0; i < nrOfBoids ; ++i){
				pmPosition2f* pos = _Boids[i]->getpmPosition();
				input.set(pos->get(0),i); //x position
				input.set(pos->get(1),i); //y position
			}
			// the first safezone position.
			pmPosition2f* safezone = _world->getSafezones()->at(0);
			input.set(safezone->get(0),nrOfBoids);// x position of safezone
			input.set(safezone->get(1),nrOfBoids+1);// y position of safezone

			// the first bomb position.
			pmPosition2f bombpos = _world->getBombs()->at(0).getpmPosition();
			input.set(bombpos.get(0),nrOfBoids+2);// x position of bomb
			input.set(bombpos.get(1),nrOfBoids+3);// y position of bomb
		
			// Think.
			output = _mlp->process(input);

			// Update brainRules.
			vector<Boid2f*> boids = _bs->getBoids(FRIENDLY);
			vector<Boid2f*>::iterator it;
			int counter = -1;
			pmPosition2f target;
			for(it = boids.begin(); it != boids.end(); ++it) {
				BrainRule<float, 2>* brain = (*it)->getBrain();
				if (brain!=NULL) {
					target.set(float(output.get(++counter)), 0);
					target.set(float(output.get(++counter)), 1);
					brain->setTarget(target);
				}
			}
		}
		_bs->update();
		++_frame;
	}
	glutPostRedisplay();
}

void GUI::windowResize (int width, int height) {
	// Adjust the global screen size variables,
	// otherwise points will be added in unexpected positions
	_screenwidth = width;
	_screenheight = height;

    glViewport( 0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity ();
    gluPerspective( 60, (GLfloat) width /(GLfloat) height , 0.10, 1000.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void GUI::keyInputHandler(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
		case 'q':
			// Exit application on Escape or 'q' key
			exit(0);
			break;
		case 'm':
			if (_mouseEnabled) {
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			} else {
				glutSetCursor(GLUT_CURSOR_NONE); 
			}
			_mouseEnabled = !_mouseEnabled;
			break;
		case 'b':
			if (_world->getBombsActive())
				_world->setBombsActive(false);
			else
				_world->setBombsActive();
			break;
		case 'f':
			toggleFullscreen();
			break;
		case 'p':
			togglePause();
			break;
	}
}


void GUI::mouseInputHandler(int button, int state, int mx, int my) {
	// Calculate the y axis according to the world location
	my = _screenheight - my;
	
	// Create or update a control point
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//_bs.addBoid(new Boid<float, 2>(_bs, 0));
		float x = ((float)mx - (_screenwidth/2)) / GRID_SIZE;
		float y = ((float)my - (_screenheight/2)) / GRID_SIZE;
		std::cout << "Bomb placed at: " << x << "\t" << y << std::endl;
		_world->addBomb(x, y, 0.5f);
		glutPostRedisplay();
	}
}


void GUI::mouseMotionHandler(int mx, int my) {
	my = _screenheight - my;
	_mouseX = mx;
	_mouseY = my;
}


void GUI::processMenuEvents(int option) {
	// Handle chosen menu options
	/*switch (option) {
	}*/
}


void GUI::createGLUTMenus() {

	int submenu;
	// Create a submenu for selecting the Polyniomal degree
	submenu = glutCreateMenu(processMenuEventsCallback);
	/*glutAddMenuEntry("Sub 1",OPTION_DEGREE2);
	glutAddMenuEntry("Sub 2",OPTION_DEGREE3);
	glutAddMenuEntry("Sub 3",OPTION_DEGREE4);
	glutAddMenuEntry("Sub 4",OPTION_DEGREE5);
	glutAddMenuEntry("Sub 5",OPTION_DEGREE6);

	menu = glutCreateMenu(processMenuEventsCallback);
	
	// Add the options to the menu
	glutAddSubMenu("Submenu",submenu);
	glutAddMenuEntry("Quit program [q]", OPTION_QUIT);
	
	// Attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);*/
}


bool GUI::initialize (int argc, char **argv, DiscreteWorld2D* world, BoidSystem2f* bs, bool brain) {
	_world = world;
	_bs = bs;
	// Initialize screen dimensions.
	_screenwidth = _world->width() * GRID_SIZE;
	_screenheight = _world->height() * GRID_SIZE;
	// Initialize graphics.
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (_screenwidth, _screenheight);
	glutInitWindowPosition (200, 100);
	glutCreateWindow ("GNA Engine 2012");
	//createGLUTMenus();
	glutDisplayFunc(drawCallback);
	glutIdleFunc(updateCallback);
	glutReshapeFunc(windowResizeCallback);
	glutKeyboardFunc(keyInputHandlerCallback);
	glutMouseFunc(mouseInputHandlerCallback);
	glutPassiveMotionFunc(mouseMotionHandlerCallback);
	//glutMotionFunc(mouseMotionHandlerCallback);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}