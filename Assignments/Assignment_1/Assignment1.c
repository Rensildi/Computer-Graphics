/*
 * Copyright (c) 1993-1999, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU &quot;AS-IS&quot;
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  double.c
 *  This is a simple double buffered program.
 *  Pressing the left mouse button rotates the rectangle.
 *  Pressing the middle mouse button stops the rotation.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float currentColor[3] = {1.0f, 1.0f, 1.0f}; // Default color (white)
static GLfloat spin = 0.0;
static GLfloat spinSpeed = 2.0;
static int shape = 0; // default shape --> rectangle
int showText = 0; // 0/1 -> on and off

// Legend for all the new features
void renderText(float x, float y, const char* text) {
    glPushMatrix();
    glRasterPos2f(x, y);
    glScalef(0.01f, 0.01, 0.01f);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
}

void drawLegend() {
    glColor3f(1.0, 1.0, 1.0);
    renderText(-48.0f, 45.0f, "Keyboard Controls:");
    renderText(-48.0f, 42.0f, "  w: Start Rotation");
    renderText(-48.0f, 39.0f, "  s: Stop Rotation");
    renderText(-48.0f, 36.0f, "  r: Reset Rotation");
    renderText(-48.0f, 33.0f, "  c: Random Color");
    renderText(-48.0f, 30.0f, "  Arrow Keys: Change Speed/Direction");
    renderText(-48.0f, 27.0f, "Mouse Controls:");
    renderText(-48.0f, 24.0f, "  Left Button: Start Rotation");
    renderText(-48.0f, 21.0f, "  Right Button: Stop Rotation");
    renderText(-48.0f, 18.0f, "Menu:");
    renderText(-48.0f, 15.0f, "  Right-click: Open Context Menu");
}


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f(currentColor[0], currentColor[1], currentColor[2]);
   
   // different shapes
   switch (shape) {
        case 0:
            glRectf(-25.0, -25.0, 25.0, 25.0); // Rectangle
            break;
        case 1:
            glutWireSphere(25.0, 10, 10); // Sphere
            break;
        case 2:
            glutWireCube(50.0); // Cube
            break;
        default:
            break;
   }

   // Show text
   if (showText) {
        glColor3f(1.0, 0.0, 0.0);
        renderText(-10.0, 0.0, "CG is fun");
   }

   // Button
   glColor3f(1.0, 1.0, 1.0);
   renderText(-8.0, -38.0, "Click Me");

    glPopMatrix();
   

   // Legend
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   drawLegend();

   glPopMatrix();
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);

   glutSwapBuffers();
}

void spinDisplay(void)
{
   spin = spin + spinSpeed;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;
      case GLUT_MIDDLE_BUTTON:
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */

// Assignment 1 addings

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27: // ESC key to exit
            exit(0);
            break;
        case 'r': // Reset rotation
            spin = 0.0f;
            glutPostRedisplay();
            break;
        case 'c': // Color Randomization
            currentColor[0] = (float)rand() / RAND_MAX; // Random red
            currentColor[1] = (float)rand() / RAND_MAX; // Random green
            currentColor[2] = (float)rand() / RAND_MAX; // Random blue
            glutPostRedisplay();
            break;
        case 'w': // Start rotation
            glutIdleFunc(spinDisplay);
            break;
        case 's': // Stop rotation
            glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}

void specialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP: // Increase rotation speed
            spinSpeed += 0.1;
            break;
        case GLUT_KEY_DOWN: // Decrease rotation speed
            spinSpeed -= 0.1;
            if (spinSpeed < 0.1) spinSpeed = 0.1; // Minimum speed
            break;
        case GLUT_KEY_LEFT: // Rotate counterclockwise
            spinSpeed = -(fabs(spinSpeed)); // Negative speed for counterclockwise
            break;
        case GLUT_KEY_RIGHT: // Rotate clockwise
            spinSpeed = fabs(spinSpeed); // Positive speed for clockwise rotation
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Popup menu
void menuHandler(int option) {
    switch (option) {
        case 1: // Start Rotation
            glutIdleFunc(spinDisplay);
            break;
        case 2: // Stop Rotation
            glutIdleFunc(NULL);
            break;
        case 3: // Reset Rotation
            spin = 0.0;
            glutPostRedisplay();
            break;
        case 4: // Increase Rotation Speed
            spinSpeed += 0.5; // Incrementing the speed
            break;
        case 5: // Decrease Rotation Speed
            spinSpeed -= 0.5; // Decrementing the speed
            if (spinSpeed < 0.1) spinSpeed = 0.1; // Minimum Speed
            break;
        default:
            break;
    }
}

void menuColor(int colorOption) {
    switch (colorOption) {
        case 1: // red
            currentColor[0] = 1.0f; // Red
            currentColor[1] = 0.0f; // Green
            currentColor[2] = 0.0f; // Blue
            break;
        case 2: // green
            currentColor[0] = 0.0f; // Red
            currentColor[1] = 1.0f; // Green
            currentColor[2] = 0.0f; // Blue
            break;
        case 3: // blue
            currentColor[0] = 0.0f; // Red
            currentColor[1] = 0.0f; // Green
            currentColor[2] = 1.0f; // Blue
            break;
        case 4: // yellow
            currentColor[0] = 1.0f; // Red
            currentColor[1] = 1.0f; // Green
            currentColor[2] = 0.0f; // Blue
            break;
        case 5: // purple
            currentColor[0] = 1.0f; // Red
            currentColor[1] = 0.0f; // Green
            currentColor[2] = 1.0f; // Blue
            break;
        case 6: // sky
            currentColor[0] = 0.0f; // Red
            currentColor[1] = 1.0f; // Green
            currentColor[2] = 1.0f; // Blue
            break;
        case 7: // white
            currentColor[0] = 1.0f; // Red
            currentColor[1] = 1.0f; // Green
            currentColor[2] = 1.0f; // Blue
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Rfresh the display to apply the color change
}

// menu shapes
void menuShape(int shapeOption) {
    switch (shapeOption) {
        case 0:
            shape = 0; // Rectangle
            break;
        case 1:
            shape = 1; // Sphere
        case 2:
            shape = 2; // Cube
        default:
            break;
    }
    glutPostRedisplay();
}


// Attaching the menu and color submenu
void createMenu() {
    int colorMenu = glutCreateMenu(menuColor);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Purple", 5);
    glutAddMenuEntry("Sky", 6);
    glutAddMenuEntry("White", 7);


    int shapeMenu = glutCreateMenu(menuShape);
    glutAddMenuEntry("Rectangle", 0);
    glutAddMenuEntry("Sphere", 1);
    glutAddMenuEntry("Cube", 2);


    int mainMenu = glutCreateMenu(menuHandler);
    glutAddMenuEntry("Start Rotation", 1);
    glutAddMenuEntry("Stop Rotation", 2);
    glutAddMenuEntry("Reset Rotation", 3);
    glutAddMenuEntry("Increase Speed", 4);
    glutAddMenuEntry("Decrease Speed", 5);

    // colorMenu is a sub menu
    glutAddSubMenu("Change Color", colorMenu);
    
    // shapeMenu
    glutAddSubMenu("Change Shape", shapeMenu);


    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Main
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   
   glutInitWindowSize(1800, 900);
   glutCreateWindow("OpenGL");

   init();
   createMenu();
   
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeys);
   glutMainLoop();
   //sliders();
   //buttons();
   return 0; /* ANSI C requires main to return int. */
}

