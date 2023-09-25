#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

 
void display();
void specialKeys();

float pi=3.14159265358979323846;

double rotate_y=3; 
double rotate_x=0;
double rotate_z=0;

void specialKeys( int key, int x, int y ) {
 
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
 
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
 
  glutPostRedisplay();
 
}


void draw_color(float x,float y){

  float r,prev_x=0,prev_y=0,next_x,next_y,col_r = 0.50;
  int init_n = 3,last_incrs = 8;
  for(int i=0;i<6;i++){ 
      r = (float)(init_n + rand() % 6)/100;
      next_x = r*x;
      next_y = r*y;

      glColor3f(col_r,0.52,0.33);
      glBegin(GL_LINES);      
      glVertex2f(prev_x,prev_y);
      glVertex2f(next_x,next_y);
      glEnd();

      prev_x = next_x;
      prev_y = next_y;
      col_r += 0.04;
      init_n += last_incrs;
      last_incrs+=3;
  }

  glColor3f(col_r,0.52,0.33);
  glBegin(GL_LINES);
  next_x = x;
  next_y = y;
  glVertex2f(prev_x,prev_y);
  glVertex2f(next_x,next_y);
  glEnd();
}



void display(){
  float angle; 
  float x,y,z,a,b,c,d,ratio,mul;
  int parts;
  float point[2];

  //glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHTING);
  glClearColor(1.0,1.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  
  glMatrixMode(GL_PROJECTION);
  gluPerspective(50.0, 1.0, 1.0, 10.0);

  gluLookAt( 0.0, 0.0, 5.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);

  glTranslatef(0.0, -2.0, -2.5);
 
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );
  glRotatef( rotate_z, 0.0, 0.0, 1.0 );
  
  
  glPointSize(2);  

  parts = 3 + (rand() % 4);
  ratio = ((float)(10)/parts)/10;
  
  //printf("%f %d \n",ratio,parts);
  int curve = rand() % 2; 
  
  for(angle=0;angle<=pi;angle+=(pi/2)) 
  {
   for(float i=0.0;i<=angle;i=i+0.001)
   {
  
    x = (2*i)-3; 
    y = 4*sin(i)+(0.2)*sin(9*i); 
    
    draw_color(x,y);
    
    glColor3f(0.27,0,0); 
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glVertex2f(0.995*x,0.995*y);
    glEnd();
    a = 0.0;
    b = 0.0;
    mul = ratio;
    for(int j = 0;j<parts-1;j++){
        c = mul*x;
        d = mul*(4*sin(i)+(0.2)*sin(8*i));  
        glBegin(GL_LINES);
        int n = rand() % 2;
        for(int k=0;k<=n;k++){
            float lambda = (float)(rand() % 11)/10;
            point[0] = (1-lambda)*(c) + lambda*(a);
            point[1] = (1-lambda)*(d) + lambda*(b);
            glVertex2f(point[0],point[1]);
        }         
        glEnd(); 

        glBegin(GL_POINTS);
        glVertex2f(c,d);
        glVertex2f(0.995*c,0.995*d);
        glEnd(); 
        mul += ratio;
        a = c;
        b = d;
      }
      glBegin(GL_LINES);
      int n = rand() % 2;
      for(int k=0;k<=n;k++){
          float lambda = (float)(rand() % 11)/10;
          point[0] = (1-lambda)*(x) + lambda*(a);
          point[1] = (1-lambda)*(y) + lambda*(b);
          glVertex2f(point[0],point[1]);
      }        
      glEnd(); 
    } 
  }

  glFlush();
  glutSwapBuffers();
 
}
 

 
int main(int argc, char* argv[]){
 
  glutInit(&argc,argv);
 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (1000, 1000);
  glutInitWindowPosition (100, 100);
  glutCreateWindow("tree_sine_wave");
 
  glEnable(GL_DEPTH_TEST);
 
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
 
  glutMainLoop();
 
  return 0;
 
}

