// UTS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glut.h>
#include <math.h>

float posX = 0, posY = 0;
bool isJumping = false; // Status lompat karakter: true jika karakter sedang melompat, false jika karakter di tanah
float jumpHeight = 0; // Ketinggian lompatan karakter dari level tanah saat melompat (bertambah saat lompat)
float groundLevel = 160; // Acuan posisi lantai

// Fungsi untuk menggambar lingkaran (untuk kepala, mata, dll)
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1416f * float(i) / float(100);
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Fungsi untuk menggambar persegi panjang (untuk tubuh, tangan, kaki, dll)
void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

// Fungsi untuk menggambar segitiga (untuk gunung, dll)
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

// Fungsi untuk menggambar kurva Bezier (untuk mulut)
void drawBezier(float p0[2], float p1[2], float p2[2], int segments) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; ++i) {
        float t = (float)i / (float)segments;
        float u = 1.0f - t;
        float x = u * u * p0[0] + 2 * u * t * p1[0] + t * t * p2[0];
        float y = u * u * p0[1] + 2 * u * t * p1[1] + t * t * p2[1];
        glVertex2f(x, y);
    }
    glEnd();
}

// Fungsi untuk menggambar karakter utama
void drawCharacter() {
    glPushMatrix();
        glTranslatef(posX, groundLevel + jumpHeight, 0.0f); // Translasi untuk posisi karakter

        // Rambut
        glColor3f(0, 0, 0); // Warna hitam untuk rambut
            drawCircle(199.8, 130, 33); // Rambut di atas kepala

        // Kepala
        glColor3f(1, 0.8, 0.6); // Warna kulit kepala
            drawCircle(200, 120, 30); // Kepala

        // Mata
        glColor3f(1, 1, 1); // Warna putih untuk mata
            drawCircle(190, 130, 5);
        glColor3f(0, 0, 0); // Warna hitam untuk bola mata kiri
            drawCircle(190, 130, 2);

        glColor3f(1, 1, 1); // Warna putih untuk mata
            drawCircle(210, 130, 5);
        glColor3f(0, 0, 0); // Warna hitam untuk bola mata kanan
            drawCircle(210, 130, 2);

        // Hidung
        glColor3f(20, 0.9, 0.7); // Warna kulit
            drawCircle(200, 118, 3);

        // Mulut
        glColor3f(1, 0, 0); // Warna merah untuk mulut
        float mulutp0[2] = { 190, 110 }; // Titik awal
        float mulutp1[2] = { 200, 95 }; // Titik menentukan kelengkungan
        float mulutp2[2] = { 210, 110 }; // Titik akhir
        glLineWidth(5);
        drawBezier(mulutp0, mulutp1, mulutp2, 20); // Gambar kurva Bezier

        // Telinga kiri
        glColor3f(1, 0.8, 0.6); // Warna kulit
            drawCircle(170, 130, 5);

        // Telinga kanan
        glColor3f(1, 0.8, 0.6); // Warna kulit
            drawCircle(230, 130, 5);

        // Badan
        glColor3f(0, 0, 1); // Warna biru
        glLineWidth(20); // Ketebalan garis untuk badan
        float badanP0[2] = { 180, 85 }; // Titik awal badan, disesuaikan
        float badanP1[2] = { 200, 74 }; // Titik menentukan kelengkungan
        float badanP2[2] = { 220, 85 }; // Titik akhir badan
        drawBezier(badanP0, badanP1, badanP2, 20); // Gambar kurva Bezier untuk badan

        glBegin(GL_QUADS);
            glVertex2f(180, 20); // Koordinat bawah badan
            glVertex2f(220, 20); // Koordinat bawah badan
            glVertex2f(220, 90); // Koordinat atas badan
            glVertex2f(180, 90); // Koordinat atas badan
        glEnd();

        // Tangan kiri
        glColor3f(1, 0.8, 0.6);
        glBegin(GL_QUADS);
            glVertex2f(184, 100);
            glVertex2f(184, 100);
            glVertex2f(170, 50);
            glVertex2f(160, 50);
        glEnd();

        // Tangan kanan
        glColor3f(1, 0.8, 0.6);
        glBegin(GL_QUADS);
            glColor3f(1, 0.8, 0.6);
            glVertex2f(216, 100);
            glVertex2f(216, 100);
            glVertex2f(230, 50);
            glVertex2f(240, 50);
        glEnd();

        // Kaki
        glColor3f(0, 0, 0); // Warna hitam untuk celana
        glBegin(GL_QUADS);
            glVertex2f(180, 20);
            glVertex2f(220, 20);
            glVertex2f(220, 50);
            glVertex2f(180, 50);
        glEnd();

        glColor3f(0, 0, 0); // Warna hitam untuk celana
            drawRectangle(180, -30, 195, 20); // Kaki kiri

        glColor3f(0, 0, 0); // Warna hitam untuk celana
            drawRectangle(205, -30, 220, 20); // Kaki kanan

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Langit
    glColor3f(0.529, 0.808, 0.980);
    glBegin(GL_QUADS);
        glVertex2f(0, 500);
        glVertex2f(500, 500);
        glVertex2f(500, 250);
        glVertex2f(0, 250);
    glEnd();

    // Matahari
    glColor3f(1, 0.843, 0);
        drawCircle(400, 400, 40);

    // Gunung
    glColor3f(0.133, 0.545, 0.133);
        drawTriangle(50, 250, 250, 450, 450, 250);
    glColor3f(0.196, 0.804, 0.196);
        drawTriangle(200, 250, 350, 400, 500, 250);

    // Rumput
    glColor3f(0, 0.5, 0);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(500, 0);
        glVertex2f(500, 250);
        glVertex2f(0, 250);
    glEnd();

    // Pohon Pertama
    glColor3f(0.5, 0.25, 0); // Warna batang
    glBegin(GL_QUADS);
        glVertex2f(45, 180);
        glVertex2f(65, 180);
        glVertex2f(65, 330);
        glVertex2f(45, 330);
    glEnd();
    // Daun Pohon
    glColor3f(0, 0.5, 0); // Warna daun
        drawCircle(35, 340, 20);
        drawCircle(55, 340, 20);
        drawCircle(75, 340, 20);
        drawCircle(45, 350, 20);
        drawCircle(65, 350, 20);
    glColor3f(0.0, 0.5, 0); // Warna daun
        drawCircle(55, 360, 20.0);

    // Pohon Kedua 
    // Batang
        glColor3f(0.5, 0.25, 0); // Warna batang
    glBegin(GL_QUADS);
        glVertex2f(445, 180);
        glVertex2f(465, 180);
        glVertex2f(465, 330);
        glVertex2f(445, 330);
    glEnd();
    // Daun  
    glColor3f(0, 0.5, 0); // Warna daun
        drawCircle(435, 340, 20);
        drawCircle(455, 340, 20);
        drawCircle(475, 340, 20);
        drawCircle(445, 350, 20);
        drawCircle(465, 350, 20);
        drawCircle(455, 360, 20);


    // Gambar karakter utama
    drawCharacter();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'A':
    case 'a':
        posX -= 5;
        break; // Gerak ke kiri
    case 'D':
    case 'd':
        posX += 5;
        break; // Gerak ke kanan
    case 'W':
    case 'w':
        if (!isJumping) isJumping = true;
        break; // Lompat
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        posX -= 5;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        posX += 5;
    }
}

void jumpAnimation(int value) {
    if (isJumping) {
        jumpHeight += 5;
        if (jumpHeight >= 50) isJumping = false;
    }
    else if (jumpHeight > 0) {
        jumpHeight -= 5;
    }
    glutPostRedisplay();
    glutTimerFunc(16, jumpAnimation, 0);
}

void init() {
    glClearColor(1, 1, 1, 1);
    glOrtho(0, 500, 0, 500, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("UTS Lab. GrafKom | Elizabeth [094] & Mutiara [115]");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, jumpAnimation, 0);
    glutMainLoop();
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
