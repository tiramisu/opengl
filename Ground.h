#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <cmath>

namespace Ground
{
class Ground
{
    double minX, minY, maxX, maxY, tile_size;
    std::vector<std::vector<float> > ambient {{0.2, 0.2, 0.2, 1}, {0.2, 0.2, 0.2, 1}};
    std::vector<std::vector<float> > diffuse {{0.8, 0.8, 0.8, 1}, {0.8, 0.8, 0.8, 1}};
    std::vector<std::vector<float> > specular {{0, 0, 0, 1}, {0, 0, 0, 1}};
    std::vector<std::vector<float> > emission {{0, 0, 0, 1}, {0, 0, 0, 1}};
    std::vector<int > shininess {0,0};
public:
    Ground(double minX, double minY, double maxX, double maxY, double tile_size);
    ~Ground();

    void drawGroundTex(GLuint num1, GLuint num2);
};

Ground::Ground(double minX, double minY, double maxX, double maxY, double tile_size)
{
    this->minX = minX;
    this->minY = minY;
    this->maxX = maxX;
    this->maxY = maxY;
    this->tile_size = tile_size;
}
Ground::~Ground()
{

}

void Ground::drawGroundTex(GLuint num1, GLuint num2)
{
    for (int i = minX / tile_size; i < maxX / tile_size; ++i)
    {
        for (int j = minY / tile_size; j < maxY / tile_size; ++j)
        {
            if ((i + j) % 2)
            {
                glBindTexture(GL_TEXTURE_2D, num1);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &ambient[0][0]);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuse[0][0]);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specular[0][0]);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &emission[0][0]);
                glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess[0]);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, num2);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &ambient[1][1]);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuse[1][1]);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specular[1][1]);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &emission[1][1]);
                glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess[1]);
            }
            glColor3f(1, 1, 1);
            glEnable(GL_TEXTURE_2D);
            glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0);

            glTexCoord2f(0, 0); glVertex3d(i * tile_size, 0.0, j * tile_size);
            glTexCoord2f(1, 0); glVertex3d((i + 1) * tile_size, 0.0, j * tile_size);
            glTexCoord2f(1, 1); glVertex3d((i + 1) * tile_size, 0.0, (j + 1) * tile_size);
            glTexCoord2f(0, 1); glVertex3d(i * tile_size, 0.0, (j + 1) * tile_size);
            //std::cout<<i * tile_size<<" "<<j * tile_size<<std::endl;
            glEnd();
            glDisable(GL_TEXTURE_2D);
        }
    }
    //std::cout<<std::endl;
}
}