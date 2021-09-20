#include "pch.h"
#include "window.hpp"
#include "vec.hpp"
#include "reader.hpp"
#include "light.hpp"

static camera cam {
    {0.0f, 0.0f, 5.0f},
    {0.0f, 0.0f, -3.0f},
    {0.0f, 1.0f, 0.0f},
};

float door_rotate = 90.0;
float last_frame = 0, dt = 0;
float speed = 9.6f;

float rot_angle = 0.0f;
float dw_angle_n_pos[] = {0.0f, 0.0f, 0.0f};
unsigned int control_index = 0;

static void idle()
{
    float current_frame = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    dt = current_frame - last_frame;
    last_frame = current_frame;

    float rotation_speed = 360.0f * 2.0f;
    rot_angle += rotation_speed * dt;
    // basically it caps the angle to 360.0f
    rot_angle -= 360.0f * (rot_angle >= 360.0f);

    glutPostRedisplay();
}

static std::unordered_map<const char*, obj_file> models;

material mat1 {{1.0f, 1.0f, 1.0f}, {0.8f, 0.8f, 0.8f}, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, 255.0f};

clight light[2];

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cam.look_at();

    for (auto &li: light)
    {
        li.dist_position();
    }

    mat1.apply_material();

    glPushMatrix();
        glTranslatef(0.0f, -5.0f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(5.0f, 5.0f, 5.0f);
        models["base cozinha"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5.5f, -4.0f, 33.90f);
        glRotatef(90.0f, 0.0f, -5.0f, 0.0f);
        glScalef(4.0f, 6.0f, 4.0f);
        models["janela"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5.5f, -4.0f, 33.90f);
        glRotatef(90.0f, 0.0f, -5.0f, 0.0f);
        glScalef(4.0f, 6.0f, 4.0f);
        models["janela"].draw_mat_mesh();
    glPopMatrix(); 

    glPushMatrix();
        glTranslatef(15.5f, -4.0f, 33.90f);
        glRotatef(90.0f, 0.0f, -5.0f, 0.0f);
        glScalef(4.0f, 6.0f, 4.0f);
        models["janela"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-13.0f, -4.7f, 2.5f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glScalef(4.5f, 4.9f, 4.9f);
        models["cadeira"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -2.0f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(5.0f, 5.0f, 5.0f);
        models["pia"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -4.7f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(4.5f, 4.5f, 4.5f);
        models["mesa de jantar"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(15.0f, -4.7f, -2.5f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(4.5f, 4.9f, 4.9f);
        models["cadeira"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(25.0f, -5.0f, -7.0f);
        glRotatef(door_rotate, 0.0f, -1.0f, 0.0f);
        glScalef(7.0f, 6.95f, 2.0f);
        models["porta cozinha"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 4.2f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(3.0f, 3.0f, 3.0f);
        models["luminaria de mesa"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -5.0f, -20.0f);
        glRotatef(90.0f, 0.0f, -5.0f, 0.0f);
        glScalef(5.0f, 5.0f, 5.0f);
        models["quadro"].draw_mat_mesh();
    glPopMatrix();

    glutSwapBuffers();
}

window mwindow;

void reshape(int width, int height)
{
    mwindow.set_dimensions_values(width, height);
    mwindow.run_perspective();
}

void motion(int x, int y)
{
    cam.motion(x, y, 0.22f);
}

bool light_on = true;

void keyboard(unsigned char key, int x, int y)
{
    float cam_speed = speed * dt;
    float &ct_var = dw_angle_n_pos[control_index];
    switch (key)
    {
        case 'w':
            cam.pos += cam.front * cam_speed / 2.0f;
        break;
        case 's':
            cam.pos -= cam.front * cam_speed / 2.0f;
        break;
        case 'a':
            cam.pos -= cam.side_vector() * cam_speed;
        break;
        case 'd':
            cam.pos += cam.side_vector() * cam_speed;
        break;
        case ' ':
            cam.pos += cam.up * cam_speed;
        break;
        case 'b':
            cam.pos -= cam.up * cam_speed;
        break;
        case 'o':
            door_rotate = 90.0;
        break;
        case 'p':
            door_rotate = 0.0;
        break;
        case 'l':
            control_index = (control_index + 1) % 3;
        break;
        case 'r':
            static GLenum mode = GL_LINE;
            glPolygonMode(GL_FRONT_AND_BACK, mode);
            mode = mode == GL_LINE ? GL_FILL : GL_LINE;
        break;
        case 'k':
            if (light_on)
            {
                light[1].disable();
                light_on = false;
            }
            else
            {
                light[1].enable();
                light_on = true;
            }
        break;
        case 'u':
            printf("%f %f %f\n", cam.pos.x, cam.pos.y, cam.pos.z);
            printf("%f %f %f\n", cam.front.x, cam.front.y, cam.front.z);
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == 3) // wheel up
    {
    }
    else if (button == 4) // wheel down
    {
    }
}

#ifndef TEST

int main(int argc, char **argv)
{
    mwindow.init(argc, argv, "CG Cozinha AB2", 700, 700);

    glEnable(GL_DEPTH_TEST);
    /* lightning  */
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    light[0] = clight(
        0,
        {0.488164f, 3.054233f, 6.129874f, 0.0f}, // position
        {0.0f, 0.0f, 0.0f, 0.0f}, // direction
        {0.0f, 0.0f, 0.0f, 1.0f}, // ambient
        {1.0f, 1.0f, 1.0f, 1.0f}, // diffuse
        {1.0f, 1.0f, 1.0f, 1.0f}, // specular
        0.0f, 0.0f, clight::type::point_light
    );

    light[1] = clight(
        1,
        {0.584521f, -0.794203f, -0.166065f, 1.0f}, // position
        {0.913373f, -0.084374f, -0.398285f, 1.0f},   // direction
        {1.2f, 1.2f, 1.2f, 1.0f},   // ambient
        {2.0f, 2.2f, 2.0f, 2.0f},   // diffuse
        {1.5f, 1.5f, 1.5f, 1.0f},   // specular
        30.0f, 10.0f, clight::type::spot_light
    );

    for (auto &li: light)
    {
        li.enable();
        li.apply_color();
    }

    mwindow.set_display_func(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(motion);

    cam.center_camera_angle(mwindow);
   
    models["base cozinha"] = obj_file("objs/baseCozinha.obj");
    models["cadeira"] = obj_file("objs/cadeira.obj");
    models["janela"] = obj_file("objs/janela.obj");
    models["mesa de jantar"] = obj_file("objs/mesadejantar.obj");
    models["pia"] = obj_file("objs/pia.obj");
    models["porta cozinha"] = obj_file("objs/portacozinha.obj");
    models["luminaria de mesa"] = obj_file("objs/luminaria.obj");
    models["quadro"] = obj_file("objs/quadro.obj");
    models["ventilador de teto"] = obj_file("objs/ventiladordeteto.obj");
    mwindow.run();
    return 0;
}

#endif
